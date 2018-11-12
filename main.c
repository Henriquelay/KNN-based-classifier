#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/distancias.h"
#include "headers/filemanager.h"
#include "headers/knn.h"

void output(char **pathPredicao, int *c, float *acc, float **vetorClassificados, int  ***matrizConfusa, char **jordana, float *maiorRotulo, int *nlinhas){

        sprintf(*jordana, "%s%s%i%s", *pathPredicao ,"predicao_", *c + 1, ".txt");
        printf(">Arquivo de saída: %s\n", *jordana);

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

int contaDigito(int num){
    int nDigitos = 1;
    while(num > 9){
        num = num % 10;
        nDigitos++;
    }
    return nDigitos;
}


int main(int argc, char *argv[]){
    FILE *config = fopen(argv[1], "r");

    if(config == NULL){
        printf("Arquivo de config não existe! Finalizando...\n");
        exit(1);
    }

    int nLinhas = countLinhas(config);
    int nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras para posicionar o ponteiro da STREAM
    puts(">Lendo arquivo de configuração...\n");
    Tpaths *paths = setupPaths(config);
    Tamostra *amostras = setupAmostras(config, nLinhasVetores);

    FILE *treinoFile = fopen(paths->pathTreino, "r");
    Data treino;

    if(treinoFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    
    puts(">Lendo base de treino...");
    transcribe(treinoFile, &treino.matriz, &treino.rotulo, &treino.nlinhas, &treino.ncolunas);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    puts(">Lendo base de teste...\n");
    transcribe(testeFile, &teste.matriz, &teste.rotulo, &teste.nlinhas, &teste.ncolunas);

    //conta quantos caracteres o maior numero de saída terá
    int maiorDigito = contaDigito(nLinhasVetores);
    
    for(int c = 0; c < nLinhasVetores; c++){
        float *vetorClassificados;
        float maiorRotulo;
        char* jordana = (char*) malloc((maiorDigito + (int)strlen(paths->pathPredicao) + 14) * sizeof(char));
        //jordana armazera a string de saida
        //+9 pelo "predicao_", +4 pelo ".txt", +1 pelo '\0'

        knn(&vetorClassificados, &maiorRotulo, treino, teste, amostras[c]);
        
        int **matrizConfusa;    //ela não faz ideia do que está fazendo
        matrizConfusa = (int**) calloc(maiorRotulo+1, sizeof(int *));

        for(int i = 0; i <= maiorRotulo; i++){
            matrizConfusa[i] = (int*) calloc(maiorRotulo+1, sizeof(int));
        }

        int acertos = 0;
        for(int i = 0; i < teste.nlinhas; i++){
            if(vetorClassificados[i] == teste.rotulo[i])
                acertos++;
            matrizConfusa[(int) teste.rotulo[i]][(int) vetorClassificados[i]]++;
        }

        float acc = (float) acertos / (float) teste.nlinhas;
 
        output(&(paths->pathPredicao), &c, &acc, &vetorClassificados, &matrizConfusa, &jordana, &maiorRotulo, &(teste.nlinhas));
        puts("");

        for(int i = 0; i < maiorRotulo+1; i++)
            free(matrizConfusa[i]); 
        free(matrizConfusa);
        free(vetorClassificados);
        free(jordana);
    }


    printf("===Sucesso!===\nAs predicoes estao em ./%s\n", paths->pathPredicao);

    free(amostras);
    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);

    for(int i = 0; i < treino.nlinhas; i++)
        free(treino.matriz[i]);
    free(treino.matriz);
    free(treino.rotulo);

    for(int i = 0; i < teste.nlinhas; i++)
        free(teste.matriz[i]);
    free(teste.matriz);
    free(teste.rotulo);

    return 0;
}
