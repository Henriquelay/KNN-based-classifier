#include <stdio.h>
#include <stdlib.h>
#include "distancias.h"

struct distRot{ 
        float dist;
        float rotulo;
    };

typedef struct distRot kneigh;

//CALCULA As DISTANCIAS DE CADA AMOSTRA DO TESTE PARA TODAS AS AMOSTRAS DO TREINO
void knnDist(kneigh ***MatrizNeighs, float **matrizTreino, float *rotuloTreino, float **matrizTeste, 
    char tipoDist, float coefMinkowski, int linhasTreino, int colunasTreino, int linhasTeste, int colunasTeste){

    kneigh **vizinho;

    vizinho = (kneigh **) malloc(linhasTeste * sizeof(kneigh*));
    for(int i = 0; i < linhasTeste; i++){
        vizinho[i] = (kneigh *) malloc(linhasTreino * sizeof(kneigh));
    }

    //CALCULO DE DISTÂNCIA
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

//ORDENA O VETOR DE DISTANCIAS E ROTULOS BASEADO NAS DISTANCIAS
//IMPLEMENTADA COM A LÓGICA DO INSERTION SORT
void insortVetor(kneigh *vetor, kneigh **vizinhoSord, int sizeVetor){
    int n = 0;

    kneigh *sorted;
    sorted = (kneigh *) malloc(sizeof(kneigh));

    for(int i = 0; i<sizeVetor; i++){
        if(n == 0){ //SE FOR O PRIMEIRO ELEMENTO, COLOCA NO INÍCIO DO VETOR
            sorted[n] = vetor[i];
            n++;            
        }else if (vetor[i].dist >= sorted[n-1].dist){ //SE FOR MAIOR, COLOCA NO FINAL DO VETOR
            sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
            sorted[n] = vetor[i];
            n++;            
        }else{
            for(int c = 0; c<n; c++){
                if(vetor[i].dist <= sorted[c].dist){//cOMPARA COM OS ELEMENTOS JÁ ORDENADOS 
                    sorted = (kneigh *) realloc(sorted, (n+1) * sizeof(kneigh));
                    for(int z = n; z>c; z--){//SE FOR MENOR, CHEGA OS ELEMENTOS MAIORES PARA FRENTE
                        sorted[z] = sorted[z-1];//COLOCA NA POSIÇÃO z
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

//PEGA OS K PRIMEIROS DADO O VETOR DE ROTULOS E DISTANCIAS
void takeKNN(kneigh *vetorAmostra, int sizeVetor, int k, kneigh **knnVetor){
    kneigh *vizinhoSord;

    insortVetor(vetorAmostra, &vizinhoSord, sizeVetor);

    vizinhoSord = (kneigh *) realloc(vizinhoSord, k * sizeof(kneigh)); 


    *knnVetor = vizinhoSord;
}

//RETORNA O MAIOR ELEMENTO DE UM VETOR
//FOI DADO COMO FLOAT PARA SER USADO NOS RÓTULOS
float maxElem(float *vet, int size){
    float max;
    
    for(int i = 0; i<size; i++){
        if(i==0){
            max = vet[i];
        }else{
            if(vet[i] > max){
                max = vet[i];                
            }
        }
    }

    return max;
}

//CLASSIFICA A AMOSTRA COM BASE NO ROTULO COM MAIOR OCORRÊNCIA DENTRE OS K PRIMEIROS
float classifica(kneigh *vetorKelem, int k, float maiorRotulo){
    int *ocorrenciasRot;  

    //CRIA UM VETOR DE NÚMERO DE OCORRÊNCIAS
    //ONDE CADA ÍNDICE CORRESPONDE A UM RÓTULO
    ocorrenciasRot = (int *)calloc(maiorRotulo+1, sizeof(int));
    
    for(int i = 0; i<k; i++){
        int rotuloAtual = vetorKelem[i].rotulo;
        ocorrenciasRot[rotuloAtual]++;
    }

    //PEGA O ÍNDICE DO MAIOR NÚMERO DO VETOR
    int maiorOcor;
    float rotuloDef;
    for(int i = 0; i<=maiorRotulo; i++){
        if(i==0){
            maiorOcor = ocorrenciasRot[i];
            rotuloDef = i;
        }else{
            if(ocorrenciasRot[i] > maiorOcor){
                maiorOcor = ocorrenciasRot[i];
                rotuloDef = i;
            }
        }
    }

    return rotuloDef;

}

//CLASSIFICA UMA MATRIZ DE AMOSTRAS
void knn(float **classVet, float *maxRotulo, float **matrizTreino, float *rotuloTreino, float **matrizTeste, float *rotuloTeste, char tipoDist, 
        int k, float coefMinkowski, int linhasTreino, int colunasTreino, int linhasTeste, int colunasTeste){    

    //CALCULANDO AS DISTÂNCIAS

    kneigh **matrizVizinhos;
    knnDist(&matrizVizinhos, matrizTreino, rotuloTreino, matrizTeste, tipoDist, coefMinkowski, linhasTreino, colunasTreino, linhasTeste, colunasTeste);

    //CLASSIFICANDO TODAS AS AMOSTRAS

    float *amostrasClass;

    amostrasClass = (float *) malloc(linhasTeste * sizeof(float));

    float maiorRotulo = maxElem(rotuloTreino, linhasTreino);

    
    for(int i = 0; i<linhasTeste; i++){
        //PEGANDO OS K PRIMEIROS
        kneigh *vetorKNN;

        takeKNN(matrizVizinhos[i], linhasTreino, k, &vetorKNN);

        // CLASSIFICA A AMOSTRA

        float rotulo = classifica(vetorKNN, k, maiorRotulo);

        amostrasClass[i] = rotulo;        
        free(vetorKNN);
    }

    *maxRotulo = maiorRotulo;
    *classVet = amostrasClass;
    free(matrizVizinhos);
}
