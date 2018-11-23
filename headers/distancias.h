/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_DISTANCIAS
#define _H_DISTANCIAS
/*Aqui vai as funcoes*/
#include <stdlib.h>
#include <math.h>
#include "../headers/distancias.h"

float absF(float);

float euclidesVetor(float*, int*, float*);

float minkowskiVetor(float*, int*, float*, float);

float chernobylVetor(float*, int*, float*);

/*Endif para evitar warnings*/
#endif