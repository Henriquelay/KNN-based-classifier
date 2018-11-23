#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/distancias.h"
#include "headers/filemanager.h"
#include "headers/knn.h"
#include "headers/aux.h"


int main(){
    header();
    FILE *config = fopen("config.txt", "r");

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
    transcribe(&treinoFile, &treino.matriz, &treino.rotulo, &treino.nlinhas, &treino.ncolunas);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    puts(">Lendo base de teste...\n");
    transcribe(&testeFile, &teste.matriz, &teste.rotulo, &teste.nlinhas, &teste.ncolunas);

    if(teste.ncolunas != treino.ncolunas){
        printf("A base de testes não possui a quantidade correta de features!\n");
        exit(1);
    }

    //conta quantos caracteres o maior numero de saída terá
    int maiorDigito = contaDigito(nLinhasVetores);
    
    //Gerando as predições para cada configuração diferente
    for(int c = 0; c < nLinhasVetores; c++){
        float *vetorClassificados;
        float maiorRotulo;
        char* jordana = (char*) malloc((maiorDigito + (int)strlen(paths->pathPredicao) + 14) * sizeof(char));
        //jordana armaneza o caminho do arquivo de saída
        //+9 pelo "predicao_", +4 pelo ".txt", +1 pelo '\0'
        printf("-------CONFIGURAÇÃO Nº%d-------\n", c+1);

        printf("K = %d ; DIST = %c ;", amostras[c].k, amostras[c].tipoDistancia);
        
        if(amostras[c].tipoDistancia == 'M')
            printf(" COEF = %.1f ;", amostras[c].coefMinkowski);

        puts("");

        knn(&vetorClassificados, &maiorRotulo, &treino, &teste, &amostras[c]);
        
        int **matrizConfusa;//ela não faz ideia do que está fazendo

        float acc = geraConfusao(&matrizConfusa, &teste, &vetorClassificados, &maiorRotulo);
 
        output(&(paths->pathPredicao), &c, &acc, &vetorClassificados, &matrizConfusa, &jordana, &maiorRotulo, &(teste.nlinhas));
        puts("");

        for(int i = 0; i <= maiorRotulo; i++)
            free(matrizConfusa[i]); 
        free(matrizConfusa);
        free(vetorClassificados);
        free(jordana);
    }

    printf("===Sucesso!===\nAs predicoes estao em %s\n", paths->pathPredicao);

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
