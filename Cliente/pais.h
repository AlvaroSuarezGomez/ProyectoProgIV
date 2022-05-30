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
/*
int cargarPaises(sqlite3 *db,ListaPais* lpais);
int ainadirPais(sqlite3 *db, Pais pais);
int deletePais(sqlite3* db, Pais pais);
int actualizarPais(sqlite3* db, Pais pais);
*/
void imprimirPais(ListaPais lpais);


#endif