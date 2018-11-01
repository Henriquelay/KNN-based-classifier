#include <stdio.h>
#include <stdlib.h>

void main(){
    FILE *arq = fopen("iris/dataset/iris_treino.csv", "r");
    float *teste;
    int *c;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    //Colocando todos os valores em um único ponteiro
    teste = (float *)malloc(sizeof(float));
    c = (int *)malloc(sizeof(int));

    for(c[0] = 0; !feof(arq); c[0]++){
        fscanf(arq, "%f,", &teste[c[0]]);
        // printf("%d\n", i);
        teste = realloc(teste, (c[0]+2)*sizeof(float));
    }
    c[0] = c[0] - 1;
    printf("%d", c[0]);
    
    for(int i = 0; i<c[0]; i++){
        printf("%.2f ", teste[i]);
    }
    free(teste);

    fclose(arq);

    //Fazer uma função que coloque os valores de cada linha (ponteiro) em outro ponteiro (matriz

}
