#include <stdio.h>
#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"

void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, linhasConfig;
    float *coefMinkowski;
    char *tipoDistancia;
    char *pathTreino, *pathTeste, *pathPredicoes;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicoes, &k, &tipoDistancia, &coefMinkowski, &linhasConfig);

    puts("PATHS:");
    printf("%s\n", pathTreino);
    printf("%s\n", pathTeste);
    printf("%s\n", pathPredicoes);

    
    puts("\nCONFIGS:");
    for(int i = 0; i < linhasConfig - 3; i++){
        printf("%d %c %.2f\n", k[i], tipoDistancia[i], coefMinkowski[i]);
    }


    FILE *treino = fopen(pathTreino, "r");
    float **matrizTreino, *rotuloTreino;
    int linhasTreino, colunasTreino;

    if(treino == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(treino, &matrizTreino, &rotuloTreino, &linhasTreino, &colunasTreino);

    puts("\nTREINO:");
    printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *teste = fopen(pathTeste, "r");
    float **matrizTeste, *rotuloTeste;
    int linhasTeste, colunasTeste;

    if(teste == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(teste, &matrizTeste, &rotuloTeste, &linhasTeste, &colunasTeste);

    puts("\nTESTE:");
    printaMatriz(matrizTeste, rotuloTeste, colunasTeste, linhasTeste);

    // ///COMEÇO DO KNN

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

    // void knnDist(kneigh ***vizinho, char tipoDist, float coefMinkowski, int linhasTreino, int colunasTreino, int linhasTeste, int colunasTeste);

    // //CALCULO DE DISTÂNCIA
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


    for(int j = 0; j < linhasTreino; j++){
        for(int i = 0;  i < linhasTeste; i++){
            printf("%f ", ((vizinho[i][j]).dist)); 
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
    free(vizinho);
    puts("");
}