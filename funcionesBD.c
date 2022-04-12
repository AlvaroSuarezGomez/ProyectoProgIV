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
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	//Apartir de aqui menu de persona probablemente valga la pena sacarlo a otra funcion
	
	return SQLITE_OK;


}





int cargarPaises(sqlite3 *db,ListaPais* lpais){
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from pais ;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	int nfilas;
	
	do {
		result = sqlite3_step(stmt) ;
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


	char sql[] = "select Cd_Pais, Nombre_Pais from pais;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	lpais->tamanyo = (int) nfilas;
	lpais->paises = (Pais*) malloc(sizeof(Pais)*nfilas);

	printf("\n");
	printf("\n");
	int i = 0;

	int codigo;
	char nPais[100];
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			codigo = sqlite3_column_int(stmt, 0);
			strcpy(nPais, (char *) sqlite3_column_text(stmt, 1));
			lpais->paises[i].codigo = codigo;
			strcpy(lpais->paises[i].pais, nPais);
			i++;
		}

	} while (result == SQLITE_ROW);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	return SQLITE_OK;
}

void imprimirAtletas(ListaPersona lper){
	for(int i = 0; i<lper.numero;i++){
		printf("%i- Nombre: %s   Telefono:  %i   Pais: %s   DNI:  %s\n",i+1, lper.persona[i].nombre, lper.persona[i].telefono, lper.persona[i].pais, lper.persona[i].dni);

	}
}
void imprimirPais(ListaPais lpais){
	for(int i = 0; i<lpais.tamanyo;i++){
		printf("%i- Pais: %s\n", lpais.paises[i].codigo, lpais.paises[i].pais);
	}
}
int ainadirPersona(sqlite3 *db, Persona per){
	/*
	sqlite3_stmt *stmt;
	char sql[250] = "insert into persona persona (DNI,Nombre,Telefono,Cd_pais) values (";
	strcat(sql,per.dni);
	strcat(sql,", ");
	strcat(sql,per.nombre);
	strcat(sql,", ");
	strcat(sql,per.telefono);
	strcat(sql,", ");
	strcat(sql,STRING(per.cdPais));
	strcat(sql,");");
	printf("%s",sql);
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
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
	*/
}
