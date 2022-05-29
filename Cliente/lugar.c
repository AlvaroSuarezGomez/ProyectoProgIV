#include "lugar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cargarLugares(sqlite3 *db, ListaLugar* llugar){
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from lugar;";
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
	llugar->tamanyo = nfilas;
	char sql[] = "select A.CD_LUGAR, A.NOM_LUGAR, A.LOC_LUGAR, B.Nombre_Pais, B.Cd_Pais from lugar A, pais B where A.CD_PAIS = B.Cd_Pais;";
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al cargar los atletas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	
	int i = 0;
	llugar->lugar = malloc(sizeof(Lugar)*nfilas);
	result = sqlite3_step(stmt) ;
	
	while (result == SQLITE_ROW) {
			llugar->lugar[i].Cd_Lugar = sqlite3_column_int(stmt, 0);
			strcpy(llugar->lugar[i].NOM_LUGAR, (char *) sqlite3_column_text(stmt, 1));
			strcpy(llugar->lugar[i].LOC_LUGAR, (char *) sqlite3_column_text(stmt, 2));
			strcpy(llugar->lugar[i].pais, (char *) sqlite3_column_text(stmt, 3));
			llugar->lugar[i].Cd_Pais = sqlite3_column_int(stmt, 4);
			i++;
			result = sqlite3_step(stmt);
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

void imprimirLugares(ListaLugar llugar){
	for(int i = 0; i<llugar.tamanyo;i++){
		printf("%i- Codigo: %i    Nombre: %s    Localidad: %s    Pais: %s\n",i+1, llugar.lugar[i].Cd_Lugar, llugar.lugar[i].NOM_LUGAR, llugar.lugar[i].LOC_LUGAR, llugar.lugar[i].pais);

	}
}

int actualizarLugar(sqlite3 *db, Lugar lugar) {
	sqlite3_stmt *stmt;
	char sql[250] = "update lugar set NOM_LUGAR = ?, LOC_LUGAR = ?, CD_PAIS = ? where CD_LUGAR = ?", s;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, lugar.NOM_LUGAR,strlen(lugar.NOM_LUGAR),SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, lugar.LOC_LUGAR, strlen(lugar.LOC_LUGAR), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 3, lugar.Cd_Pais);
	sqlite3_bind_int(stmt, 4, lugar.Cd_Lugar);

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

int deleteLugar(sqlite3 *db, Lugar lugar)	{
	sqlite3_stmt *stmt;
	char sql[250] = "delete from lugar where CD_LUGAR = ?";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, lugar.Cd_Lugar);

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

int ainadirLugar(sqlite3 *db, Lugar lugar){
	
	sqlite3_stmt *stmt;



	char sql[250] = "insert into lugar (CD_LUGAR,NOM_LUGAR,LOC_LUGAR,CD_PAIS) values (?, ?, ?, ?)";
	
	int result;
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al introducir atleta\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_bind_int(stmt, 1, lugar.Cd_Lugar);
	sqlite3_bind_text(stmt, 2, lugar.NOM_LUGAR,strlen(lugar.NOM_LUGAR),SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, lugar.LOC_LUGAR, strlen(lugar.LOC_LUGAR), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, lugar.Cd_Pais);

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