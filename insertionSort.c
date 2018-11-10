#include <stdio.h>
#include <stdlib.h>

void printa(int *sort, int n){
    printf("Vetor ordenado: {");
for(int i = 0; i<n; i++){
    printf("%d ", sort[i]);
}
puts("}");
}

void insertionSort(float )

void main(){
    int vetor[10] = {5,2,3,7,6,9,1,10,45,12};
    int *sort;
    sort = (int *) malloc(sizeof(int));

    int n = 0;

    for(int i = 0; i<10; i++){
        if(n == 0){
            printf("1 - Adicionando %d na posição %d\n", vetor[i], n);
            sort[n] = vetor[i];
            n++;
            printa(sort, n);
        }else if (vetor[i] >= sort[n-1]){
            printf("2 - Adicionando %d na posição %d\n", vetor[i], n);
            sort = (int *) realloc(sort, (n+1) * sizeof(int));
            sort[n] = vetor[i];
            n++;
            printa(sort, n);
        }else{
            for(int c = 0; c<n; c++){
                if(vetor[i] <= sort[c]){
                    printf("3 - Adicionando %d na posição %d\n", vetor[i], c);
                    sort = (int *) realloc(sort, (n+1) * sizeof(int));
                    for(int z = n; z>c; z--){
                        sort[z] = sort[z-1];
                    }
                    sort[c] = vetor[i];
                    n++;
                    printa(sort, n);
                    break;
                }
            }
        }
    }   

free(sort);

}
