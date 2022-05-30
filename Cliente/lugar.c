#include "lugar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirLugares(ListaLugar llugar){
	for(int i = 0; i<llugar.tamanyo;i++){
		printf("%i- Codigo: %i    Nombre: %s    Localidad: %s    Pais: %s\n",i+1, llugar.lugar[i].Cd_Lugar, llugar.lugar[i].NOM_LUGAR, llugar.lugar[i].LOC_LUGAR, llugar.lugar[i].pais);

	}
}
