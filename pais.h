#include "sqlite3.h"
#ifndef _PAIS_H_
#define _PAIS_H_

typedef struct 
{
    int codigo;
    char pais[50];

}Pais;
typedef struct 
{
    Pais* paises;
    int tamanyo;

}ListaPais;
int cargarPaises(sqlite3 *db,ListaPais* lpais);
void imprimirPais(ListaPais lpais);

#endif