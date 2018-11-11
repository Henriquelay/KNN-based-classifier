#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filemanager.h"

void printMatrizFile(FILE *arq ,int size, int **matriz){
    fprintf(arq, "\n");
    for(int i = 0; i<size; i++){ //PRINTA A MATRIZ DE CONFUSÃO
        for(int j = 0; j<size; j++){
            fprintf(arq, "%d ", matriz[i][j]);
        }
        fprintf(arq, "\n");
    }
    fprintf(arq, "\n");
}

void printVetorFile(FILE *arq, int size, float *vet){
    for(int i = 0; i<size; i++){ //PRINTA AS PREDIÇÕES
        fprintf(arq, "%.f\n", vet[i]);
    }
}

//debug apenas. mostra os vetores dos arquivos de dados
void printaMatriz(float **matriz, float *iD, int nColunas, int nLinhas){
    for(int i = 0;  i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            printf("%.2f ", matriz[i][j]); 
        }
        printf("%.0f\n", iD[i]);
    }
}

//pega os dados dos datasets e passa para vetores no programa
void transcribe(FILE *arquivo, float ***matrizAmostra, float **rotuloVet, int *linhas, int *colunas){
    char junkChar;
    float **matriz;
    float *rotulo;
    int c = 0, l = 0;
    
    for(int i = 0; !feof(arquivo); i++){
        fscanf(arquivo, "%c", &junkChar);
        if(junkChar == ','){
            c++;
        }else if (junkChar == '\n'){
            break;
        }
    }
    rewind(arquivo);

    matriz = (float **) calloc(1, sizeof(float *));
    rotulo = (float *) calloc(1, sizeof(float));

    for(int i = 1; !feof(arquivo); i++){
        l++;
        rotulo = (float *) realloc(rotulo, (i)*sizeof(float));
        matriz = (float **) realloc(matriz, (i)*sizeof(float *));
        
        matriz[i-1] = (float *) calloc(c, sizeof(float));
        for(int j = 0; j<c; j++){
            fscanf(arquivo, "%f%c", &matriz[i-1][j], &junkChar);
        }
        fscanf(arquivo, "%f%c", &rotulo[i-1], &junkChar);
    }
    l--; //Os arquivos de teste e treino possui uma linha em branco no final do arquivo
    matriz = (float **) realloc(matriz, l*sizeof(float *));
    
    *linhas = l;
    *colunas = c;

    *matrizAmostra  = matriz;
    *rotuloVet = rotulo;

    fclose(arquivo);
}

int countLinhas(FILE *arquivo){
    int charAtual = 0, nLinhas = 1;

    while((charAtual = fgetc(arquivo)) != EOF)
        if(charAtual == 10) nLinhas++;

    rewind(arquivo);
    nLinhas--;  //pois o arquivo quebra linha mais uma vez antes do EOF
    return nLinhas;
}

//conta chars de uma linha especifica
int countChars(FILE *arquivo, int linha){
    int nLinhas = 1, nChars = 0, charAtual = 0;

    rewind(arquivo);

    while((charAtual = fgetc(arquivo)) != EOF){
        if(nLinhas == linha){
            nChars++;
            do{
                nChars++;
            }while((charAtual = getc(arquivo)) != 10);        //10 é \n em int
        }
        if(charAtual == 10) nLinhas++;
    }
    rewind(arquivo);
    return nChars;
}

//remove os \n que a função fgets pega nos vetores de PATH
void tiraQuebra(char *string){
    int tamanho = strlen(string);
    for(int i = 0; i < tamanho; i++){
        if(string[i] == '\n')
            string[i] = '\0';
            
    }
}

//pega os PATHs do config para vetores do programa
Tpaths* setupPaths(FILE *config){
    int sizeTreino = countChars(config, 1) + 1;
    int sizeTeste = countChars(config, 2) + 1;
    int sizePerdicao = countChars(config, 3) + 1;
    //+1 para ter espaço para o \n e \0 da string a ser inserida
    
    char treinoTemp[sizeTreino], testeTemp[sizeTeste], predicaoTemp[sizePerdicao];

    fgets(treinoTemp, sizeTreino, config);
    fgets(testeTemp, sizeTeste, config);
    fgets(predicaoTemp, sizePerdicao, config);

    strtok(treinoTemp, "\n");
    strtok(testeTemp, "\n");
    strtok(predicaoTemp, "\n");

    Tpaths *t = (Tpaths*) malloc(sizeof(Tpaths));

    t->pathTreino = (char*) malloc(strlen(treinoTemp) + sizeof(char));
    t->pathTeste = (char*) malloc(strlen(testeTemp) + sizeof(char));
    t->pathPredicao = (char*) malloc(strlen(predicaoTemp) + sizeof(char));

    strcpy(t->pathTreino, treinoTemp);
    strcpy(t->pathTeste, testeTemp);
    strcpy(t->pathPredicao, predicaoTemp);

    return t;
}
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
    //Final da leitura de PATHs
    //início da leitura dos vetores

Tamostra* setupAmostras(FILE *config, int linhasVetores){
    
    Tamostra *amostras = (Tamostra*) calloc(linhasVetores, sizeof(Tamostra));

    for(int i = 0; i < linhasVetores; i++){
        fscanf(config, "%d, %c", &(amostras[i]).k, &(amostras[i]).tipoDistancia);
        if((amostras[i]).tipoDistancia == 'M'){
            fscanf(config, ", %f\n", &(amostras[i]).coefMinkowski);
        }else{
            fgetc(config);
        }
    }

    fclose(config);
    return amostras;
}

// MAIN PARA TESTES E DEBUG
/*void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas = countLinhas(config), nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra **amostra = (Tamostra**) malloc(nLinhasVetores * sizeof(Tamostra*));

    setupAmostra(config, nLinhasVetores, amostra);

    printf("\tPATHS\nPath Treino = %s\nPath Testes = %s\nPath Perdicao = %s\n", paths->pathTreino, paths->pathTeste, paths->pathPredicao);

    printf("\n\tVETORES\n");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, amostra[i]->k, i, amostra[i]->tipoDistancia, i, amostra[i]->coefMinkowski);
    }

    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);
    for(int index = 0; index < nLinhasVetores; index++)
        free(amostra[index]);
    free(amostra);
}
*/