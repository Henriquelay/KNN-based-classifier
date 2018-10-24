/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//linhas e colunas de treinamento mais tarde transformar em variavel global
//deste cara (featureTarget), use isso como base (featureTraining), 
//a resposta será a distância entre o target e o treinamento OS OUTROS SAO INFORMAÇÕES NECESSARIAS, REMOVER FUTURAMENTE
float euclidiana(float featureTarget, float featureTraining){
    float resultado = sqrt((featureTarget - featureTraining) * (featureTarget - featureTraining));
    return resultado;
}

//implementa a distância euclidiana já como vetor
float* euclidianaVetor(float* featureTarget, float* featureTraining){
    float* resultado = (float*) malloc(sizeof(featureTarget);

    if(sizeof(featureTarget )!= sizeof(featureTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        return NULL;
    }

    for(int i = 0; i < sizeof(featureTarget), i++)
        resultado[i] = euclidiana(featureTarget[i], featureTraining[i]);
    
    return resultado;
}