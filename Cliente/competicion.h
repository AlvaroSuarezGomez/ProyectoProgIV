#ifndef _COMPETICION_H_
#define _COMPETICION_H_
#include "pais.h"

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


void imprimirCompeticiones(ListaCompeticion lcomp);

#endif