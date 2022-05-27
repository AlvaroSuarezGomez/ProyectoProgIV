#include "atleta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"


int cargarAtletas(sqlite3 *db, ListaPersona* lper, FILE* ficherolog){
	ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "COMIENZO FUNCION CARGAR ATLETAS______________\n");
    fclose(ficherolog);
    sqlite3_stmt *stmt;
	char numeroFilas[] = "select count(*) from persona;";
	int result = sqlite3_prepare_v2(db, numeroFilas, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		ficherolog = fopen("logger.txt", "a");
        fprintf(ficherolog, "Error cargando Atletas 1\n");
		fprintf(ficherolog,"%s\n", sqlite3_errmsg(db));
        fclose(ficherolog);
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
		ficherolog = fopen("logger.txt", "a");
        fprintf(ficherolog, "Error finalizing statement (SELECT) 1\n");
		fprintf(ficherolog,"%s\n", sqlite3_errmsg(db));
        fclose(ficherolog);
		return result;
	}
	lper->numero = nfilas;
	char sql[] = "select A.DNI, A.Nombre, A.Telefono, B.Nombre_Pais, B.Cd_Pais from persona A, pais B where A.Cd_Pais = B.Cd_Pais;";
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		ficherolog = fopen("logger.txt", "a");
        fprintf(ficherolog, "Error cargando Atletas 2\n");
		fprintf(ficherolog,"%s\n", sqlite3_errmsg(db));
        fclose(ficherolog);
		return result;
	}
	
	int i = 0;
	lper->persona = malloc(sizeof(Persona)*nfilas);
	result = sqlite3_step(stmt) ;
	
	while (result == SQLITE_ROW) {
			strcpy(lper->persona[i].dni, (char *) sqlite3_column_text(stmt, 0));
			strcpy(lper->persona[i].nombre, (char *) sqlite3_column_text(stmt, 1));
			strcpy(lper->persona[i].pais, (char *) sqlite3_column_text(stmt, 3));
			lper->persona[i].telefono = sqlite3_column_int(stmt, 2);
			lper->persona[i].cdPais = sqlite3_column_int(stmt, 4);
			i++;
			result = sqlite3_step(stmt);
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		ficherolog = fopen("logger.txt", "a");
        fprintf(ficherolog, "Error finalizing statement (SELECT) 2\n");
		fprintf(ficherolog,"%s\n", sqlite3_errmsg(db));
        fclose(ficherolog);
		return result;
	}
	ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "FIN DE LA FUNCION_______________________________\n");
    fclose(ficherolog);
	//Apartir de aqui menu de persona probablemente valga la pena sacarlo a otra funcion
	
	return SQLITE_OK;
}

int ainadirPersona(sqlite3 *db, Persona per){
	
	sqlite3_stmt *stmt;



	char sql[250] = "insert into persona (DNI,Nombre,Telefono,Cd_Pais) values (?, ?, ?, ?)";
	
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

int deletePersona(sqlite3* db, Persona per)	{
	sqlite3_stmt *stmt;
	char sql[250] = "delete from persona where DNI = ?";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, per.dni, strlen(per.dni), SQLITE_STATIC);

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

int actualizarPersona(sqlite3* db, Persona per) {
	sqlite3_stmt *stmt;
	char sql[250] = "update persona set Nombre = ?, Telefono = ?, Cd_Pais = ? where DNI = ?", s;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, per.nombre, strlen(per.nombre), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, per.telefono);
	sqlite3_bind_int(stmt, 3, per.cdPais);
	sqlite3_bind_text(stmt, 4, per.dni, strlen(per.dni), SQLITE_STATIC);

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

void imprimirAtletas(ListaPersona lper){
	for(int i = 0; i<lper.numero;i++){
		printf("%i- Nombre: %s   Telefono:  %i   Pais: %s   DNI:  %s\n",i+1, lper.persona[i].nombre, lper.persona[i].telefono, lper.persona[i].pais, lper.persona[i].dni);

	}
}
