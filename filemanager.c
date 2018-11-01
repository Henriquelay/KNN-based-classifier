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



void openConfig(FILE *configuracao, char *pathTreino, char *pathTeste, char* pathPredicao, int *k, char *distancia, float *coefMinkowski, int *linhas){

    k = (int*) malloc(nLinhas * sizeof(int));
    distancia = (char*) malloc(nLinhas * sizeof(char));
    coefMinkowski = (float*) malloc(nLinhas * sizeof(float));

    for(int quebraLinhas = 0; quebraLinhas < 4; quebraLinhas++){
        fscanf(configuracao, "%s", pathTreino);
        fscanf(configuracao, "%s", pathTeste);
        fscanf(configuracao, "%s", pathPredicao);
    }

    int nLinhas = 0;
    for(int i = 0; !feof(configuracao); i++){
        while(configuracao != "\n"){ 
            fscanf(configuracao, "%i, %c", &k[i], &distancia[i]);
            if(k[i] == 'M')
                fscanf(configuracao, "%f", &coefMinkowski[i]);
            else
                coefMinkowski[i] = NULL;
        }
        nLinhas++;
    }

    *linhas = nLinhas;
    rewind(configuracao);
}

void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, nLinhas;
    char *tipoDistancia, *pathTreino, *pathTeste, *pathPredicao;
    float *coefMinkowski;

    openConfig(config, pathTreino, pathTeste, pathPredicao, k, tipoDistancia, coefMinkowski, &nLinhas);

// printa os vetores
    printf("Path Treino = %s\nPathTeste = %s\nPathPredicao = %s", pathTreino, pathTeste, pathPredicao);
    for(int i = 0; i < sizeof(k); i++){
        printf("K[%i] = %i\nDist[%i] = %c\ncoefMinkowski[%i] = %f\n\n", i, k[i], i, tipoDistancia[i], i, coefMinkowski[i]);
    }

    free(k);
    free(coefMinkowski);
    fclose(config);


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