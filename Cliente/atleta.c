#include "atleta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirAtletas(ListaPersona lper){
	for(int i = 0; i<lper.numero;i++){
		printf("%i- Nombre: %s   Telefono:  %i   Pais: %s   DNI:  %s\n",i+1, lper.persona[i].nombre, lper.persona[i].telefono, lper.persona[i].pais, lper.persona[i].dni);

	}
}
