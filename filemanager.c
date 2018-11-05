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
void configPaths(FILE *config, char **pathTreino, char **pathTeste, char **pathPredicao){

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
    tiraQuebra(*pathPredicao);

    printf("%s\n", *pathTreino);
    printf("%s\n", *pathTeste);
    printf("%s\n", *pathPredicao);
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
}

void configKNN(FILE *config, int **k, char **tipoDistancia, float **coefMinkowski, int nLinhas){
    int nAmostras = nLinhas - 3;    //pois as 3 primeiras são PATHs

    int *kVet = (int *) calloc(nAmostras, sizeof(int));
    char *tipoDistanciaVet = (char *) calloc(nAmostras, sizeof(char));
    float *coefMinkowskiVet = (float *) calloc(nAmostras, sizeof(float));


    for(int i = 0; i < nAmostras; i++){
        fscanf(config, "%d, %c", &kVet[i], &tipoDistanciaVet[i]);
        // printf("%d %c\n", kVet[i], tipoDistanciasVet[i]);
        if(tipoDistanciaVet[i] == 'M'){
            fscanf(config, ", %f\n", &coefMinkowskiVet[i]);
            // printf("%.2f\n", vetMinkowski[i]);
        }else{
            // printf("%p\n", &*coefMinkowski[i]);
            // *coefMinkowski[i] = 0.00;
            // printf("%.2f\n", vetMinkowski[i]);
            fgetc(config);
        }
    }


    for(int i = 0; i < nAmostras; i++){
    // //     k[i] = i;
        printf("Ktemp%i %i\n", i, kVet[i]);
    // //     tipoDistancia[i] = (char) i;
        printf("tipoDistanciaTemp%i %c\n", i, tipoDistanciaVet[i]);
    // //     coefMinkowski[i] = (float) i;
        printf("coefMinkowskiTemp%i %f\n", i, coefMinkowskiVet[i]);
    }
    
    *k = kVet;
    *tipoDistancia = tipoDistanciaVet;
    *coefMinkowski = coefMinkowskiVet;

}

 


// void configKNN(FILE *config, int **k, char **tipoDistancia, float **coefMinkowski, int nLinhas){
//     int nAmostras = nLinhas - 3;    //pois as 3 primeiras são PATHs

//     *k = (int *) calloc(nAmostras, sizeof(int));
//     *tipoDistancia = (char *) calloc(nAmostras, sizeof(char));
//     *coefMinkowski = (float *) calloc(nAmostras, sizeof(float));

//     for(int i = 0; i < 3; i++){
//         fscanf(config, "%d, %c", &*k[i], &*tipoDistancia[i]);
//         printf("%d %c\n", *k[i], *tipoDistancia[i]);
//         if(*tipoDistancia[i] == 'M'){
//             fscanf(config, ", %f\n", &*coefMinkowski[i]);
//             printf("%.2f\n", *coefMinkowski[i]);
//         }else{
//             // printf("%p\n", &*coefMinkowski[i]);
//             // *coefMinkowski[i] = 0.00;
//             printf("%.2f\n", *coefMinkowski[i]);
//             fgetc(config);
//         }
//     }
// }  


void main(){
    FILE *config = fopen("iris/config.txt", "r");
    int *k, nLinhas = countLinhas(config);
    char *pathTreino, *pathTeste, *pathPredicao, *tipoDistancia;
    float *coefMinkowski;
    

    if(config == NULL){
        printf("Deu bosta. Fechando.\n\n");
            exit(EXIT_FAILURE);
    }

    // printf("Numero de linhas = %i", countLines(config));

    configPaths(config, &pathTreino, &pathTeste, &pathPredicao);
    
    configKNN(config, &k, &tipoDistancia, &coefMinkowski, nLinhas);

    //preenche e printa os vetores de dados
    puts("Vetores de vdd");
    for(int i = 0; i < nLinhas - 3; i++){
    // //     k[i] = i;
        printf("K%i \t\t%i\n", i, k[i]);
    // //     tipoDistancia[i] = (char) i;
        printf("tipoDistancia%i \t %c\n", i, tipoDistancia[i]);
    // //     coefMinkowski[i] = (float) i;
        printf("coefMinkowski%i \t%.2f\n", i, coefMinkowski[i]);
    }

    free(k);
    free(tipoDistancia);
    free(coefMinkowski);
    // rewind(config);
    free(pathTeste);
    free(pathPredicao);
    free(pathTreino);
    fclose(config);
    


/*
    FILE *arq = fopen("vowels/dataset/vowels_teste.csv", "r");
    float **amostras;
    float *rotulo;
    int colunas, linhas;

    if (arq==NULL){
        printf("DEU MERDA");
        exit(1);
    }

    textSize(arq, &colunas, &linhas); //MEDE O TAMANHO DO ARQUIVO (FEATURESxAMOSTRAS)
    
    printf("Colunas: %d\nLinhas: %d\n", colunas, linhas);

    amostras = (float **)malloc(linhas * sizeof(float *));

    for(int i = 0; i<linhas; i++){
        amostras[i] = (float *)malloc(colunas * sizeof(float));
    }

    rotulo = (float *)malloc(linhas * sizeof(float));

    transcribe(arq, amostras, rotulo, colunas, linhas);
    printaMatriz(amostras, rotulo, colunas, linhas);


    free(amostras);
    free(rotulo);
    fclose(arq);
    printf("\n\n");
*/
}