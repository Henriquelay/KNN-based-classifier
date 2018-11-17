/* HEADER PARA A BIBLIOTECA AUXILIAR */
#ifndef _H_AUX
#define _H_AUX
/*Aqui vai as funcoes*/
#include <stdlib.h>
#include <stdio.h>
#include "../headers/knn.h"

void output(char**, int*, float*, float**, int***, char**, float*, int*);
float geraConfusao(int***, Data*, float**, float*);
int contaDigito(int);
void header();

/*Endif para evitar warnings*/
#endif