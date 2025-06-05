#include <stdio.h>
#include "MPT.h"
#include "MPV.h"

//Ordena vetores em ordem crescente
void ordenarVetor(int *vetor,int tamanho){
   for(int indiceFixo = 0;indiceFixo < tamanho;indiceFixo++){
      int aux = vetor[indiceFixo];
      for(int indice = indiceFixo + 1;indice < tamanho;indice++){
         if(vetor[indice] < aux){
            aux = vetor[indice];
            vetor[indice] = vetor[indiceFixo];
            vetor[indiceFixo] = aux;
         }
      }
   }
}