#include <stdio.h>
#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"



void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas = countLinhas(config), nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra **amostra;

    puts("PATHS:");
    printf("%s\n", paths->pathTreino);
    printf("%s\n", paths->pathTeste);
    printf("%s\n", paths->pathPredicoes);

    puts("VETORES");
    for(int i = 0; i < nLinhasVetores; i++){
        printf("K[%i] = %i\t Distancia[%i] = %c\t CoefMinKowski[%i] = %f\n", i, amostra.k[i], i, amostra.tipoDistancia[i], i, amostra.coefMinkowski[i]);
    }
    
    for(int i = 0; i < nLinhasVetores; i++){

    }

}