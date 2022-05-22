#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _PERSONA_H_
#define _PERSONA_H_

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

int cargarAtletas(sqlite3 *db, ListaPersona* lper);
void imprimirAtletas(ListaPersona lper);
int ainadirPersona(sqlite3 *db, Persona per);
//int deletePersona(sqlite3* db, Persona per);

#endif