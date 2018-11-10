#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"

/*
void knnDist(kneigh ***MatrizNeighs, float **matrizTreino, float *rotuloTreino, float **matrizTeste, 
    char tipoDist, float coefMinkowski, int linhasTreino, int colunasTreino, int linhasTeste, int colunasTeste){

    kneigh **vizinho;

    vizinho = (kneigh **) malloc(linhasTeste * sizeof(kneigh*));
    for(int i = 0; i < linhasTeste; i++){
        vizinho[i] = (kneigh *) malloc(linhasTreino * sizeof(kneigh));
    }

    // //CALCULO DE DISTÂNCIA
    for(int aTst = 0; aTst < linhasTeste; aTst++){
        for(int aTrn = 0; aTrn < linhasTreino; aTrn ++){
            switch(tipoDist){
                case 'E':
                    vizinho[aTst][aTrn].dist = euclidesVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino);
                    break;
                case 'C':
                    vizinho[aTst][aTrn].dist = chebyshevVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino);
                    break;
                case 'M':
                    vizinho[aTst][aTrn].dist = minkowskiVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino, coefMinkowski);
            }
            vizinho[aTst][aTrn].rotulo = rotuloTreino[aTrn];
        }
    }
    *MatrizNeighs = vizinho;
}
*/


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

    }

    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);
    free(amostras);

    return 0;
}

/*
void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas, nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra **amostra = setupAmostras(config, nLinhas);

    FILE *treino = fopen(paths->pathTreino, "r");
    float **matrizTreino, *rotuloTreino;
    int linhasTreino, colunasTreino;

    if(treino == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(treino, &matrizTreino, &rotuloTreino, &linhasTreino, &colunasTreino);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *teste = fopen(paths.pathTeste, "r");
    float **matrizTeste, *rotuloTeste;
    int linhasTeste, colunasTeste;

    if(teste == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(teste, &matrizTeste, &rotuloTeste, &linhasTeste, &colunasTeste);

    // puts("\nTESTE:");
    // printaMatriz(matrizTeste, rotuloTeste, colunasTeste, linhasTeste);

    // ///COMEÇO DO KNN

    kneigh **matrizVizinhos;

    knnDist(&matrizVizinhos, matrizTreino, rotuloTreino, matrizTeste, tipoDistancia[2], coefMinkowski[2], linhasTreino, colunasTreino, linhasTeste, colunasTeste);

    for(int j = 0; j < linhasTreino; j++){
        for(int i = 0;  i < linhasTeste; i++){
            printf("%.f ", ((matrizVizinhos[i][j]).dist)); 
        }
        puts("");
    }

    // free temporário (remover ao continaur o programa)
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
    free(matrizVizinhos);
    puts("");
}*/