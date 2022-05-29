#include "pais.h"
#include "atleta.h"
#include "lugar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

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

	int i = 0;
	result = sqlite3_step(stmt);
	do {
		if (result == SQLITE_ROW) {
			lpais->paises[i].codigo = sqlite3_column_int(stmt, 0);
			strcpy(lpais->paises[i].pais, (char *) sqlite3_column_text(stmt, 1));
			i++;
			result = sqlite3_step(stmt);
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

int ainadirPais(sqlite3 *db, Pais pais){
	
	sqlite3_stmt *stmt;

	char sql[250] = "insert into pais (Cd_Pais,Nombre_Pais) values (?, ?)";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, pais.codigo);
	sqlite3_bind_text(stmt, 2, pais.pais, strlen(pais.pais), SQLITE_STATIC);

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

int deletePais(sqlite3 *db, Pais pais){
	
	sqlite3_stmt *stmt;

	char sql[250] = "delete from pais where Cd_Pais = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	ListaPersona lper;
	ListaLugar llugar;
	cargarAtletas(db, &lper);
	cargarLugares(db, &llugar);
	for (int i = 0; i < lper.numero; i++) {
		if (pais.codigo == lper.persona[i].cdPais) {
			deletePersona(db, lper.persona[i]);
		}
	}
	for (int i = 0; i < llugar.tamanyo; i++) {
		if (pais.codigo == llugar.lugar[i].Cd_Pais) {
			deleteLugar(db, llugar.lugar[i]);
		}
	}
	free(lper.persona);
	free(llugar.lugar);

	sqlite3_bind_int(stmt, 1, pais.codigo);

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

int actualizarPais(sqlite3 *db, Pais pais){
	
	sqlite3_stmt *stmt;

	char sql[250] = "update pais set Nombre_Pais = ? where Cd_Pais = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_text(stmt, 1, pais.pais, strlen(pais.pais), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, pais.codigo);

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

void imprimirPais(ListaPais lpais){
	for(int i = 0; i<lpais.tamanyo;i++){
		printf("%i- Codigo: %i    Pais: %s\n", i+1, lpais.paises[i].codigo, lpais.paises[i].pais);
	}
}