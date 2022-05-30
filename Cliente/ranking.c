#include "ranking.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
int cargarRanking(sqlite3 *db, Ranking* ranking, int codModalidad, int codCompeticion) {
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(A.DNI) from compite A, competicion B, modalidad C where A.CD_MODALIDAD = C.CD_MODALIDAD and A.CD_COMPETICION = B.CD_COMPETICION and C.CD_MODALIDAD = ? and B.CD_COMPETICION = ?;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar el ranking\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	sqlite3_bind_int(stmt, 1, codModalidad);
	sqlite3_bind_int(stmt, 2, codCompeticion);

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

	char sql[] = "SELECT A.DNI, A.CD_MODALIDAD, A.CD_COMPETICION, A.LANZAMIENTO, D.NOMBRE FROM COMPITE A, COMPETICION B, MODALIDAD C, PERSONA D where A.CD_MODALIDAD = C.CD_MODALIDAD and A.CD_COMPETICION = B.CD_COMPETICION and A.DNI = D.DNI and A.CD_MODALIDAD = ? and A.CD_COMPETICION = ? ORDER BY A.LANZAMIENTO ASC;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar el ranking\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	sqlite3_bind_int(stmt, 1, codModalidad);
	sqlite3_bind_int(stmt, 2, codCompeticion);

	ranking->tamanyo = (int) nfilas;
	ranking->compite = (Compite*) malloc(sizeof(Compite)*nfilas);

	int i = 0;
	result = sqlite3_step(stmt);

	do {
		if (result == SQLITE_ROW) {
			strcpy(ranking->compite[i].dniPer, sqlite3_column_text(stmt, 0));
			ranking->compite[i].codModalidad = sqlite3_column_int(stmt, 1);
			ranking->compite[i].codCompeticion = sqlite3_column_int(stmt, 2);
			ranking->compite[i].lanzamiento = sqlite3_column_double(stmt, 3);
			strcpy(ranking->compite[i].nomPer, sqlite3_column_text(stmt, 4));
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
}*/

void imprimirRanking(Ranking ranking){
	for(int i = 0; i<ranking.tamanyo;i++){
		printf("%i- Nombre: %s    Lanzamiento: %f\n", i+1, ranking.compite[i].nomPer, ranking.compite[i].lanzamiento);

	}
}

/*
int ainadirCompetidor(sqlite3 *db, Compite comp){
	
	sqlite3_stmt *stmt;

	char sql[250] = "insert into compite (DNI, CD_MODALIDAD, CD_COMPETICION, LANZAMIENTO) values (?, ?, ?, ?)";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_text(stmt, 1, comp.dniPer, strlen(comp.dniPer), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, comp.codModalidad);
	sqlite3_bind_int(stmt, 3, comp.codCompeticion);
	sqlite3_bind_double(stmt, 4, comp.lanzamiento);

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

int deleteCompetidor(sqlite3 *db, Compite compite){
	
	sqlite3_stmt *stmt;

	char sql[250] = "delete from compite where DNI = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al eliminar competidor\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_text(stmt, 1, compite.dniPer, strlen(compite.dniPer), SQLITE_STATIC);

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

int actualizarCompetidor(sqlite3 *db, Compite compite){
	
	sqlite3_stmt *stmt;

	char sql[250] = "update compite set CD_MODALIDAD = ?, CD_COMPETICION = ?, LANZAMIENTO = ? where DNI = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al actualizar competidor\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	sqlite3_bind_int(stmt, 1, compite.codModalidad);
	sqlite3_bind_int(stmt, 2, compite.codCompeticion);
	sqlite3_bind_double(stmt, 3, compite.lanzamiento);
	sqlite3_bind_text(stmt, 4, compite.dniPer, strlen(compite.dniPer), SQLITE_STATIC);

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