#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"
typedef struct 
{
    int codigo;
    char pais[50];

}Pais;
typedef struct{
    char dni[9];
    char nombre[20];
    int telefono;
    char pais[20];
    int cdPais;
}Persona;

typedef struct{
    int numero;
    Persona* persona;
}ListaPersona;



typedef struct 
{
    Pais* paises;
    int tamanyo;

}ListaPais;


typedef struct 
{
    int cd_lan;
    float distancia;
}Lanzamiento;

typedef struct 
{
    int cd_mod;
    char descripcion[200];
    char nom_modalidad [40];
}Modalidad;

typedef struct 
{
    int cdC;
    char organizador[40];
    char nombre[100];                                                    
}Competicion;

typedef struct 
{
    Persona* personas;
    Modalidad* modalidades;
    Competicion* competicines;
    Lanzamiento* Lanzamiento;
}Ranking;//Tabla compite


int conectarBase(char base[],sqlite3* db);
int cargarAtletas(sqlite3 *db, ListaPersona* lper);
void imprimirAtletas(ListaPersona lper);
void imprimirPais(ListaPais lpais);
int cargarPaises(sqlite3 *db,ListaPais* lpais);
int ainadirPersona(sqlite3 *db, Persona per);



#endif  /* _FUNCIONESBD_H_ */