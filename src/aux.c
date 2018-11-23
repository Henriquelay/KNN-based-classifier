/*              Esta biblioteca contém as funções
               que geram os dados de saída na main

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include "../headers/aux.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//printa o status da execução
void printarStatus(int *c, Tamostra *amostras){
        printf("-------CONFIGURAÇÃO Nº%d-------\n", *c+1);
        printf("K = %d ; DIST = %c ;", amostras[*c].k, amostras[*c].tipoDistancia);
        
        if(amostras[*c].tipoDistancia == 'M')
            printf(" COEF = %.1f ;", amostras[*c].coefMinkowski);
        puts("");
}


//PRODUZ O ARQUIVO .txt DE SAÍDA
void output(char **pathPredicao, int *c, float *acc, float **vetorClassificados, int ***matrizConfusa, char **jordana, float *maiorRotulo, int *nlinhas){

        sprintf(*jordana, "%spredicao_%i.txt", *pathPredicao, *c + 1);
        printf(">Arquivo de saída: %s\n", *jordana);

        FILE *predicao = fopen(*jordana, "w");

        if (predicao == NULL){
            printf("Erro na gravação dos resultados\n");
            printf("Pode ser que o diretório %s não exista.\n", *pathPredicao);
            exit(1);
        }

        fprintf(predicao, "%.2f\n", *acc); //PRINTA ACCURACY
        printMatrizFile(predicao, (int) *maiorRotulo, *matrizConfusa);
        printVetorFile(predicao, *nlinhas, *vetorClassificados);

        fclose(predicao);
}

//GERA A MATRIZ DE CONFUSÃO E CALCULA A ACCURACY
float geraConfusao(int ***matrizConfusa, Data *teste, float **vetorClassificados, float *maiorRotulo){
    int **matrizPerdida = (int**) calloc(*maiorRotulo+1, sizeof(int*));
    //calloc pois fazemos a confusão por incrementos
    for(int i = 0; i <= *maiorRotulo; i++){
        matrizPerdida[i] = (int*) calloc (*maiorRotulo+1, sizeof(int));
    }

    int acertos = 0;
    for(int i = 0; i < teste->nlinhas; i++){
        if((*vetorClassificados)[i] == teste->rotulo[i]) acertos++;
        matrizPerdida[((int) teste->rotulo[i])][((int) (*vetorClassificados)[i])]++;
    }
    *matrizConfusa = matrizPerdida;

    return ((float) acertos / (float) teste->nlinhas);
}

//CONTA A QUANTIDADE DE DIGITOS QUE UM NÚMERO OCUPA
int contaDigito(int num){
    int nDigitos = 1;
    while(num > 9){
        num = num % 10;
        nDigitos++;
    }
    return nDigitos;
}

void header(){
    puts("");
    printf("KKKKKKKKK    KKKKKKKNNNNNNNN        NNNNNNNNNNNNNNNN        NNNNNNNN\n");
    printf("K:::::::K    K:::::KN:::::::N       N::::::NN:::::::N       N::::::N\n");
    printf("K:::::::K    K:::::KN::::::::N      N::::::NN::::::::N      N::::::N\n");
    printf("K:::::::K   K::::::KN:::::::::N     N::::::NN:::::::::N     N::::::N\n");
    printf("KK::::::K  K:::::KKKN::::::::::N    N::::::NN::::::::::N    N::::::N\n");
    printf("  K:::::K K:::::K   N:::::::::::N   N::::::NN:::::::::::N   N::::::N\n");
    printf("  K::::::K:::::K    N:::::::N::::N  N::::::NN:::::::N::::N  N::::::N\n");
    printf("  K:::::::::::K     N::::::N N::::N N::::::NN::::::N N::::N N::::::N\n");
    printf("  K:::::::::::K     N::::::N  N::::N:::::::NN::::::N  N::::N:::::::N\n");
    printf("  K::::::K:::::K    N::::::N   N:::::::::::NN::::::N   N:::::::::::N\n");
    printf("  K:::::K K:::::K   N::::::N    N::::::::::NN::::::N    N::::::::::N\n");
    printf("KK::::::K  K:::::KKKN::::::N     N:::::::::NN::::::N     N:::::::::N\n");
    printf("K:::::::K   K::::::KN::::::N      N::::::::NN::::::N      N::::::::N\n");
    printf("K:::::::K    K:::::KN::::::N       N:::::::NN::::::N       N:::::::N\n");
    printf("K:::::::K    K:::::KN::::::N        N::::::NN::::::N        N::::::N\n");
    printf("KKKKKKKKK    KKKKKKKNNNNNNNN         NNNNNNNNNNNNNNN         NNNNNNN\n");
    puts("");
    puts("");

    puts("         |                              ____.......__");
    puts("         |\\      .'           _.--\"\"''``             ``''--._");
    puts("         | \\   .'/      ..--'`                             .-'`");
    puts("  .._    |  \\.' /  ..-''                                .-'");
    puts("   '.`'\"-:  '  .-'`                                  .-'");
    puts("     '.             __...----""\"\"\"\"\"\"\"\"--..             \\");
    puts("     -         ..-''                     ``""-.____      \\");
    puts("   .'  _.      \\                                  `\"-   \\");
    puts("  _.-'` |  /-.  \\                                    `-. \\");
    puts("        | /   `. \\                                      `.\\");
    puts("        |/      `-\\                                       `.");
    puts("        |");
    puts("");
    puts("");

    sleep(1);
}