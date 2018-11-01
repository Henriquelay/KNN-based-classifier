#include <stdio.h>
#include <stdlib.h>

void main(){
    FILE *arq = fopen("iris/dataset/iris_treino.csv", "r");
    char *teste;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    teste = malloc(100 * sizeof(char));

    for(int i = 0; !feof(arq); i++){
        fscanf(arq, "%c", &teste[i]);
        teste = realloc(teste, (i+2)*sizeof(char));
    }
    
    printf("%s", teste);
    free(teste);

    fclose(arq);
    
}
