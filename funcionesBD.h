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
int ensenarAtletas(sqlite3 *db, ListaPersona* lper);
int ensenarPais(sqlite3 *db,char paisSeleccionado);
int ensenarPaisesEnLaBD(sqlite3 *db,Pais* paises,int* tamanyo);




#endif  /* _FUNCIONESBD_H_ */