#include <stdio.h>
#include <stdlib.h>

void textSize(FILE *arquivo, int *colunas, int *linhas){
    char *texto;
    texto = (char *)malloc(sizeof(char));
    int c = 0, l = 0;

    for(int i = 0; !feof(arquivo); i++){
        fscanf(arquivo, "%c", &texto[i]);
        if(l==0){
            if(texto[i] == ','){
                c++;
            }
        }
        if(texto[i] == '\n'){
            l++;
        }
        texto = realloc(texto, (i+2)*sizeof(char));
    }
    
    free(texto);

    *colunas = c;
    *linhas = l;
}

void main(){
    FILE *arq = fopen("iris/dataset/iris_teste.csv", "r");
    float *feature, **amostra;
    int *rotulo;
    int c, l;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    textSize(arq, &c, &l);

    printf("Colunas: %d\nLinhas: %d\n", c, l);

    feature = (float *)malloc(c * sizeof(float));
    amostra = (float **)malloc(l * sizeof(float *));
    rotulo = (int *)malloc(l * sizeof(int));

    for(int i = 0; i<l; i++){
        for(int j = 0; j<l; j++){

        }
    }

    fclose(arq);



}
