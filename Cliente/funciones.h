#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

char menuAdmin();
char menuPrincipal();
char menuPaises();
char mostrarMenu();
void menuPrincipalAdmin(sqlite3* db);
char menuPersona(sqlite3 *db);
char menuPais(sqlite3 *db);
char menuCompeticiones(sqlite3* db);
char menuModalidades(sqlite3* db);
char menuLugares(sqlite3* db);
char menuRanking(sqlite3* db);
void cargarDatosPostu();
void monstrarLogo();
void limpiarFinales(char* str);


#endif  /* _FUNCIONES_H_ */