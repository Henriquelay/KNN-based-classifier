#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void textSize(FILE *arquivo, int *colunas, int *linhas){
    char *texto;
    texto = (char *)malloc(sizeof(char));
    int c = 0, l = 0;

    for(int i = 0; !feof(arquivo); i++){
        fscanf(arquivo, "%c", &texto[i]);
        if(l==0){
            if(texto[i] == ','){
                c++;
            }
        }
        if(texto[i] == '\n'){
            l++;
        }
        texto = realloc(texto, (i+2)*sizeof(char));
    }
    free(texto);
    rewind(arquivo);

    *colunas = c;
    *linhas = l;
}

void printaMatriz(float **matriz, float *iD, int nColunas, int nLinhas){
    for(int i = 0;  i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            printf("%.2f ", matriz[i][j]); 
        }
        printf("%.0f\n", iD[i]);
    }
}

void transcribe(FILE *arquivo, float **matrizAmostra, float *rotuloVet, int colunas, int linhas){
    for(int i = 0; !feof(arquivo); i++){
        for(int j = 0; j < colunas; j++){ 
            fscanf(arquivo, "%f,", &matrizAmostra[i][j]);
            if(j==(colunas-1)){
                fscanf(arquivo, "%f", &rotuloVet[i]);
            }
        }
    }
    rewind(arquivo);
}

void maloqueiroPaths(int *tamanhoString, const int counterLinhas, char *pathTreino, char *pathTeste, char *pathPredicao){
    switch(counterLinhas){
        case 1:
            pathTreino = (char*) calloc(*tamanhoString, sizeof(char));
            puts("alocado pathTreino");
            break;
        case 2:
            pathTeste = (char*) calloc(*tamanhoString, sizeof(char));
            puts("alocado pathTeste");
            break;
        case 3:
            pathPredicao = (char*) calloc(*tamanhoString, sizeof(char));
            puts("alocado pathPredicao");
            break;
    }
    *tamanhoString = 0;
}

void maloqueiroVectors(int *counterLinhas, int *k, char *distancia, float *coefMinkowski){
    k = (int*) calloc(*counterLinhas, sizeof(int));
    distancia = (char*) calloc(*counterLinhas, sizeof(char));
    coefMinkowski = (float*) calloc(*counterLinhas, sizeof(float));
}

void setupConfig(FILE *config, char *pathTreino, char *pathTeste, char *pathPredicao, int *k, char *distancia, float *coefMinkowski, int *nLinhas){
    int tamanhoString = 0, charAtual; 


    do{
        tamanhoString++;
        charAtual = fgetc(config);

        if(charAtual != '\n') tamanhoString++;
        else {
            *nLinhas++;
            maloqueiroPaths(&tamanhoString, *nLinhas, pathTreino, pathTeste, pathPredicao);
        }
    }while(charAtual != EOF);

    //-1 pois o EOF é depois do \n
    *nLinhas--;
    // -3 pois as 3 primeiras linhas são paths
    maloqueiroVectors(nLinhas - 3, k, distancia, coefMinkowski);
}

void main(){
    int *k, nLinhas = 0;
    char *tipoDistancia, *pathTreino, *pathTeste, *pathPredicao;
    float *coefMinkowski;
    FILE *config = fopen("iris/config.txt", "r");

    if(config == NULL){
        printf("Deu bosta. Fechando.\n\n");
            exit(EXIT_FAILURE);
    }

    setupConfig(config, pathTreino, pathTeste, pathPredicao, k, tipoDistancia, coefMinkowski, &nLinhas);

    // printa os vetores
    // printf("Path Treino = %p \nPath Teste = %p \nPath Predicao = %p\n==========================\n", &pathTreino, &pathTeste, &pathPredicao);

    for(int i = 0; i < nLinhas; i++){
        k[i] = i;
        printf("K%i %i\n", i, k[i]);
        tipoDistancia[i] = (char) i;
        printf("tipoDistancia%i %i\n", i, tipoDistancia[i]);
        coefMinkowski[i] = (float) i;
        printf("coefMinkowski%i %i\n", i, coefMinkowski[i]);
    }

    // free(k);
    // free(tipoDistancia);
    // free(coefMinkowski);
    // free(pathTreino);
    // free(pathTeste);
    // free(pathPredicao);
    // fclose(config);


/*
    FILE *arq = fopen("vowels/dataset/vowels_teste.csv", "r");
    float **amostras;
    float *rotulo;
    int colunas, linhas;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    textSize(arq, &colunas, &linhas); //MEDE O TAMANHO DO ARQUIVO (FEATURESxAMOSTRAS)
    
    printf("Colunas: %d\nLinhas: %d\n", colunas, linhas);

    amostras = (float **)malloc(linhas * sizeof(float *));

    for(int i = 0; i<linhas; i++){
        amostras[i] = (float *)malloc(colunas * sizeof(float));
    }

    rotulo = (float *)malloc(linhas * sizeof(float));

    transcribe(arq, amostras, rotulo, colunas, linhas);
    printaMatriz(amostras, rotulo, colunas, linhas);


    free(amostras);
    free(rotulo);
    fclose(arq);
    printf("\n\n");
*/
}