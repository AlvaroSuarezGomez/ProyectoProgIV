#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_
#include "funcionesBD.h"
char menuPrincipal();
char menuPaises();
char mostrarMenu();
char menuPersona(ListaPersona* lper, sqlite3 *db);
void cargarDatosPostu();
void monstrarLogo();


#endif  /* _FUNCIONES_H_ */