#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openfile.h"

struct Tamostra{
    int k;
    char tipoDistancia;
    float coefMinkowski;
};

struct Tpaths{
    char *pathTreino;
    char *pathTeste;
    char *pathPredicao;
};

Tpaths* novoPaths(char* treino, char* teste, char* predicoes){
    Tpaths* t = (Tpaths*) malloc(sizeof(Tpaths));
    t->pathTreino = (char*) malloc(strlen(treino) + sizeof(char));
    t->pathTeste = (char*) malloc(strlen(treino) + sizeof(char));
    t->pathPredicao = (char*) malloc(strlen(treino) + sizeof(char));

    strcpy(t->pathTreino, treino);
    strcpy(t->pathTeste, teste);
    strcpy(t->pathPredicao, predicoes);

    free(treino);
    free(teste);
    free(predicoes);

    return t;
}

char* returnPath(Tpaths path, int x){
    switch(x){
        case 1: 
            return path.pathTreino;
        case 2: 
            return path.pathTeste;
        case 3: 
            return path.pathPredicao;        
    }
    return NULL;
}

void printerAmostras(Tamostras *amostra){
        printf("K = %i\tTipoDistancia = %c\tCoefMinkowski = %f\n", amostra->k, amostra->tipoDistancia, amostra->coefMinkowski);
}

Tamostra* novaAmostra(int k, char tipoDistancia, float coefMinkowski){
    Tamostra* t = (Tamostra*) malloc(sizeof(Tamostra));

    t->k = k;
    t->tipoDistancia = tipoDistancia;
    t->coefMinkowski = coefMinkowski;
    return t;
}

//conta colunas e linhas para carregar os arquivos de dados
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
    rewind(arquivo);

    *colunas = c;
    *linhas = l;
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
void transcribe(FILE *arquivo, float **matrizAmostra, float *rotuloVet, int colunas, int linhas){
    for(int i = 0; !feof(arquivo); i++){
        for(int j = 0; j < colunas; j++){ 
            fscanf(arquivo, "%f,", &matrizAmostra[i][j]);
            if(j==(colunas-1)){
                fscanf(arquivo, "%f", &rotuloVet[i]);
            }
        }
    }
    rewind(arquivo);
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
    
    char *treinoTemp = (char*) malloc(sizeTreino * sizeof(char));
    char *testeTemp = (char*) malloc(sizeTeste * sizeof(char));
    char *predicaoTemp = (char*) malloc(sizePerdicao * sizeof(char));

    fgets(treinoTemp, sizeTreino, config);
    fgets(testeTemp, sizeTeste, config);
    fgets(predicaoTemp, sizePerdicao, config);

    strtok(treinoTemp, "\n");
    strtok(testeTemp, "\n");
    strtok(predicaoTemp, "\n");

    Tpaths *t = novoPaths(treinoTemp, testeTemp, predicaoTemp);

    return t;
}
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
    //Final da leitura de PATHs
    //início da leitura dos vetores
void setupAmostra(FILE *config, int nLinhasVetores, Tamostra **amostra){
    int k;
    char tipoDistancia;
    float coefMinkowski;


    for(int i = 0; i < nLinhasVetores; i++){
        fscanf(config, "%d, %c", &k, &tipoDistancia);
        if(tipoDistancia == 'M'){
            fscanf(config, ", %f\n", &coefMinkowski);
        }else{
            coefMinkowski = 0;
            fgetc(config);
        }

        amostra[i] = novaAmostra(k, tipoDistancia, coefMinkowski);
    }

    fclose(config);
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