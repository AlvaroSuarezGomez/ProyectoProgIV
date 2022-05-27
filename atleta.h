#ifndef _ATLETA_H_
#define _ATLETA_H_
#include "sqlite3.h"

typedef struct{
    char dni[10];
    char nombre[20];
    int telefono;
    char pais[20];
    int cdPais;
}Persona;

typedef struct{
    int numero;
    Persona* persona;
}ListaPersona;

int cargarAtletas(sqlite3 *db, ListaPersona* lper, FILE* ficherolog);
int ainadirPersona(sqlite3 *db, Persona per);
int deletePersona(sqlite3* db, Persona per);
int actualizarPersona(sqlite3* db, Persona per);
void imprimirAtletas(ListaPersona lper);

#endif