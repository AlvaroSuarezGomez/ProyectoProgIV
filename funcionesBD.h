#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"

typedef struct{
    char dni[9];
    char nombre[20];
    int telefono;
    char pais[20];
}Persona;

typedef struct{
    int numero;
    Persona* persona;
}ListaPersona;

int conectarBase(char base[],sqlite3* db);
int ensenarAtletas(sqlite3 *db, ListaPersona* lper);
int ensenarPais(sqlite3 *db,char paisSeleccionado);




#endif  /* _FUNCIONESBD_H_ */