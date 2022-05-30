#include "competicion.h"
#include "pais.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void imprimirCompeticiones(ListaCompeticion lcomp){
	for(int i = 0; i<lcomp.tamanyo;i++){
		printf("%i- Codigo: %i    Lugar: %s    Organizador: %s    Nombre: %s    Fecha: %i/%i/%i\n",i+1, lcomp.competicion[i].CdCompeticion, lcomp.competicion[i].lugar, lcomp.competicion[i].organizador, lcomp.competicion[i].nomCompeticion, lcomp.competicion[i].dia, lcomp.competicion[i].mes, lcomp.competicion[i].ano);

	}
}

