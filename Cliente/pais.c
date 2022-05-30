#include "pais.h"
#include "atleta.h"
#include "lugar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void imprimirPais(ListaPais lpais){
	for(int i = 0; i<lpais.tamanyo;i++){
		printf("%i- Codigo: %i    Pais: %s\n", i+1, lpais.paises[i].codigo, lpais.paises[i].pais);
	}
}