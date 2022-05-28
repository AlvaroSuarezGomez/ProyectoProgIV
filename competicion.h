#ifndef _COMPETICION_H_
#define _COMPETICION_H_
#include "sqlite3.h"

typedef struct
{
    int CdCompeticion;
    int CdLugar;
    char lugar[50];
    char organizador[50];
    char nomCompeticion[50];
    int dia;
    int mes;
    int ano;
}Competicion;

typedef struct
{
    int tamanyo;
    Competicion* competicion;
}ListaCompeticion;

int cargarCompeticiones(sqlite3 *db,ListaCompeticion* lcomp);
int ainadirCompeticion(sqlite3 *db, Competicion comp);
int deleteCompeticion(sqlite3 *db, Competicion comp);
int actualizarCompeticion(sqlite3 *db, Competicion comp);
void imprimirCompeticiones(ListaCompeticion lcomp);

#endif