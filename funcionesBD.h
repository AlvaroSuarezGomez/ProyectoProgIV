#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"

int ensenarAtletas(sqlite3 *db);
int ensenarPais(sqlite3 *db,char paisSeleccionado);


#endif  /* _FUNCIONESBD_H_ */