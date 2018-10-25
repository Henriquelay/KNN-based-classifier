/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_DISTANCIAS
#define _H_DISTANCIAS
/*Aqui vai as funcoes*/

float euclides(float, float);
float euclidesVetor(float*, float*);
float* euclidesMatrix(float**, float**);

float minkowski(float, float, float);
float minkowskiVetor(float*, float*, float);
float* minkowskiMatrix(float**, float**, float);

float produtoInterno(float*, float*);
float similaridadeCosseno(float*, float*);


/*Endif para evitar warnings*/
#endif