/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_DISTANCIAS
#define _H_DISTANCIAS
/*Aqui vai as funcoes*/

float absF(float);

float euclides(float*, float*);
float euclidesVetor(float*, int*, float*);

float minkowskiVetor(float*, int*, float*, int*, float);

float chernobylVetor(float**, int*, float**, int*);

/*Endif para evitar warnings*/
#endif