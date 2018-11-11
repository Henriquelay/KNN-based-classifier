#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "distancias.h"
#include "filemanager.h"
#include "knn.h"

int main(int argc, char *argv[]){
    FILE *config = fopen(argv[1], "r");

    if(config == NULL){
        printf("Arquivo de config não existe! Finalizando...\n");
        exit(1);
    }

    int nLinhas = countLinhas(config);
    int nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras para posicionar o ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra *amostras = setupAmostras(config, nLinhasVetores);

    FILE *treinoFile = fopen(paths->pathTreino, "r");
    Data treino;

    if(treinoFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    
    transcribe(treinoFile, &treino.matriz, &treino.rotulo, &treino.nlinhas, &treino.ncolunas);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    
    transcribe(testeFile, &teste.matriz, &teste.rotulo, &teste.nlinhas, &teste.ncolunas);

    float *vetorClassificados;
    float maiorRotulo;
        
    int c = 2;    
    knn(&vetorClassificados, &maiorRotulo, treino, teste, amostras[c]);
    int **matrizConfusa = (int **) calloc(maiorRotulo+1, sizeof(int *));

    for(int i = 0; i <= maiorRotulo; i++)
        matrizConfusa[i] = (int *) calloc(maiorRotulo+1, sizeof(int));

    int acertos = 0;
    for(int i = 0; i < teste.nlinhas; i++){
        if(vetorClassificados[i] == teste.rotulo[i])
            acertos++;
        matrizConfusa[(int)teste.rotulo[i]][(int)vetorClassificados[i]]++;
    }

    float acc = (float)acertos / (float)teste.nlinhas;

    FILE* arq = fopen("saida.txt", "w");

    fprintf(arq, "%.2f\n", acc); //PRINTA ACCURACY
    printMatrizFile(arq, (int)maiorRotulo+1, matrizConfusa);
    printVetorFile(arq, teste.nlinhas, vetorClassificados);


    fclose(arq);
    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);
    free(amostras);
    for(int i = 0; i < maiorRotulo; i++)
        free(matrizConfusa[i]);
    free(matrizConfusa);
    for(int i = 0; i < treino.nlinhas; i++)
        free(treino.matriz[i]);
    free(treino.matriz);
    free(treino.rotulo);
    for(int i = 0; i < teste.nlinhas; i++)
        free(teste.matriz[i]);
    free(teste.matriz);
    free(teste.rotulo);
    free(vetorClassificados);

    printf("===Sucesso!===\n");
    return 0;
}