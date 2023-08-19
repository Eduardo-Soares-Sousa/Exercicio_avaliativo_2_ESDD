#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000000

struct tab_indice{
	int chave;
	int posicao; 
};

void carrega_vetor_aleatorio(int colecao[], int tamanho, int qtd_digitos);
void carrega_vetor_ordenado(int colecao[], int valor_inicial, int tamanho);
void imprime_vetor(int colecao[], int tamanho);
void gerar_indice(int arquivo[], struct tab_indice indice[]);
int busca_indexada(int chave, struct tab_indice indice[]);

int main(int argc, char const *argv[]){
    
    int vetor[TAM];
	int elem;
	struct tab_indice array[100+1];
    int pos_encontrada;

    carrega_vetor_ordenado(vetor, 0, TAM);
    imprime_vetor(vetor, TAM);

	printf("Índice\n");
	gerar_indice(vetor, array);

	printf("Digite qual número deseja ser buscado: ");
	scanf("%d", &elem);

    pos_encontrada = busca_indexada(elem, array); //pos_encontrada recebe a posição da chave no vetor

    if (pos_encontrada != -1) {
        printf("A chave: %d, foi encontrada com êxito, na posição %d.", elem, pos_encontrada);//mostra a chave digitada pelo usuário e a posição onde ela se encontra
    } else {
        printf("A chave: %d, não existe neste vetor.", elem);
    }

    return 0;
}

void carrega_vetor_aleatorio(int colecao[], int tamanho, int qtd_digitos){
	int i, digitos;
	
	for(i=1, digitos = 10; i < qtd_digitos; i++){
		digitos *= 10;
	}
	
	srand( (unsigned) time(NULL) );
	for(i=0; i < tamanho; i++){
		colecao[i] = rand() % digitos;
	}
	
}

void carrega_vetor_ordenado(int colecao[], int valor_inicial, int tamanho){
	int i;
	srand( (unsigned) time(NULL) );
	for(colecao[0] = valor_inicial, i=1; i<tamanho; i++){
		colecao[i] = colecao[i-1] + (rand() % 10);
	}
}

void imprime_vetor(int colecao[], int tamanho){
	int i = 0;
	for(i = 0; i < tamanho; i++){
		printf("[%d]: %d, ", i, colecao[i]);
		printf("\n");
	}
	printf("\n");
}

void gerar_indice(int arquivo[], struct tab_indice indice[]){
	int pos_indice, pos_arquivo;

	indice[0].chave = arquivo[0];
	indice[0].posicao = 0;


	for(pos_indice = 1, pos_arquivo = 9999; pos_arquivo < TAM; pos_arquivo+= 10000, pos_indice++){
		indice[pos_indice].chave = arquivo[pos_arquivo];
		indice[pos_indice].posicao = pos_arquivo;
	}

	/*Imprimir a tabela de indice*/
	for(pos_indice = 0; pos_indice <= 100; pos_indice++){
		printf("Indice[%d] -> chave: %d, posicao: %d\n", pos_indice, indice[pos_indice].chave, indice[pos_indice].posicao);
	}
}

int busca_indexada(int chave, struct tab_indice indice[]) {
    int pos_indice = 0;

    //não funciona
    while (pos_indice <= 100 && indice[pos_indice].chave <= chave){
        int i = indice[pos_indice].posicao;
        while (i < TAM && indice[i].chave <= chave){
            if (chave == indice[i].chave) {
                return indice[i].posicao; //retorna a possição da chave se ela existir no vetor
            }
            i++;
        }
        pos_indice++;
    }

    return -1;
}

//tentativas falhas para implementação da busca sequencial indexada
/*
    int pos_indice = 0;

    while(pos_indice <= 100){
        int indice[pos_indice].posicao = 0;
        while(indice[pos_indice].posicao <= TAM && indice[pos_indice].chave <= chave){
            if(indice[pos_indice].chave == chave){
                return indice[pos_indice].posicao;
            }
            indice[pos_indice].posicao++;
        }
        pos_indice++;
    }
return -1;
*/

/*
    int pos_indice = 0;

    for(pos_indice = 0; pos_indice <= 100+1; pos_indice++){
        if( (chave == indice[pos_indice].chave) ){
            return indice[pos_indice].posicao;
        }else{
            if( (chave <= indice[pos_indice].chave) && (chave >= indice[pos_indice+1].chave) ){
                for(int i = 0; i < n; i++){
                    if(chave == indice[pos_indice].chave){
                        return i;
                    }
                }
            }   
        }
        return -1;
    }
*/

/*
    pos_indice = 0;
        for(pos_indice = 0; pos_indice <= 100; pos_indice++){
            if(indice[pos_indice].chave <= chave){
                int i = 0;
                for(i = 0; i <= 9999; i++){
                    if(chave == indice[i].chave){
                        return indice[i].posicao;
                    }else{
                        return -1;
                    }
                }
            }
        }
        return -1;
*/