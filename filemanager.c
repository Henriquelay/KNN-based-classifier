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

int countLines(FILE *arquivo){
    int charAtual = 0, nLinhas = 1;

    while((charAtual = fgetc(arquivo)) != EOF)
        if(charAtual == '\n') nLinhas++;

    rewind(arquivo);
  return nLinhas;
}

//conta chars de uma linha especifica
int countChars(FILE *arquivo, int linha){
    int nLinhas = 1, nChars = 0, charAtual = 0;

    while((charAtual = fgetc(arquivo)) != EOF){
        if(nLinhas == linha){
            nChars++;
            while((charAtual = getc(arquivo)) != 10)        //10 é \n em int
                nChars++;
        }
        if(charAtual == '\n') nLinhas++;
    }
    rewind(arquivo);
    return nChars;
}

void setupConfig(FILE *config, char *pathTreino, char *pathTeste, char *pathPredicao, int *k, char *tipoDistancia, float *coefMinkowski, int *nLinhas){
    *nLinhas = countLines(config);

    printf("NChar linha 2 = %i", countChars(config, 3));

    // pathTreino = (char*) malloc(countChars(config, 1) * sizeof(char));
    // pathTeste = (char*) malloc(countChars(config, 2) * sizeof(char));
    // pathPredicao = (char*) malloc(countChars(config, 3) * sizeof(char));

    // k = (int*) malloc(*nLinhas * sizeof(int));
    // tipoDistancia = (char*) malloc(*nLinhas * sizeof(char));
    // coefMinkowski = (float*) malloc(*nLinhas * sizeof(float));
}

void main(){
    int *k, nLinhas;
    char *tipoDistancia, *pathTreino, *pathTeste, *pathPredicao;
    float *coefMinkowski;
    FILE *config = fopen("iris/config.txt", "r");

    if(config == NULL){
        printf("Deu bosta. Fechando.\n\n");
            exit(EXIT_FAILURE);
    }

    setupConfig(config, pathTreino, pathTeste, pathPredicao, k, tipoDistancia, coefMinkowski, &nLinhas);

    // printa os vetores de path
    // printf("Path Treino = %p \nPath Teste = %p \nPath Predicao = %p\n==========================\n", &pathTreino, &pathTeste, &pathPredicao);

      //preenche e printa os outros vetores
    // for(int i = 0; i < nLinhas; i++){
    //     k[i] = i;
    //     printf("K%i %i\n", i, k[i]);
    //     tipoDistancia[i] = (char) i;
    //     printf("tipoDistancia%i %i\n", i, tipoDistancia[i]);
    //     coefMinkowski[i] = (float) i;
    //     printf("coefMinkowski%i %f\n", i, coefMinkowski[i]);
    // }

    // free(k);
    // free(tipoDistancia);
    // free(coefMinkowski);
    // free(pathTreino);
    // free(pathTeste);
    // free(pathPredicao);
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