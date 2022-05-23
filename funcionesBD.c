#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pais.h"
#include "persona.h"
#include "sqlite3.h"


int conectarBase(char base[],sqlite3 *db){
    int result = sqlite3_open(base, &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    printf("Base de datos conectada\n") ;
	return result;
}



/*
int main(void){ Pruebas
	sqlite3 *db;
	Persona p;
	ListaPersona lista;
	p.cdPais = 2;
	strcpy(p.dni,"4324321L");
	strcpy(p.nombre,"Lander");
	p.telefono = 4312;
	int result = sqlite3_open("Basededatos.sqlite", &db);
	result = ainadirPersona(db,p);
	result = cargarAtletas(db,&lista);
	imprimirAtletas(lista);
}*/
