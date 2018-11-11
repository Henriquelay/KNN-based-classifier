#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


//Lê os arquivos de teste ou treino e guarda as informações em uma matriz
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
void setupConfig(FILE *config, char **pathTreino, char **pathTeste, char **pathPredicao, int **k, char **tipoDistancia, float **coefMinkowski, int *linhas){
    int nLinhas = countLinhas(config);
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
    *linhas = nLinhas;

    fclose(config);

}

// // MAIN PARA TESTES E DEBUG
// void main(){
//     FILE* saida = fopen("saida.txt", "w");

//     int maiorRotulo=5;

//     int matrizConfusa[(int)maiorRotulo+1][(int)maiorRotulo+1];

//     for(int i = 0; i<=maiorRotulo; i++){
//         for(int j = 0; j<=maiorRotulo; j++){
//             matrizConfusa[i][j] = 0;
//         }
//     }

//     printMatrizFile(saida,maiorRotulo+1, matrizConfusa);
    

// }

