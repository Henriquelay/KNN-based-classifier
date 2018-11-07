#include "distancias.h"
#include "openfile.h"
#include <stdio.h>
#include <stdlib.h>

void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int *k, nLinhas = countLinhas(config);
    float *coefMinkowski;
    char *tipoDistancia;
    char *pathTreino, *pathTeste, *pathPredicoes;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicoes, &k, &tipoDistancia, &coefMinkowski, nLinhas);

    puts("PATHS:");
    printf("%s\n", pathTreino);
    printf("%s\n", pathTeste);
    printf("%s\n", pathPredicoes);

    puts("VETORES:");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, k[i], i, tipoDistancia[i], i, coefMinkowski[i]);
    }
    

    //free temporário (remover ao continaur o programa)
    free(k);
    free(coefMinkowski);
    free(tipoDistancia);
    free(pathTreino);
    free(pathTeste);
    free(pathPredicoes);

    puts("");

    
}