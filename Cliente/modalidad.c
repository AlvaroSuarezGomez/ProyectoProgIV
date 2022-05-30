#include "modalidad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void imprimirModalidades(ListaModalidades lmod){
	for(int i = 0; i<lmod.tamanyo;i++){
		printf("%i- Codigo: %i    Nombre: %s    Descripcion: %s\n", i+1, lmod.modalidades[i].cd_mod, lmod.modalidades[i].nom_modalidad, lmod.modalidades[i].descripcion);
	}
}