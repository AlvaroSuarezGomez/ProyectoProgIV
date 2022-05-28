#include "competicion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

int cargarCompeticiones(sqlite3 *db,ListaCompeticion* lcomp){
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from competicion ;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar las competiciones\n");
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


	char sql[] = "select A.CD_COMPETICION, B.CD_LUGAR, B.NOM_LUGAR, A.ORGANIZADOR, A.NOM_COMPETICION, A.DIA, A.MES, A.ANO from competicion A, lugar B where A.CD_LUGAR = B.CD_LUGAR;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar las competiciones\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	lcomp->tamanyo = (int) nfilas;
	lcomp->competicion = (Competicion*) malloc(sizeof(Competicion)*nfilas);

	int i = 0;
	result = sqlite3_step(stmt);
	do {
		if (result == SQLITE_ROW) {
			lcomp->competicion[i].CdCompeticion = sqlite3_column_int(stmt, 0);
			lcomp->competicion[i].CdLugar = sqlite3_column_int(stmt, 1);
			strcpy(lcomp->competicion[i].lugar, sqlite3_column_text(stmt, 2));
			strcpy(lcomp->competicion[i].organizador, sqlite3_column_text(stmt, 3));
			strcpy(lcomp->competicion[i].nomCompeticion, sqlite3_column_text(stmt, 4));
			lcomp->competicion[i].dia = sqlite3_column_int(stmt, 5);
			lcomp->competicion[i].mes = sqlite3_column_int(stmt, 6);
			lcomp->competicion[i].ano = sqlite3_column_int(stmt, 7);
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

void imprimirCompeticiones(ListaCompeticion lcomp){
	for(int i = 0; i<lcomp.tamanyo;i++){
		printf("%i- Codigo: %i    Lugar: %s    Organizador: %s    Nombre: %s    Fecha: %i/%i/%i\n",i+1, lcomp.competicion[i].CdCompeticion, lcomp.competicion[i].lugar, lcomp.competicion[i].organizador, lcomp.competicion[i].nomCompeticion, lcomp.competicion[i].dia, lcomp.competicion[i].mes, lcomp.competicion[i].ano);

	}
}

int actualizarCompeticion(sqlite3 *db, Competicion comp){
	
	sqlite3_stmt *stmt;

	char sql[250] = "update competicion set CD_LUGAR = ?,ORGANIZADOR = ?,NOM_COMPETICION = ?,DIA = ?,MES = ?,ANO = ? where CD_COMPETICION = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, comp.CdLugar);
	sqlite3_bind_text(stmt, 2, comp.organizador, strlen(comp.organizador), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, comp.nomCompeticion, strlen(comp.nomCompeticion), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, comp.dia);
	sqlite3_bind_int(stmt, 5, comp.mes);
	sqlite3_bind_int(stmt, 6, comp.ano);
	sqlite3_bind_int(stmt, 7, comp.CdCompeticion);

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

int deleteCompeticion(sqlite3 *db, Competicion comp){
	
	sqlite3_stmt *stmt;

	char sql[250] = "delete from competicion where CD_COMPETICION = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, comp.CdCompeticion);

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

	char sql2[250] = "delete from compite where CD_COMPETICION = ?";
	
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, comp.CdCompeticion);

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

int ainadirCompeticion(sqlite3 *db, Competicion comp){
	
	sqlite3_stmt *stmt;

	char sql[250] = "insert into competicion (CD_COMPETICION,CD_LUGAR,ORGANIZADOR,NOM_COMPETICION,DIA,MES,ANO) values (?, ?, ?, ?, ?, ?, ?)";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, comp.CdCompeticion);
	sqlite3_bind_int(stmt, 2, comp.CdLugar);
	sqlite3_bind_text(stmt, 3, comp.organizador, strlen(comp.organizador), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, comp.nomCompeticion, strlen(comp.nomCompeticion), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, comp.dia);
	sqlite3_bind_int(stmt, 6, comp.mes);
	sqlite3_bind_int(stmt, 7, comp.ano);

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