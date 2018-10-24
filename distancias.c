/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
                                                                                                                                //linhas e colunas de treinamento mais tarde transformar em variavel global
float* euclidiana(float** featureTarget, int linhasTreinamento, int colunasTreinamento, float** featureTraining){                //deste cara, pegue estes mais proximos e use isso como base
        float acc = 0;
        float* resultado = (float*) malloc();                                                                                   //alocar espaço para matriz linha da resposta

        for(int i = 0; i < linhasTreinamento; i++, acc = 0){
                for(int j = 0; j < colunasTreinamento; j++)
                        acc += (featureTarget[i][j] - featureTraining[i][j]) * (featureTarget[i][j] - featureTraining[i][j]);
                
                resultado[i] = sqrt(acc);
        }

        return resultado;
}