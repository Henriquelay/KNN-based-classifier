#include <stdlib.h>
#include "../headers/knn.h"
#include "../headers/distancias.h"
#include "../headers/filemanager.h"

void knnDist(Kneigh ***MatrizNeighs, Data treino, Data teste, Tamostra amostra){

    Kneigh **vizinho;

    vizinho = (Kneigh **) malloc(teste.nlinhas * sizeof(Kneigh*));
    for(int i = 0; i < teste.nlinhas; i++){
        vizinho[i] = (Kneigh *) malloc(treino.nlinhas * sizeof(Kneigh));
    }

    //CALCULO DE DISTÂNCIA
    for(int aTst = 0; aTst < teste.nlinhas; aTst++){
        for(int aTrn = 0; aTrn < treino.nlinhas; aTrn ++){
            switch(amostra.tipoDistancia){
                case 'E':
                    vizinho[aTst][aTrn].dist = euclidesVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas);
                    break;
                case 'C':
                    vizinho[aTst][aTrn].dist = chebyshevVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas);
                    break;
                case 'M':
                    vizinho[aTst][aTrn].dist = minkowskiVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas, amostra.coefMinkowski);
            }
            vizinho[aTst][aTrn].rotulo = treino.rotulo[aTrn];
        }
    }
    *MatrizNeighs = vizinho;
}


//ORDENA O VETOR DE DISTANCIAS E ROTULOS BASEADO NAS DISTANCIAS
//IMPLEMENTADA COM A LÓGICA DO INSERTION SORT
void insortVetor(Kneigh *vetor, Kneigh **vizinhoSord, int sizeVetor){
    int n = 0;

    Kneigh *sorted;
    sorted = (Kneigh *) malloc(sizeof(Kneigh));

    for(int i = 0; i<sizeVetor; i++){
        if(n == 0){ //SE FOR O PRIMEIRO ELEMENTO, COLOCA NO INÍCIO DO VETOR
            sorted[n] = vetor[i];
            n++;            
        }else if (vetor[i].dist >= sorted[n-1].dist){ //SE FOR MAIOR, COLOCA NO FINAL DO VETOR
            sorted = (Kneigh *) realloc(sorted, (n+1) * sizeof(Kneigh));
            sorted[n] = vetor[i];
            n++;            
        }else{
            for(int c = 0; c<n; c++){
                if(vetor[i].dist <= sorted[c].dist){//cOMPARA COM OS ELEMENTOS JÁ ORDENADOS 
                    sorted = (Kneigh *) realloc(sorted, (n+1) * sizeof(Kneigh));
                    for(int z = n; z >c; z--){//SE FOR MENOR, CHEGA OS ELEMENTOS MAIORES PARA FRENTE
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
void takeKNN(Kneigh *vetorAmostra, int sizeVetor, int k, Kneigh **knnVetor){
    Kneigh *vizinhoSord;

    insortVetor(vetorAmostra, &vizinhoSord, sizeVetor);

    vizinhoSord = (Kneigh *) realloc(vizinhoSord, k * sizeof(Kneigh)); 


    *knnVetor = vizinhoSord;
}

//RETORNA O MAIOR ELEMENTO DE UM VETOR
//FOI DADO COMO FLOAT PARA SER USADO NOS RÓTULOS
float maxElem(float *vet, int size){
    float max;
    
    for(int i = 0; i < size; i++){
        if(i == 0){
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
float classifica(Kneigh *vetorKelem, int k, float maiorRotulo){
    int *ocorrenciasRot;  

    //CRIA UM VETOR DE NÚMERO DE OCORRÊNCIAS
    //ONDE CADA ÍNDICE CORRESPONDE A UM RÓTULO
    ocorrenciasRot = (int *)calloc(maiorRotulo+1, sizeof(int));
    
    for(int i = 0; i < k; i++){
        int rotuloAtual = vetorKelem[i].rotulo;
        ocorrenciasRot[rotuloAtual]++;
    }

    //PEGA O ÍNDICE DO MAIOR NÚMERO DO VETOR
    int maiorOcor;
    float rotuloDef;
    for(int i = 0; i <= maiorRotulo; i++){
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
void knn(float **classVet, float *maxRotulo, Data treino, Data teste, Tamostra amostra){    

    //CALCULANDO AS DISTÂNCIAS

    Kneigh **matrizVizinhos;
    knnDist(&matrizVizinhos, treino, teste, amostra);

    //CLASSIFICANDO TODAS AS AMOSTRAS

    float *amostrasClass;

    amostrasClass = (float *) malloc(teste.nlinhas * sizeof(float));

    float maiorRotulo = maxElem(treino.rotulo, treino.nlinhas);

    
    for(int i = 0; i < teste.nlinhas; i++){
        //PEGANDO OS K PRIMEIROS
        Kneigh *vetorKNN;

        takeKNN(matrizVizinhos[i], treino.nlinhas, amostra.k, &vetorKNN);

        // CLASSIFICA A AMOSTRA

        float rotulo = classifica(vetorKNN, amostra.k, maiorRotulo);

        amostrasClass[i] = rotulo;        
        free(vetorKNN);
    }

    *maxRotulo = maiorRotulo;
    *classVet = amostrasClass;
    free(matrizVizinhos);
}
