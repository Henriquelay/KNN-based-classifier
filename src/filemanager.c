/*              Esta biblioteca contém as funções
            que gerenciam leitura e escrita de arquivos

                Davi Petris e Henrique Layber                  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/filemanager.h"

//PRINTA A MATRIZ DE CONFUSÃO NO ARQUIVO DE SAÍDA
void printMatrizFile(FILE *arq ,int size, int **matriz){
    fprintf(arq, "\n");
    for(int i = 0; i <= size; i++){ 
        for(int j = 0; j <= size; j++){
            fprintf(arq, "%d", matriz[i][j]);    
            if(j!=size)
                fprintf(arq, " ");    
        }
        fprintf(arq, "\n");
    }
    fprintf(arq, "\n");
}

//PRINTA AS PREDIÇÕES NO ARQUIVO DE SAÍDA
void printVetorFile(FILE *arq, int size, float *vet){
    for(int i = 0; i<size; i++){ 
        fprintf(arq, "%.f\n", vet[i]);
    }
}

//debug apenas. mostra os vetores dos arquivos de dados
void printaMatriz(float **matriz, float *iD, int nColunas, int nLinhas){
    for(int i = 0;  i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            printf("%.2f ", matriz[i][j]); 
        }
        printf("%.0f\n", iD[i]);
    }
}

int countLinhas(FILE *arquivo){
    int charAtual = 0, nLinhas = 1;

    while((charAtual = fgetc(arquivo)) != EOF)
        if(charAtual == 10) nLinhas++;

    rewind(arquivo);
    nLinhas--;  //pois o arquivo quebra linha mais uma vez antes do EOF
    return nLinhas;
}

//pega os dados dos datasets e passa para vetores no programa
void transcribe(FILE **arquivo, float ***matrizAmostra, float **rotuloVet, int *linhas, int *colunas){
    char junkChar;
    float **matriz;
    float *rotulo;
    int c = 0, l = countLinhas(*arquivo);
    
    //Conta a quantidade de colunas
    for(int i = 0; !feof(*arquivo); i++){
        fscanf(*arquivo, "%c", &junkChar);
        if(junkChar == ','){
            c++;
        }else if (junkChar == '\n'){
            break;
        }
    }
    rewind(*arquivo);

    matriz = (float**) malloc(l * sizeof(float*));
    rotulo = (float*) malloc(l *sizeof(float));

    //Guarda todos os valores em uma matriz
    for(int i = 0; i < l ; i++){
        matriz[i] = (float *) malloc(c * sizeof(float));
        for(int j = 0; j < c; j++){
            fscanf(*arquivo, "%f%c", &matriz[i][j], &junkChar);
        }
        //Guarda todos os rotulos em um vetor
        fscanf(*arquivo, "%f%c", &rotulo[i], &junkChar);
        rotulo[i]--;
        //rotulo[i]--; //pois os rotulos começam de 0
    }
    
    *linhas = l;
    *colunas = c;
    *matrizAmostra  = matriz;
    *rotuloVet = rotulo;

    fclose(*arquivo);
}

//conta chars de uma linha especifica
int countChars(FILE *arquivo, int linha){
    int nLinhas = 1, nChars = 0, charAtual = 0;

    rewind(arquivo);

    while((charAtual = fgetc(arquivo)) != EOF){
        if(nLinhas == linha){
            nChars++;
            do{
                nChars++;
            //10 é \n em int
            }while((charAtual = getc(arquivo)) != 10);
        }
        if(charAtual == 10) 
            nLinhas++;
    }
    rewind(arquivo);
    return nChars;
}

//remove a quebra de linha de uma string
void tiraQuebra(char *string){
    int tamanho = strlen(string);
    for(int i = 0; i < tamanho; i++){
        if(string[i] == '\n')
            string[i] = '\0';
            
    }
}

//pega os PATHs do config para vetores do programa
Tpaths* setupPaths(FILE *config){
    int sizeTreino = countChars(config, 1) + 1;
    int sizeTeste = countChars(config, 2) + 1;
    int sizePerdicao = countChars(config, 3) + 1;
    //+1 para ter espaço para o \n e \0 da string a ser inserida
    
    char treinoTemp[sizeTreino], testeTemp[sizeTeste], predicaoTemp[sizePerdicao];

    fgets(treinoTemp, sizeTreino, config);
    fgets(testeTemp, sizeTeste, config);
    fgets(predicaoTemp, sizePerdicao, config);

    strtok(treinoTemp, "\n");
    strtok(testeTemp, "\n");
    strtok(predicaoTemp, "\n");

    Tpaths *t = (Tpaths*) malloc(sizeof(Tpaths));

    t->pathTreino = (char*) malloc(strlen(treinoTemp) + sizeof(char));
    t->pathTeste = (char*) malloc(strlen(testeTemp) + sizeof(char));
    t->pathPredicao = (char*) malloc(strlen(predicaoTemp) + sizeof(char));

    strcpy(t->pathTreino, treinoTemp);
    strcpy(t->pathTeste, testeTemp);
    strcpy(t->pathPredicao, predicaoTemp);

    return t;
}
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
    //Final da leitura de PATHs
    //início da leitura dos vetores

Tamostra* setupAmostras(FILE *config, int linhasVetores){
  
    Tamostra *amostras = (Tamostra*) calloc(linhasVetores, sizeof(Tamostra));

    for(int i = 0; i < linhasVetores; i++){
        //Armazena o valor de K e o tipo de distância
        fscanf(config, "%d, %c", &(amostras[i]).k, &(amostras[i]).tipoDistancia);
        //Armazena o coeficiente de Minkwoski se necessário
        if((amostras[i]).tipoDistancia == 'M'){
            fscanf(config, ", %f\n", &(amostras[i]).coefMinkowski);
        }else{
            fgetc(config);
        }
    }

    fclose(config);
    return amostras;
}