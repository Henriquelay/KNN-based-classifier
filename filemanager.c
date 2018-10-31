#include <stdio.h>
#include <stdlib.h>

void main(){
    FILE *arq = fopen("iris/dataset/iris_treino.csv", "r");
    char teste[100];
    float x;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }
    
    fgets(teste, 100, arq);
    fclose(arq);

    printf("%s", teste);
    
}
