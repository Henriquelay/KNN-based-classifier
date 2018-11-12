#include <stdlib.h>
#include <stdio.h>

//main para teste
void main(){
    char c;
    float r;
    float *target, *training, *resultado;
    int indexTarget, indexTraining;

    printf("Tamanho do vetor target: ");
    scanf(" %i", &indexTarget);

    printf("Tamanho do vetor training: ");
    scanf(" %i", &indexTraining);

    target = (float*) malloc(indexTarget * sizeof(float));
    training = (float*) malloc(indexTraining * sizeof(float));

    for(int i = 0; i < indexTarget; i++){
            printf("\nTarget[%i]: ", i);
            scanf(" %f", &target[i]);
    }
    for(int i = 0; i < indexTraining; i++){
            printf("\nTraining[%i]: ", i);
            scanf(" %f", &training[i]);
    }

    while(1){
    printf("\nM = Minkowski\tE = Euclides\tC = chernobyl\tQ = Quit\n>");
    scanf(" %c", &c);

    switch(c){
        case 'M':
        case 'm':
            printf("R: ");
            scanf(" %f", &r);
            printf("%f\n_______\n",minkowskiVetor(target, indexTarget, training, indexTraining, r));
        break;
        case 'E':
        case 'e':
            printf("%f\n_______\n",euclidesVetor(target, indexTarget, training, indexTraining));
        break;
        case 'C':
        case 'c':
            printf("%f\n_______\n",chernobylVetor(target, indexTarget, training, indexTraining));
        break;
        case 'Q':
        case 'q':
            free(target);
            free(training);
            return;
        }
    }
}