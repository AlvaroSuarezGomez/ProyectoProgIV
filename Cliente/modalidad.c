#include "modalidad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int cargarModalidades(sqlite3 *db, ListaModalidades* lmod){
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from modalidad ;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar las modalidades\n");
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


	char sql[] = "select CD_MODALIDAD, DESC_MODALIDAD, NOM_MODALIDAD from modalidad;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	lmod->tamanyo = (int) nfilas;
	lmod->modalidades = malloc(sizeof(Modalidad)*nfilas);

	int i = 0;
	result = sqlite3_step(stmt);
	do {
		if (result == SQLITE_ROW) {
			lmod->modalidades[i].cd_mod = sqlite3_column_int(stmt, 0);
			strcpy(lmod->modalidades[i].descripcion, (char *) sqlite3_column_text(stmt, 1));
			strcpy(lmod->modalidades[i].nom_modalidad, (char *) sqlite3_column_text(stmt, 2));
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

int ainadirModalidad(sqlite3 *db, Modalidad modalidad){
	
	sqlite3_stmt *stmt;

	char sql[250] = "insert into modalidad (CD_MODALIDAD,DESC_MODALIDAD,NOM_MODALIDAD) values (?, ?, ?)";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, modalidad.cd_mod);
	sqlite3_bind_text(stmt, 2, modalidad.descripcion, strlen(modalidad.descripcion), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, modalidad.nom_modalidad, strlen(modalidad.nom_modalidad), SQLITE_STATIC);

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

int deleteModalidad(sqlite3 *db, Modalidad modalidad){
	
	sqlite3_stmt *stmt;

	char sql[250] = "delete from modalidad where CD_MODALIDAD = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, modalidad.cd_mod);

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

	char sql2[250] = "delete from compite where CD_MODALIDAD = ?";
	
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, modalidad.cd_mod);

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

int actualizarModalidad(sqlite3 *db, Modalidad modalidad){
	
	sqlite3_stmt *stmt;

	char sql[250] = "update modalidad set DESC_MODALIDAD = ?, NOM_MODALIDAD = ? where CD_MODALIDAD = ?";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_text(stmt, 1, modalidad.descripcion, strlen(modalidad.descripcion), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 1, modalidad.nom_modalidad, strlen(modalidad.nom_modalidad), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, modalidad.cd_mod);

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

void imprimirModalidades(ListaModalidades lmod){
	for(int i = 0; i<lmod.tamanyo;i++){
		printf("%i- Codigo: %i    Nombre: %s    Descripcion: %s\n", i+1, lmod.modalidades[i].cd_mod, lmod.modalidades[i].nom_modalidad, lmod.modalidades[i].descripcion);
	}
}