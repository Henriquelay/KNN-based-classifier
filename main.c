#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distancias.h"
#include "filemanager.h"
#include "knn.h"


void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, linhasConfig;
    float *coefMinkowski;
    char *tipoDistancia;
    char *pathTreino, *pathTeste, *pathPredicoes;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicoes, &k, &tipoDistancia, &coefMinkowski, &linhasConfig);

    // puts("PATHS:");
    // printf("%s\n", pathTreino);
    // printf("%s\n", pathTeste);
    // printf("%s\n", pathPredicoes);

    
    // puts("\nCONFIGS:");
    // for(int i = 0; i < linhasConfig - 3; i++){
    //     printf("%d %c %.2f\n", k[i], tipoDistancia[i], coefMinkowski[i]);
    // }


    FILE *treino = fopen(pathTreino, "r");
    float **matrizTreino, *rotuloTreino;
    int linhasTreino, colunasTreino;

    if(treino == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(treino, &matrizTreino, &rotuloTreino, &linhasTreino, &colunasTreino);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *teste = fopen(pathTeste, "r");
    float **matrizTeste, *rotuloTeste;
    int linhasTeste, colunasTeste;

    if(teste == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(teste, &matrizTeste, &rotuloTeste, &linhasTeste, &colunasTeste);


    float *vetorClassificados;
    float maiorRotulo;

    int c = 0;
    knn(&vetorClassificados, &maiorRotulo, matrizTreino, rotuloTreino, matrizTeste, rotuloTeste, 
            tipoDistancia[c], k[c], coefMinkowski[c], linhasTreino, colunasTreino, linhasTeste, colunasTeste);
    
    int **matrizConfusa;
    matrizConfusa = (int **) calloc(maiorRotulo+1, sizeof(int *));

    for(int i = 0; i<=maiorRotulo; i++){
        matrizConfusa[i] = (int *) calloc(maiorRotulo+1, sizeof(int));;
    }

    int acertos = 0;
    for(int i = 0; i<linhasTeste; i++){
        if(vetorClassificados[i] == rotuloTeste[i])
            acertos++;
        matrizConfusa[(int)rotuloTeste[i]][(int)vetorClassificados[i]]++;
    }

    float acc = (float)acertos / (float)linhasTeste;

    

    FILE* arq = fopen("saida.txt", "w");


    fprintf(arq, "%.2f\n", acc); //PRINTA ACURACY

    printMatrizFile(arq, (int)maiorRotulo+1, matrizConfusa);

    printVetorFile(arq, linhasTeste, vetorClassificados);

    fclose(arq);
    free(matrizConfusa);
    free(vetorClassificados); 


    free(k);
    free(coefMinkowski);
    free(tipoDistancia);
    free(pathTreino);
    free(pathTeste);
    free(pathPredicoes);
    
    free(matrizTreino);
    free(rotuloTreino);
    free(matrizTeste);
    free(rotuloTeste);
    puts("");
}