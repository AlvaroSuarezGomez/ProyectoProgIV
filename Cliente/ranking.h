#ifndef _RANKING_H_
#define _RANKING_H_


typedef struct 
{
    int cd_lan;
    float distancia;
}Lanzamiento;

typedef struct {
    char dniPer[10];
    char nomPer[50];
    char nomCompeticion[100];
    char nomModalidad[100];
    int codModalidad;
    int codCompeticion;
    double lanzamiento;
} Compite;

typedef struct {
    int tamanyo;
    Compite* compite;
} Ranking;


void imprimirRanking(Ranking ranking);


#endif