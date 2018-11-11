#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"
#include "knn.h"

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

void insortvetorKelem(kneigh *vetor, kneigh **vizinhoSord, int sizeVetor){
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

float classifica(kneigh *vetorKelem, int k){
    int *ocorrenciasRot;
    
    insortvetorKelem(vetorKelem, &vetorKelem, k);
    
    int maiorRotulo = vetorKelem[k - 1].rotulo;

    ocorrenciasRot = (int *)calloc(maiorRotulo+1, sizeof(int));
    
    for(int i = 0; i<k; i++){
        int rotuloAtual = vetorKelem[i].rotulo;
        ocorrenciasRot[rotuloAtual]++;
    }

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




void knn(float **Class, float **matrizTreino, float *rotuloTreino, float **matrizTeste, float *rotuloTeste, char *tipoDist, 
        int *k, float *coefMinkowski, int linhasTreino, int colunasTreino, int linhasTeste, int colunasTeste){
        
        //CALCULANDO AS DISTÂNCIAS

    int c = 0; //SELECIONA A CONFIGURAÇÃO

    kneigh **matrizVizinhos;
    knnDist(&matrizVizinhos, matrizTreino, rotuloTreino, matrizTeste, tipoDist[c], coefMinkowski[c], linhasTreino, colunasTreino, linhasTeste, colunasTeste);

    //CLASSIFICANDO TODAS AS AMOSTRAS

    float *amostrasClass;

    amostrasClass = (float *) malloc(linhasTeste * sizeof(float));

    for(int i = 0; i<linhasTeste; i++){
        //PEGANDO OS K PRIMEIROS
        kneigh *vetorKNN;

        takeKNN(matrizVizinhos[i], linhasTreino, k[c], &vetorKNN);

        // CLASSIFICA A AMOSTRA

        float rotulo = classifica(vetorKNN, k[c]);

        amostrasClass[i] = rotulo;        
        free(vetorKNN);
    }

    printf("CLASSIFICAÇÃO ROTULO REAL\n");
    for(int i = 0; i<linhasTeste; i++){
        printf("     %.f          %.f\n", amostrasClass[i], rotuloTeste[i]);
    }

    free(matrizVizinhos);
}


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
    
    transcribe(treinoFile, &treino.matriz, &treino.rotulo, &treino.nlinhas, &treino.ncolunas);

    // puts("\nTREINO:");
    // printaMatriz(matrizTreino, rotuloTreino, colunasTreino, linhasTreino);

    FILE *testeFile = fopen(paths->pathTeste, "r");
    Data teste;

    if(testeFile == NULL){
        printf("Arquivo de treino não existe!");
        exit(1);
    }
    
    transcribe(testeFile, &teste.matriz, &teste.rotulo, &teste.nlinhas, &teste.ncolunas);

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
