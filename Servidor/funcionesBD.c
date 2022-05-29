#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pais.h"
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

int crearTablas(sqlite3* db) {
	sqlite3_stmt *stmt;

	char sql1[] = "CREATE TABLE IF NOT EXISTS Pais (\
		Cd_Pais	INTEGER NOT NULL,\
		Nombre_Pais	TEXT NOT NULL,\
		PRIMARY KEY(Cd_Pais)\
	);";

	char sql2[] = "CREATE TABLE IF NOT EXISTS LUGAR (\
		CD_LUGAR	INTEGER NOT NULL,\
		NOM_LUGAR	TEXT,\
		LOC_LUGAR	TEXT,\
		CD_PAIS		INTEGER,\
		PRIMARY KEY(CD_LUGAR)\
	);";

	char sql3[] = "CREATE TABLE IF NOT EXISTS PERSONA (\
		DNI	TEXT NOT NULL,\
		Nombre	TEXT,\
		Telefono	INTEGER,\
		Cd_Pais	INTEGER,\
		PRIMARY KEY(DNI)\
	);";

	char sql4[] = "CREATE TABLE IF NOT EXISTS COMPETICION (\
		CD_COMPETICION	INTEGER NOT NULL,\
		CD_LUGAR	INTEGER,\
		ORGANIZADOR	TEXT,\
		NOM_COMPETICION	TEXT,\
		DIA	INTEGER,\
		MES	INTEGER,\
		ANO	INTEGER,\
		PRIMARY KEY(CD_COMPETICION)\
	);";

	char sql5[] = "CREATE TABLE IF NOT EXISTS MODALIDAD (\
		CD_MODALIDAD	INTEGER NOT NULL,\
		DESC_MODALIDAD	TEXT,\
		NOM_MODALIDAD	TEXT,\
		PRIMARY KEY(CD_MODALIDAD AUTOINCREMENT)\
	);";

	char sql6[] = "CREATE TABLE IF NOT EXISTS COMPITE (\
		DNI	TEXT NOT NULL,\
		CD_MODALIDAD	INTEGER NOT NULL,\
		CD_COMPETICION	INTEGER NOT NULL,\
		LANZAMIENTO	REAL\
	);";
	
	int result;
	result = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir pais\n");
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

	result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir lugar\n");
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

	result = sqlite3_prepare_v2(db, sql3, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
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

	result = sqlite3_prepare_v2(db, sql4, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir competicion\n");
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

	result = sqlite3_prepare_v2(db, sql5, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir modalidad\n");
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

	result = sqlite3_prepare_v2(db, sql6, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir ranking\n");
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
}


/*
int main(void){ Pruebas
	sqlite3 *db;
	Persona p;
	ListaPersona lista;
	p.cdPais = 2;
	strcpy(p.dni,"47258922V");
	strcpy(p.nombre,"Alvaro");
	p.telefono = 4312;
	int result = sqlite3_open("Basededatos.sqlite", &db);
	result = ainadirPersona(db,p);
	result = cargarAtletas(db,&lista);
	imprimirAtletas(lista);
}*/
