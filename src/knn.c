#include <stdlib.h>
#include "../headers/knn.h"
#include "../headers/distancias.h"
#include "../headers/filemanager.h"

void knnDist(Kneigh ***MatrizNeighs, Data *treino, Data *teste, Tamostra *amostra){
    //prepara a matriz que vai receber as structs contendo distancia e rotulo
    Kneigh **vizinho;
    vizinho = (Kneigh**) malloc(teste->nlinhas * sizeof(Kneigh*));
    for(int i = 0; i < teste->nlinhas; i++){
        vizinho[i] = (Kneigh *) malloc(treino->nlinhas * sizeof(Kneigh));
    }

    //CALCULO DE DISTÂNCIA
    for(int amostraTeste = 0; amostraTeste < teste->nlinhas; amostraTeste++){
        for(int amostraTreino = 0; amostraTreino < treino->nlinhas; amostraTreino ++){
            switch(amostra->tipoDistancia){
                case 'E':
                    vizinho[amostraTeste][amostraTreino].dist = euclidesVetor(teste->matriz[amostraTeste], &teste->ncolunas, treino->matriz[amostraTreino]);
                    break;
                case 'C':
                    vizinho[amostraTeste][amostraTreino].dist = chernobylVetor(&teste->matriz[amostraTeste], &teste->ncolunas, &treino->matriz[amostraTreino], &treino->ncolunas);
                    break;
                case 'M':
                    vizinho[amostraTeste][amostraTreino].dist = minkowskiVetor(teste->matriz[amostraTeste], &teste->ncolunas, treino->matriz[amostraTreino], &treino->ncolunas, &amostra->coefMinkowski);
            }
            if(vizinho[amostraTeste][amostraTreino].dist == -1){
                printf("Ocorreu um erro ao calcular as distâncias!\n");
                exit(1);
            }
            vizinho[amostraTeste][amostraTreino].rotulo = treino->rotulo[amostraTreino];
        }
    }
    *MatrizNeighs = vizinho;
}


//ORDENA O VETOR DE DISTANCIAS E ROTULOS BASEADO NAS DISTANCIAS
//IMPLEMENTADA COM A LÓGICA DO INSERTION SORT
void insortVetor(Kneigh *vetor, Kneigh **vizinhoSord, int sizeVetor){
    int n = 0;

    Kneigh *sorted;
    sorted = (Kneigh*) malloc(sizeof(Kneigh));

    for(int i = 0; i < sizeVetor; i++){
        if(n == 0){ //SE FOR O PRIMEIRO ELEMENTO, COLOCA NO INÍCIO DO VETOR
            sorted[n] = vetor[i];
            n++;            
        }else if (vetor[i].dist >= sorted[n-1].dist){ //SE FOR MAIOR, COLOCA NO FINAL DO VETOR
            sorted = (Kneigh*) realloc(sorted, (n+1) * sizeof(Kneigh));
            sorted[n] = vetor[i];
            n++;            
        }else{
            for(int c = 0; c < n; c++){
                if(vetor[i].dist <= sorted[c].dist){//COMPARA COM OS ELEMENTOS JÁ ORDENADOS 
                    sorted = (Kneigh*) realloc(sorted, (n+1) * sizeof(Kneigh));
                    for(int z = n; z > c; z--){//SE FOR MENOR, CHEGA OS ELEMENTOS MAIORES PARA FRENTE
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

    //Ordena o vetor de distâncias
    insortVetor(vetorAmostra, &vizinhoSord, sizeVetor);
    //Trunca o tamanho do vetor no tamanho K
    vizinhoSord = (Kneigh*) realloc(vizinhoSord, k * sizeof(Kneigh)); 

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
    ocorrenciasRot = (int*) calloc(maiorRotulo+1, sizeof(int));
    
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

    free(ocorrenciasRot);
    return rotuloDef;
}

//CLASSIFICA UMA MATRIZ DE AMOSTRAS
void knn(float **classVet, float *maxRotulo, Data *treino, Data *teste, Tamostra *amostra){    

    //CALCULANDO AS DISTÂNCIAS
    Kneigh **matrizVizinhos;
    puts(">Calculando distâncias...");
    knnDist(&matrizVizinhos, treino, teste, amostra);

    //CLASSIFICANDO TODAS AS AMOSTRAS
    float *amostrasClass;
    amostrasClass = (float*) malloc(teste->nlinhas * sizeof(float));

    float maiorRotulo = maxElem(treino->rotulo, treino->nlinhas);

    puts(">Classificando amostras...");
    for(int i = 0; i < teste->nlinhas; i++){
        //PEGANDO OS K PRIMEIROS
        Kneigh *vetorKNN;

        takeKNN(matrizVizinhos[i], treino->nlinhas, amostra->k, &vetorKNN);

        // CLASSIFICA A AMOSTRA
        float rotulo = classifica(vetorKNN, amostra->k, maiorRotulo);

        amostrasClass[i] = rotulo;        
        free(vetorKNN);
    }

    *maxRotulo = maiorRotulo;
    *classVet = amostrasClass;
    
    for(int i = 0; i < teste->nlinhas; i++)
        free(matrizVizinhos[i]);
    free(matrizVizinhos);
}