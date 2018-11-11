/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_DISTANCIAS
#define _H_DISTANCIAS
/*Aqui vai as funcoes*/

float euclides(float, float);
float euclidesVetor(float*, int, float*, int);
float* euclidesMatrix(float**, int, int, float**, int, int);

float minkowski(float, float, float);
float minkowskiVetor(float*, int, float*, int, float);
float* minkowskiMatrix(float**, int, float**, int, float);

float chebyshevVetor(float*, int, float*, int);

// float produtoInterno(float*, int, float*, int);
// float similaridadeCosseno(float*, int, float*, int);


/*Endif para evitar warnings*/
#endif