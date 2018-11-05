/* HEADER PARA A BIBLIOTECA FILEMANAGER */
#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER
/*Aqui vai as funcoes*/

void textSize(FILE*, int*, int*);
void printaMatriz(float**, float*, int, int);
void transcribe(FILE*, float**, float*, int, int);
int countLinhas(FILE*);
int countChars(FILE*, int);
void tiraQuebra(char*);
void configPaths(FILE*, char**, char**, char**);
void configKNN(FILE*, int**, char**, float**, int*);



/*Endif para evitar warnings*/
#endif