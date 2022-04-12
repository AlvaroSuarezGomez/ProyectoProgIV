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

typedef struct 
{
    int codigo;
    char pais[100];

}Pais;

typedef struct 
{
    Pais* paises;
    int tamanyo;

}ListaPais;



int conectarBase(char base[],sqlite3* db);
int cargarAtletas(sqlite3 *db, ListaPersona* lper);
int cargarPais(sqlite3 *db,char paisSeleccionado);
void imprimirAtletas(ListaPersona lper);
void imprimirPais(ListaPais lpais);
int ensenarPaisesEnLaBD(sqlite3 *db,ListaPais* lpais);




#endif  /* _FUNCIONESBD_H_ */