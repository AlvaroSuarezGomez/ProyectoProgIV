#include "persona.h"
#include "pais.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cargarAtletas(sqlite3 *db, ListaPersona* lper){
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from persona;";
	
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	int nfilas;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			nfilas = sqlite3_column_int(stmt, 0);
		}
	} while (result == SQLITE_ROW);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	lper->numero = nfilas;

	char sql[] = "select A.DNI, A.Nombre, A.Telefono, B.Nombre_Pais, B.Cd_Pais from persona A, pais B where A.Cd_Pais = B.Cd_Pais;";
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
	int cdPais;
	int i = 0;
	lper->persona = malloc(sizeof(Persona)*nfilas);
	result = sqlite3_step(stmt) ;

	while (result == SQLITE_ROW) {
			strcpy(dni, (char *) sqlite3_column_text(stmt, 0));
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			nfilas = sqlite3_column_int(stmt, 2);
			telefono = sqlite3_column_int(stmt, 2);
			strcpy(nombrePais, (char *) sqlite3_column_text(stmt, 3));
            cdPais = sqlite3_column_int(stmt, 4);
			strcpy(lper->persona[i].dni, dni);
			strcpy(lper->persona[i].nombre, nombre);
			strcpy(lper->persona[i].pais, nombrePais);
			lper->persona[i].telefono = telefono;
			lper->persona[i].cdPais = cdPais;
			i++;
			if (result < nfilas) {
			result = sqlite3_step(stmt) ;
			}
	}
	//SE ROMPE AQUÍ
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	//Apartir de aqui menu de persona probablemente valga la pena sacarlo a otra funcion
	return SQLITE_OK;


}


void imprimirAtletas(ListaPersona lper){
	for(int i = 0; i<lper.numero;i++){
		printf("%i- Nombre: %s   Telefono:  %i   Pais: %s   DNI:  %s\n",i+1, lper.persona[i].nombre, lper.persona[i].telefono, lper.persona[i].pais, lper.persona[i].dni);

	}
}

int ainadirPersona(sqlite3 *db, Persona per){
	
	sqlite3_stmt *stmt;
	char sql[250] = "insert into persona (DNI,Nombre,Telefono,Cd_Pais) values (?,?,?,?);";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_text(stmt, 1, per.dni,strlen(per.dni),SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, per.nombre, strlen(per.nombre), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 3, per.telefono);
	sqlite3_bind_int(stmt, 4, per.cdPais);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return SQLITE_OK;
	
}
/*
int deletePersona(sqlite3* db, Persona per) {
	sqlite3_stmt *stmt;

	char sql[250] = "delete from persona where DNI =" + per.dni + ";";
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return SQLITE_OK;
}*/