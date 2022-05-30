#ifndef _LUGAR_H_
#define _LUGAR_H_

typedef struct 
{
    int Cd_Lugar;
    char NOM_LUGAR[50];
    char LOC_LUGAR[50];
    int Cd_Pais;
    char pais[20];
}Lugar;

typedef struct
{
    int tamanyo;
    Lugar* lugar;
}ListaLugar;

/*
int cargarLugares(sqlite3* db, ListaLugar* llugar);
int ainadirLugar(sqlite3 *db, Lugar lugar);
int deleteLugar(sqlite3 *db, Lugar lugar);
int actualizarLugar(sqlite3 *db, Lugar lugar);
*/
void imprimirLugares(ListaLugar llugar);

#endif
