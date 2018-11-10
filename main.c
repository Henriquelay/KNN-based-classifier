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


void insortVetor(kneigh *vetor, kneigh **vizinhoSord, int sizeVetor){
    int n = 0;

    kneigh *sorted;
    sorted = (kneigh *) malloc(sizeof(kneigh));

    for(int i = 0; i<sizeVetor; i++){
        if(n == 0){
            sorted[n] = vetor[i];
            n++;            
        }else if (vetor[i].dist >= sorted[n-1].dist){
            sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
            sorted[n] = vetor[i];
            n++;            
        }else{
            for(int c = 0; c<n; c++){
                if(vetor[i].dist <= sorted[c].dist){
                    sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
                    for(int z = n; z>c; z--){
                        sorted[z] = sorted[z-1];
                    }
                    sorted[c] = vetor[i];
                    n++;
                    break;
                }
            }
        }
    }

    *vizinhoSord = sorted;
}

void insortVetorRotulo(kneigh *vetor, kneigh **vizinhoSord, int sizeVetor){
    int n = 0;

    kneigh *sorted;
    sorted = (kneigh *) malloc(sizeof(kneigh));

    for(int i = 0; i<sizeVetor; i++){
        if(n == 0){
            sorted[n] = vetor[i];
            n++;            
        }else if (vetor[i].rotulo >= sorted[n-1].rotulo){
            sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
            sorted[n] = vetor[i];
            n++;            
        }else{
            for(int c = 0; c<n; c++){
                if(vetor[i].dist <= sorted[c].rotulo){
                    sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
                    for(int z = n; z>c; z--){
                        sorted[z] = sorted[z-1];
                    }
                    sorted[c] = vetor[i];
                    n++;
                    break;
                }
            }
        }
    }

    *vizinhoSord = sorted;
}

void takeKNN(kneigh *vetorAmostra, int sizeVetor, int k, kneigh **knnVetor){
    kneigh *vizinhoSord;

    insortVetor(vetorAmostra, &vizinhoSord, sizeVetor);

    vizinhoSord = (kneigh *) realloc(vizinhoSord, k * sizeof(kneigh));

    *knnVetor = vizinhoSord;
}




// vo mata o gafanhoto
void main(){
    FILE *config = fopen("iris/config.txt", "r");
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

    //CALCULANDO AS DISTÂNCIAS

    kneigh **matrizVizinhos;

    knnDist(&matrizVizinhos, matrizTreino, rotuloTreino, matrizTeste, tipoDistancia[2], coefMinkowski[2], linhasTreino, colunasTreino, linhasTeste, colunasTeste);



    //PEGANDO OS K PRIMEIROS

    kneigh *vetorKNN;

    takeKNN(matrizVizinhos[4], linhasTreino, k[2], &vetorKNN);

    

    // CLASSIFICA A AMOSTRA
    int *ocorrenciasRot;
    
    insortVetorRotulo(vetorKNN, &vetorKNN, k[2]);
    
    int maiorRotulo = vetorKNN[k[2] - 1].rotulo;

    ocorrenciasRot = (int *)calloc(maiorRotulo+1, sizeof(int));
    
    for(int i = 0; i<k[2]; i++){
        int rotuloAtual = vetorKNN[i].rotulo;
        ocorrenciasRot[rotuloAtual]++;
    }

    int maiorOcor;
    int rotuloMaior;
    for(int i = 0; i<=maiorRotulo; i++){
        if(i==0){
            maiorOcor = ocorrenciasRot[i];
            rotuloMaior = i;
        }else{
            if(ocorrenciasRot[i] > maiorOcor){
                maiorOcor = ocorrenciasRot[i];
                rotuloMaior = i;
            }
        }
    }

    printf("Rotulo: %d", rotuloMaior);

    

    // free temporário (remover ao continuar o programa)
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
    free(vetorKNN);
    puts("");
}