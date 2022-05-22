#include "pais.h"

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

void imprimirPais(ListaPais lpais){
	for(int i = 0; i<lpais.tamanyo;i++){
		printf("%i- Pais: %s\n", lpais.paises[i].codigo, lpais.paises[i].pais);
	}
}