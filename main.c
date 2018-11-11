#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"
#include "knn.h"

int main(void){
     FILE *config = fopen("iris/config.txt", "r");
    if(config == NULL){
        printf("Arquivo de config não existe!");
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
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(treinoFile, treino.matriz, treino.rotulo, treino.nlinhas, treino.ncolunas);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(testeFile, teste.matriz, teste.rotulo, teste.nlinhas, teste.ncolunas);

    // puts("\nTESTE:");
    // printaMatriz(matrizTeste, rotuloTeste, colunasTeste, linhasTeste);

    //COMEÇO DO KNN

    Kneigh **matrizVizinhos;

    distancias(&matrizVizinhos, amostras[2].tipoDistancia, amostras[2].coefMinkowski, treino, teste);

    for(int j = 0; j < treino.nlinhas; j++){
        for(int i = 0;  i < teste.nlinhas; i++){
            printf("%.f ", (matrizVizinhos[i][j].dist)); 
        }
        puts("");
    }


    free(amostras);
    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);

    free(treino.matriz);
    free(treino.rotulo);
    free(teste.matriz);
    free(teste.rotulo);
    free(matrizVizinhos);
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
