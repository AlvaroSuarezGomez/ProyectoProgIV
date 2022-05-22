#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "pais.h"
#include "sqlite3.h"
#include "persona.h"



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
 

#endif  /* _FUNCIONESBD_H_ */