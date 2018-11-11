#include <stdlib.h>
#include "distancias.h"
#include "filemanager.h"
#include "knn.h"

int main(void){
     FILE *config = fopen("iris/config.txt", "r");
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

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe! Finalizando...\n");
        exit(1);
    }
    
    transcribe(testeFile, &teste.matriz, &teste.rotulo, &teste.nlinhas, &teste.ncolunas);

   

    float *vetorClassificados;
    float maiorRotulo;

    int c = 0;
    knn(&vetorClassificados, &maiorRotulo, treino, teste, amostras[c]);
    
    int **matrizConfusa;
    matrizConfusa = (int **) calloc(maiorRotulo+1, sizeof(int *));

    for(int i = 0; i <= maiorRotulo; i++){
        matrizConfusa[i] = (int *) calloc(maiorRotulo+1, sizeof(int));
    }

    int acertos = 0;
    for(int i = 0; i < teste.nlinhas; i++){
        if(vetorClassificados[i] == teste.rotulo[i])
            acertos++;
        matrizConfusa[(int)teste.rotulo[i]][(int)vetorClassificados[i]]++;
    }

    float acc = (float)acertos / (float)teste.nlinhas;

    

    FILE* arq = fopen("saida.txt", "w");


    fprintf(arq, "%.2f\n", acc); //PRINTA ACURACY

    printMatrizFile(arq, (int)maiorRotulo+1, matrizConfusa);

    printVetorFile(arq, teste.nlinhas, vetorClassificados);

    fclose(arq);
    free(matrizConfusa);
    free(amostras);
    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);

    free(treino.matriz);
    free(treino.rotulo);
    free(teste.matriz);
    free(teste.rotulo);
    // free(matrizVizinhos);
    free(vetorClassificados);
    puts("");

    return 0;
}

/* Main apenas para printar o config
int main(void){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas = countLinhas(config), nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra *amostras = setupAmostras(config, nLinhasVetores);

    puts("PATHS:");
    printf("%s\n", paths->pathTreino);
    printf("%s\n", paths->pathTeste);
    printf("%s\n", paths->pathPredicao);

    puts("VETORES:");
    for(int i = 0; i < nLinhasVetores; i++){
        printf("K[%i] = %i\t Distancia[%i] = %c\t CoefMinKowski[%i] = %.2f\n", i, amostras[i].k, i, amostras[i].tipoDistancia, i, amostras[i].coefMinkowski);
    }
    
    for(int i = 0; i < nLinhasVetores; i++){

    printf("\n\tVETORES\n");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, amostra[i]->k, i, amostra[i]->tipoDistancia, i, amostra[i]->coefMinkowski);
    }

    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);
    free(amostras);

    return 0;
}
*/
