#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"

int conectarBase(char base[],sqlite3* db);
int ensenarAtletas(sqlite3 *db);
int ensenarPais(sqlite3 *db,char paisSeleccionado);


#endif  /* _FUNCIONESBD_H_ */