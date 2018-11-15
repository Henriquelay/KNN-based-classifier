/*              Esta biblioteca contém as funções
               que geram os dados de saída na main

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include "../headers/aux.h"
#include "../headers/knn.h"

//PRODUZ O ARQUIVO .txt DE SAÍDA
void output(char **pathPredicao, int *c, float *acc, float **vetorClassificados, int ***matrizConfusa, char **jordana, float *maiorRotulo, int *nlinhas){

        sprintf(*jordana, "%s%s%i%s", *pathPredicao ,"predicao_", *c + 1, ".txt");
        printf(">Arquivo de saída: %s\n", *jordana);

        FILE *predicao = fopen(*jordana, "w");

        if (predicao == NULL){
            printf("Erro na gravação dos resultados\n");
            printf("Pode ser que o diretório %s não exista.\n", *pathPredicao);
            exit(1);
        }

        fprintf(predicao, "%.2f\n", *acc); //PRINTA ACCURACY
        printMatrizFile(predicao, (int) *maiorRotulo, *matrizConfusa);
        printVetorFile(predicao, *nlinhas, *vetorClassificados);

        fclose(predicao);
}

//GERA A MATRIZ DE CONFUSÃO E CALCULA A ACCURACY
float geraConfusao(int ***matrizConfusa, Data *teste, float **vetorClassificados, float *maiorRotulo){
    int **matrizPerdida = (int**) calloc(*maiorRotulo, sizeof(int*));
    //calloc pois fazemos a confusão por incrementos
    for(int i = 0; i <= *maiorRotulo; i++){
        matrizPerdida[i] = (int*) calloc(*maiorRotulo, sizeof(int));
    }

    int acertos = 0;
    for(int i = 0; i < teste->nlinhas; i++){
        if((*vetorClassificados)[i] == teste->rotulo[i]) acertos++;
        matrizPerdida[((int) teste->rotulo[i])][((int) (*vetorClassificados)[i])]++;
    }
    *matrizConfusa = matrizPerdida;

    return ((float) acertos / (float) teste->nlinhas);
}

//CONTA A QUANTIDADE DE DIGITOS QUE UM NÚMERO OCUPA
int contaDigito(int num){
    int nDigitos = 1;
    while(num > 9){
        num = num % 10;
        nDigitos++;
    }
    return nDigitos;
}