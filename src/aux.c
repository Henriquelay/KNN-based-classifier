#include <stdlib.h>
#include <stdio.h>
#include "../headers/aux.h"
#include "../headers/knn.h"

void output(char **pathPredicao, int *c, float *acc, float **vetorClassificados, int ***matrizConfusa, char **jordana, float *maiorRotulo, int *nlinhas){

        sprintf(*jordana, "%s%s%i%s", *pathPredicao ,"predicao_", *c + 1, ".txt");
        printf("%s\n", *jordana);

        FILE *predicao = fopen(*jordana, "w");

        if (predicao == NULL){
            printf("Erro na gravação dos resultados\n");
            printf("Pode ser que o diretório %s não exista.\n", *pathPredicao);
            exit(1);
        }

        fprintf(predicao, "%.2f\n", *acc); //PRINTA ACCURACY
        printMatrizFile(predicao, (int) *maiorRotulo + 1, *matrizConfusa);
        printVetorFile(predicao, *nlinhas, *vetorClassificados);

        fclose(predicao);
}

float geraConfusao(int ***matrizConfusa, Data *teste, float **vetorClassificados, float *maiorRotulo){
    int **matrizPerdida = (int**) calloc(*maiorRotulo + 1, sizeof(int*));
    //calloc pois fazemos a confusão por incrementos
    for(int i = 0; i < *maiorRotulo + 1; i++){
        matrizPerdida[i] = (int*) calloc(*maiorRotulo + 1, sizeof(int));
    }

    int acertos = 0;
    for(int i = 0; i < teste->nlinhas; i++){
        if((*vetorClassificados)[i] == teste->rotulo[i]) acertos++;
        matrizPerdida[(int) teste->rotulo[i]][(int) (*vetorClassificados)[i]]++;
    }
    *matrizConfusa = matrizPerdida;
    return ((float) acertos / (float) teste->nlinhas);
}

int contaDigito(int num){
    int nDigitos = 1;
    while(num > 9){
        num = num % 10;
        nDigitos++;
    }
    return nDigitos;
}