#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

	//estrutura da arvore
struct arvore {
	int num;	//valor do n�
	arvore *esq;//ponteiro para o n� da esquerda
	arvore *dir;//ponteiro para o n� da direita
	arvore *ant;//ponteiro para o n� anterior
};

//ponteiro para o valor atual e ponteiro para a raiz da arvore
arvore *atual, *raiz;
	
void inserir(){
	//Alocando espa�o para a nova estrutura
	arvore *temp = (arvore*)malloc(sizeof(arvore));
	temp->num = NULL;
	temp->dir = NULL;
	temp->esq = NULL;
	temp->ant = NULL;
			
	printf("\nINFORME O VALOR\n");
	scanf("%d", &temp->num);
	
	//Caso seja o primeiro valor
	if(raiz == NULL){
		raiz = temp;
		atual = raiz;
	} else {
		arvore *aux = raiz;
		//Encontra o lugar para adicionar o novo elemento
		while(true){
			if(temp->num > aux->num) { //verifica se o num � maior que o ultimo elemento
				if(aux->dir == NULL) { //se direita for nulo
					aux->dir = temp;
					temp->ant = aux;
					break;
				}else{  //se nao estiver nulo
					aux = aux->dir;
				}
			}else{
				if(aux->esq == NULL){  //se a esquerda for nulo
					aux->esq = temp;
					temp->ant = aux;
					break;
				}else{ //se nao estiver nulo
					aux = aux->esq;
				}
			}
		}
	}
	printf("\nVALOR %d INSERIDO COM SUCESSO\n", temp->num);
}

void lerEsquerda(){
	if(raiz == NULL) {
		printf("\nERROR 404 ARVORE NOT FOUND\n");
	} else {
		if(atual->esq != NULL){
			atual = atual->esq;
		}else{
			printf("\nNAO H� NENHUM VALOR A ESQUERDA\n");
		}
		printf("-----------------------------------\nVALOR ATUAL: %d \n-----------------------------------\n", atual->num);
	}
}

void lerDireita(){
	if(raiz == NULL) {
		printf("\nERROR 404 ARVORE NOT FOUND\n");
	} else {
		if(atual->dir != NULL){
			atual = atual->dir;
		}else{
			printf("\nNAO H� NENHUM VALOR A DIREITA\n");
		}
		printf("-----------------------------------\nVALOR ATUAL: %d \n-----------------------------------\n", atual->num);
	}
}

void lerAcima(){
	if(raiz == NULL) {
		printf("\nERROR 404 ARVORE NOT FOUND\n");
	} else {
		if(atual->ant != NULL){
			atual = atual->ant;
		}else{
			printf("\nNAO H� NENHUM VALOR A ACIMA\n");
		}
	printf("-----------------------------------\nVALOR ATUAL: %d \n-----------------------------------\n", atual->num);
	}
}

void excluir(){
	int numDel = atual->num;
	if(raiz == NULL){
		printf("\nERROR 404 ARVORE NOT FOUND\n");
	} else if(atual->dir == NULL && atual->esq == NULL) { //Caso n�o tenha nenhum ramo
		if(atual->ant->dir == atual){
			atual->ant->dir = NULL;
		}else{
			atual->ant->esq = NULL;
		}
	}
	//Caso seja um galho que possui uma folha
	else if((atual->dir != NULL && atual->esq == NULL) || (atual->dir == NULL && atual->esq != NULL)){
		if(atual->esq != NULL){ //lado esquerdo
			if(atual->ant->dir == atual){
				atual->ant->dir = atual->esq;
				atual->esq->ant = atual->ant;
			}else{
				atual->ant->esq = atual->esq;
				atual->esq->ant = atual->ant;
			}
		}else{ //lado direito
			if(atual->ant->dir == atual){
				atual->ant->dir = atual->dir;
				atual->dir->ant = atual->ant;	
			}else{
				atual->ant->esq = atual->dir;
				atual->dir->ant = atual->ant;
			}
		}
	}
	//Caso seja um galho que possui duas folhas
	else{
		//pega o valor a direita do valor atual e vai at� o valor mais a esquerda deste
		arvore *temp = atual->dir;
		
		while(temp->esq != NULL){ // temp vai mais a esquerda
			temp = temp->esq;
		}
		
		// alteracao dos ponteiros do temp 
		if(temp->dir != NULL) {
			if(temp->ant->dir == temp){
				temp->ant->dir = temp->dir;
			}else{
				temp->ant->esq = temp->dir;
			}
			temp->dir->ant = temp->ant; //apontamento do anterior
		}
		
		//remover o temp do apontamento anterior
		if(temp->ant->dir == temp){ 
			temp->ant->dir = NULL;
		}else{
			temp->ant->esq = NULL;
		}
				
		//temp -> atual
		temp->ant = atual->ant;
		temp->dir = atual->dir;
		temp->esq = atual->esq;
		
		// verifica direita e faz apontar
		if(atual->dir != NULL){
			atual->dir->ant = temp;
		}
		// verifica esquerda e faz apontar
		if(atual->esq != NULL){
	 		atual->esq->ant = temp;
		}
		//verifica o anterior e faz apontar
		if(atual->ant->dir == atual){
			atual->ant->dir = temp;
		}else{
			atual->ant->esq = temp;
		}
	}
	//Valor atual passa a ser o valor anterior e o valor a ser excluido pode receber o free
	printf("\nVALOR %d EXCLUIDO COM SUCESSO!\n", numDel);
	arvore *temp = atual;
	atual = atual->ant;
	free(temp);
}

void preOrdem(arvore *aux) {
     if(aux != NULL){
         printf(" %d ",aux->num);
         preOrdem(aux->esq);
         preOrdem(aux->dir);
     }
}

void posOrdem(arvore *aux){
     if(aux != NULL){
         posOrdem(aux->esq);
         posOrdem(aux->dir);
         printf(" %d ",aux->num);
     }
}

void ordem(arvore *aux){
     if(aux != NULL){
           ordem(aux->esq);
           printf(" %d ",aux->num);
           ordem(aux->dir);
     }
}

int nivel(arvore *aux) {
   if (aux==NULL) 
       return 0;
   else {
       int ne = nivel(aux->esq);
       int nd = nivel(aux->dir);
    	if (ne > nd) {
       		return(ne+1);
	   } else {
			return(nd+1);
	   }
   }
}

main(){
	
	setlocale(LC_ALL,"Portuguese");
	int op;
	do {
		printf("\nINFORMA A OP��O:\n1 - ADICIONAR\n2 - DESLOCAR-SE A ESQUERDA\n3 - DESLOCAR-SE A DIREITA\n4 - VOLTAR PARA CIMA\n5 - EXCLUIR\n6 - PR�-ORDEM\n7 - P�S ORDEM\n8 - EM ORDEM\n9 - N�VEIS DA �RVORE\n0 - SAIR\n");
		scanf("%d", &op);
		if (op == 1){
			inserir();
		} else if (op == 2){
			lerEsquerda();
		} else if (op == 3){
			lerDireita();
		} else if(op == 4){
			lerAcima();
		} else if(op == 5){
			excluir();
		} else if (op==6) {
			if(raiz==NULL) {
				printf("\nERROR 404 ARVORE NOT FOUND\n");
			} else {
				printf("\nPR� ORDEM:\n-----------------------------------\n");
				preOrdem(raiz);
				printf("\n-----------------------------------\n");
			}
		} else if (op==7) {
			if(raiz==NULL) {
				printf("\nERROR 404 ARVORE NOT FOUND\n");
			} else {
				printf("\nP�S ORDEM:\n-----------------------------------\n");
				posOrdem(raiz);
				printf("\n-----------------------------------\n");
			}
		} else if (op==8) {
			if(raiz==NULL) {
				printf("\nERROR 404 ARVORE NOT FOUND\n");
			} else {
				printf("\nEM ORDEM:\n-----------------------------------\n");
				ordem(raiz);
				printf("\n-----------------------------------\n");
			}
		} else if (op==9) {
			printf("N�VEL DA �RVORE %d \n", nivel(raiz));
			printf("\n-----------------------------------\n");
		}
	} while (op!=0);
	system("pause");
}

/*
https://www.vivaolinux.com.br/script/avores-binarias-em-C
*/

