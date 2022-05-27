#ifndef _RANKING_H_
#define _RANKING_H_
#include "sqlite3.h"

typedef struct 
{
    int cd_lan;
    float distancia;
}Lanzamiento;

typedef struct {
    char* dniPer;
    int codModalidad;
    int codCompeticion;
    double lanzamiento;
} Compite;

typedef struct {
    int tamanyo;
    Compite* compite;
} Ranking;


void imprimirRanking(Ranking ranking);
int cargarRanking(sqlite3 *db, Ranking* ranking);

#endif