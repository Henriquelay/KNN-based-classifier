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
    float **amostras;
    float *rotulo;
    int colunas, linhas;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    textSize(arq, &colunas, &linhas); //MEDE O TAMANHO DO ARQUIVO (FEATURESxAMOSTRAS)
    rewind(arq);
    printf("Colunas: %d\nLinhas: %d\n", colunas, linhas);

    amostras = (float **)malloc(linhas * sizeof(float *));

    for(int i = 0; i<linhas; i++){
        amostras[i] = (float *)malloc(colunas * sizeof(float));
    }

    rotulo = (float *)malloc(linhas * sizeof(float));

    //NÃO LÊ OS VALORES DIREITO
    for(int i = 0; !feof(arq); i++){
        for(int j = 0; j < colunas; j++){ 
            fscanf(arq, "%f,", &amostras[i][j]);
            if(j==(colunas-1)){
                fscanf(arq, "%f", &rotulo[i]);
            }
        }
    }
            
            
    //PRINTA A MATRIZ CORRETAMENTE
    for(int i = 0;  i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%.2f", amostras[i][j]); 
            printf(" ");
        }
        printf("%.0f", rotulo[i]);
        puts(" ");
    }

    free(amostras);
    free(rotulo);
    fclose(arq);
    printf("\n\n");
}