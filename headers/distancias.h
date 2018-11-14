/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_DISTANCIAS
#define _H_DISTANCIAS
/*Aqui vai as funcoes*/

float euclides(float*, float*);
float euclidesVetor(float*, int*, float*);

float minkowski(float*, float*, float*);
float minkowskiVetor(float*, int*, float*, float*);

float chernobylVetor(float**, int*, float**);

/*Endif para evitar warnings*/
#endif