#include "ranking.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void imprimirRanking(Ranking ranking){
	for(int i = 0; i<ranking.tamanyo;i++){
		printf("%i- Nombre: %s    Lanzamiento: %f\n", i+1, ranking.compite[i].nomPer, ranking.compite[i].lanzamiento);

	}
}

