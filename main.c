#include <stdio.h>
#include <stdlib.h>
#include "distancias.h"
#include "openfile.h"

void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas = countLinhas(config), nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra **amostra = (Tamostra**) malloc(nLinhasVetores * sizeof(Tamostra*));

    setupAmostra(config, nLinhasVetores, amostra);

    printf("\tPATHS\nPath Treino = %s\nPath Testes = %s\nPath Perdicao = %s\n", returnPath(*paths, 1), returnPath(*paths, 2), returnPath(*paths, 3);

    printf("\n\tVETORES\n");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, amostra[i]->k, i, amostra[i]->tipoDistancia, i, amostra[i]->coefMinkowski);
    }

    // free(paths->pathTreino);
    // free(paths->pathTeste);
    // free(paths->pathPredicao);
    // free(paths);
    // for(int index = 0; index < nLinhasVetores; index++)
    //     free(amostra[index]);
    // free(amostra);
}