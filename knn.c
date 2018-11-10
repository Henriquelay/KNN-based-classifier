#include <stdlib.h>
#include "knn.h"
#include "distancias.h"

void distancias(Kneigh ***MatrizNeighs, char tipoDist, float coefMinkowski, Data treino, Data teste){

    Kneigh **vizinho;

    vizinho = (Kneigh **) malloc(teste.nlinhas * sizeof(Kneigh*));
    for(int i = 0; i < teste.nlinhas; i++){
        vizinho[i] = (Kneigh *) malloc(treino.nlinhas * sizeof(Kneigh));
    }

    // //CALCULO DE DISTÂNCIA
    for(int aTst = 0; aTst < teste.nlinhas; aTst++){
        for(int aTrn = 0; aTrn < treino.nlinhas; aTrn ++){
            switch(tipoDist){
                case 'E':
                    vizinho[aTst][aTrn].dist = euclidesVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas);
                    break;
                case 'C':
                    vizinho[aTst][aTrn].dist = chebyshevVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas);
                    break;
                case 'M':
                    vizinho[aTst][aTrn].dist = minkowskiVetor(teste.matriz[aTst],teste.ncolunas, treino.matriz[aTrn], treino.ncolunas, coefMinkowski);
            }
            vizinho[aTst][aTrn].rotulo = treino.rotulo[aTrn];
        }
    }
    *MatrizNeighs = vizinho;
}
