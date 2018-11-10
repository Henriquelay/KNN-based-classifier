#include <stdio.h>
#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"

struct distRot{ 
        float dist;
        float rotulo;
    };

typedef struct distRot kneigh;


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




void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int *k, linhasConfig;
    float *coefMinkowski;
    char *tipoDistancia;
    char *pathTreino, *pathTeste, *pathPredicoes;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicoes, &k, &tipoDistancia, &coefMinkowski, &linhasConfig);

    // puts("PATHS:");
    // printf("%s\n", pathTreino);
    // printf("%s\n", pathTeste);
    // printf("%s\n", pathPredicoes);

    
    // puts("\nCONFIGS:");
    // for(int i = 0; i < linhasConfig - 3; i++){
    //     printf("%d %c %.2f\n", k[i], tipoDistancia[i], coefMinkowski[i]);
    // }


    FILE *treino = fopen(pathTreino, "r");
    float **matrizTreino, *rotuloTreino;
    int linhasTreino, colunasTreino;

    if(treino == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(treino, &matrizTreino, &rotuloTreino, &linhasTreino, &colunasTreino);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *teste = fopen(pathTeste, "r");
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



    // for(int i = 0;  i < linhasTeste; i++){
    //     for(int j = 0; j < linhasTreino; j++){
    //         printf("%.f ", ((matrizVizinhos[i][j]).dist)); 
    //     }
    //     puts("");
    // }

    //PEGANDO OS K PRIMEIROS

   

    kneigh *vizinhoSord;
    vizinhoSord = (kneigh *) malloc(linhasTreino * sizeof(kneigh));

    int n = 0;

    for(int i = 0; i<linhasTreino; i++){
        if(n == 0){
            vizinhoSord[n] = matrizVizinhos[0][i];
            n++;            
        }else if (matrizVizinhos[0][i].dist >= vizinhoSord[n-1].dist){
            vizinhoSord = (kneigh *) realloc(vizinhoSord, (n+1) * sizeof(kneigh));
            vizinhoSord[n] = matrizVizinhos[0][i];
            n++;            
        }else{
            for(int c = 0; c<n; c++){
                if(matrizVizinhos[0][i].dist <= vizinhoSord[c].dist){
                    vizinhoSord = (kneigh *) realloc(vizinhoSord, (n+1) * sizeof(kneigh));
                    for(int z = n; z>c; z--){
                        vizinhoSord[z] = vizinhoSord[z-1];
                    }
                    vizinhoSord[c] = matrizVizinhos[0][i];
                    n++;
                    break;
                }
            }
        }
    }

    for(int i = 0; i<linhasTreino; i++){
        printf("%f\n", vizinhoSord[i].dist);
    }


    vizinhoSord = (kneigh *) realloc(vizinhoSord, k[2] * sizeof(kneigh));

    printf("K primeiros: ");
    for(int i = 0; i<linhasTreino; i++){
        printf("%f ", vizinhoSord[i].dist);
    }
    puts("");
    

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
    free(vizinhoSord);
    puts("");
}