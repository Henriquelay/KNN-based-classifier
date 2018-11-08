#include "distancias.h"
#include "openfile.h"
#include <stdio.h>
#include <stdlib.h>

void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, linhasConfig = countLinhas(config);
    float *coefMinkowski;
    char *tipoDistancia;
    char *pathTreino, *pathTeste, *pathPredicoes;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicoes, &k, &tipoDistancia, &coefMinkowski, linhasConfig);

    // puts("PATHS:");
    // printf("%s\n", pathTreino);
    // printf("%s\n", pathTeste);
    // printf("%s\n", pathPredicoes);

    puts("VETORES:");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, k[i], i, tipoDistancia[i], i, coefMinkowski[i]);
    }
    

    //free temporário (remover ao continaur o programa)
    // puts("\nCONFIGS:");
    // for(int i = 0; i < linhasConfig - 3; i++){
    //     printf("%d %c %.2f\n", k[i], tipoDistancia[i], coefMinkowski[i]);
    // }


    FILE *treino = fopen("iris/dataset/iris_treino.csv", "r");
    float **matrizTreino, *rotuloTreino;
    int linhasTreino, colunasTreino;

    textSize(treino, &colunasTreino, &linhasTreino);

    rotuloTreino = (float *) malloc(linhasTreino * sizeof(float));
    matrizTreino = (float **) malloc(linhasTreino * sizeof(float *));
    for(int i = 0; i < linhasTreino; i++){
        matrizTreino[i] = (float *) malloc(colunasTreino * sizeof(float));
    }
    
    transcribe(treino, matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *teste = fopen("iris/dataset/iris_teste.csv", "r");
    float **matrizTeste, *rotuloTeste;
    int colunasTeste, linhasTeste; 

    textSize(teste, &colunasTeste, &linhasTeste);

    rotuloTeste = (float *) malloc(linhasTeste * sizeof(float));
    matrizTeste = (float **) malloc(linhasTeste * sizeof(float *));
    for(int i = 0; i < linhasTeste; i++){
        matrizTeste[i] = (float *) malloc(colunasTeste * sizeof(float));
    }
    
    transcribe(teste, matrizTeste, rotuloTeste, colunasTeste, linhasTeste);

    // puts("\nTESTE:");
    // printaMatriz(matrizTeste, rotuloTeste, colunasTeste, linhasTeste);


    ///COMEÇO DO KNN

    struct distRot{ 
        float dist;
        float rotulo;
    };

    typedef struct distRot kneigh;

    kneigh **vizinho;

    vizinho = (kneigh **) malloc(linhasTeste * sizeof(kneigh*));
    for(int i = 0; i < linhasTeste; i++){
        vizinho[i] = (kneigh *) malloc(linhasTreino * sizeof(kneigh));
    }

    // //CALCULO DE DISTÂNCIA (EUCLIDES PARA FACILITAR OS TESTES)
    for(int aTst = 0; aTst < linhasTeste; aTst++){
        for(int aTrn = 0; aTrn < linhasTreino; aTrn ++){
            switch(tipoDistancia[2]){
                case 'E':
                    vizinho[aTst][aTrn].dist = euclidesVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino);
                    break;
                case 'C':
                    vizinho[aTst][aTrn].dist = chebyshevVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino);
                    break;
                case 'M':
                    vizinho[aTst][aTrn].dist = minkowskiVetor(matrizTeste[aTst],colunasTeste, matrizTreino[aTrn], colunasTreino, coefMinkowski[1]);
            }
            vizinho[aTst][aTrn].rotulo = rotuloTreino[aTrn];
        }
    }

    // for(int i = 0;  i < linhasTeste; i++){
    //     for(int j = 0; j < linhasTreino; j++){
    //         printf("%f ", ((vizinho[i][j]).dist)); 
    //     }
    //     puts("");
    // }

    // free temporário (remover ao continaur o programa)
    free(k);
    free(coefMinkowski);
    free(tipoDistancia);
    free(pathTreino);
    free(pathTeste);
    free(pathPredicoes);

    puts("");

    
    free(matrizTreino);
    free(rotuloTreino);
    free(matrizTeste);
    free(rotuloTeste);
    free(vizinho);
    puts("");
}