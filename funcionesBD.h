#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "pais.h"
#include "sqlite3.h"

int conectarBase(char base[],sqlite3* db);
int crearTablas(sqlite3* db);

#endif  /* _FUNCIONESBD_H_ */