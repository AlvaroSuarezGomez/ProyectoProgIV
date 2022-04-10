#include "funciones.h"
#include <stdio.h>
#include <string.h>

void limpiarLineas(char *texto, int capacidadaxima)
{
	if ((strlen(texto) == capacidadaxima-1) && (texto[capacidadaxima-2] != '\n'))
		while (getchar() != '\n');
}

char menuPrincipal(){
    printf("Elija lo que quiere hacer: \n");
    printf("    1-Seleccionar Atleta \n");
    printf("    2-Ver ranking por paises\n"); 
    printf("    3-Salir\n");
    printf("Seleccione opcion: \n");
    fflush(stdout);
	char linea[5];
	fgets(linea, 3, stdin);
	limpiarLineas(linea, 3);
	return *linea;
}

char menuPaises(){
    printf("Listado de paises: \n");
    printf("    1-Espania\n");
    printf("    2-Francia\n");
    printf("    3-Rusia\n");
    printf("    4-Italia\n");
    printf("    5-Volver\n");
    printf("Seleccione pais\n");
    fflush(stdout);
	char linea[5];
	fgets(linea, 5, stdin);
	limpiarLineas(linea, 5);
	return *linea;
}

void espaciosEntreMenus(){
    for (int i=0; i<101 ; i++){
        printf("\n");
    }
}



