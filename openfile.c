#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void setupConfig(FILE *config, char **pathTreino, char **pathTeste, char **pathPredicao, int **k, char **tipoDistancia, float **coefMinkowski, int nLinhas){
    int sizeTreino = countChars(config, 1) +1;
    int sizeTeste = countChars(config, 2) +1;
    int sizePerdicao = countChars(config, 3) +1;

    *pathTreino = (char*) malloc(sizeTreino * sizeof(char));
    *pathTeste = (char*) malloc(sizeTeste * sizeof(char));
    *pathPredicao = (char*) malloc(sizePerdicao * sizeof(char));
    
    fgets(*pathTreino, sizeTreino, config);
    fgets(*pathTeste, sizeTeste, config);
    fgets(*pathPredicao, sizePerdicao, config);

    tiraQuebra(*pathTreino);
    tiraQuebra(*pathTeste);
    tiraQuebra(*pathPredicao);;
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
    //Final da leitura de PATHs
    //início da leitura dos vetores
    int nAmostras = nLinhas - 3;    //pois as 3 primeiras são PATHs

    int *kVet = (int*) calloc(nAmostras, sizeof(int));
    char *tipoDistanciaVet = (char*) calloc(nAmostras, sizeof(char));
    float *coefMinkowskiVet = (float*) calloc(nAmostras, sizeof(float));


    for(int i = 0; i < nAmostras; i++){
        fscanf(config, "%d, %c", &kVet[i], &tipoDistanciaVet[i]);
        if(tipoDistanciaVet[i] == 'M'){
            fscanf(config, ", %f\n", &coefMinkowskiVet[i]);
        }else{
            fgetc(config);
        }
    }

    *k = kVet;
    *tipoDistancia = tipoDistanciaVet;
    *coefMinkowski = coefMinkowskiVet;

    fclose(config);
}

/* MAIN PARA TESTES E DEBUG
void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, nLinhas = countLinhas(config);
    char *pathTreino, *pathTeste, *pathPredicao;
    char *tipoDistancia;
    float *coepMinkowski;

    setupConfig(config, &pathTreino, &pathTeste, &pathPredicao, &k, &tipoDistancia, &coepMinkowski, nLinhas);

    printf("\tPATHS\nPath Treino = %s\nPath Testes = %s\nPath Perdicao = %s\n", pathTreino, pathTeste, pathPredicao);

    puts("");
    puts("VETORES");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, k[i], i, tipoDistancia[i], i, coepMinkowski[i]);
    }

    free(pathTreino);
    free(pathTeste);
    free(pathPredicao);
    free(k);
    free(tipoDistancia);
    free(coepMinkowski);
}

*/