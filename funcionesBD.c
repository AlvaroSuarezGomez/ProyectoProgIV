#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int conectarBase(char base[],sqlite3 *db){
    int result = sqlite3_open(base, &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    printf("Base de datos conectada\n") ;
	return result;
}


int ensenarAtletas(sqlite3 *db, ListaPersona* lper){
    sqlite3_stmt *stmt;
	printf("Comienza\n");
	char numeroFilas[] = "select count(*) from persona;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	int nfilas;
	printf("Primera Parte\n");
	
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			nfilas = sqlite3_column_int(stmt, 0);
			printf("socorro\n");
		}
	} while (result == SQLITE_ROW);
	result = sqlite3_finalize(stmt);
	printf("Esperanza\n");
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	printf("FE %i\n", nfilas);
	lper->numero = nfilas;
	printf("Numero de filas calculado\n");

	char sql[] = "select A.DNI, A.Nombre, A.Telefono, B.Nombre_Pais from persona A, pais B where A.Cd_Pais = B.Cd_Pais;";
	printf("%s", sql);
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	char dni[9];
	char nombre[100];
	int telefono;
	char nombrePais[100];
	

	printf("\n");
	printf("\n");
	printf("Estos son los datos (Filas: %i):\n", nfilas);
	int i = 0;
	lper->persona = malloc(sizeof(Persona)*nfilas);
	result = sqlite3_step(stmt) ;
	while (result == SQLITE_ROW) {
		
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			strcpy(dni, (char *) sqlite3_column_text(stmt, 0));
			nfilas = sqlite3_column_int(stmt, 2);
			strcpy(nombrePais, (char *) sqlite3_column_text(stmt, 3));
            
			strcpy(lper->persona[i].dni, dni);
			strcpy(lper->persona[i].nombre, nombre);
			strcpy(lper->persona[i].pais, nombrePais);
			printf("%i- Nombre: %s   Pais: %s\n", i+1, lper->persona[i].nombre, lper->persona[i].pais);
			i++;
			if (result < nfilas) {
			result = sqlite3_step(stmt) ;
			}
	}
	printf("\n");
	printf("\n");
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	//Apartir de aqui menu de persona probablemente valga la pena sacarlo a otra funcion
	
	return SQLITE_OK;


}




int ensenarPais(sqlite3 *db,char paisSelecionado){
        sqlite3_stmt *stmt;

	char sql[100] = "select nombre, apellido,pais,fechaNacimiento from atleta WHERE pais=";
    strcat(sql,&paisSelecionado);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	
	char nombre[100];
    char apellido[100];
    char pais[50];
    char fechaNacimiento[20];


	printf("\n");
	printf("\n");
	printf("Estos son los atletas del %s :\n",paisSelecionado);
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 0));
			strcpy(apellido, (char *) sqlite3_column_text(stmt, 1));
			strcpy(pais, (char *) sqlite3_column_text(stmt, 2));
            strcpy(fechaNacimiento, (char *) sqlite3_column_text(stmt, 3));
            printf("Nombre: %s Apellido: %s fechaNacimiento: %s \n", nombre, apellido,fechaNacimiento);
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;
}

