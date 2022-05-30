#ifndef _MODALIDAD_H_
#define _MODALIDAD_H_

typedef struct 
{
    int cd_mod;
    char descripcion[200];
    char nom_modalidad [40];
}Modalidad;


typedef struct 
{
    int tamanyo;
    Modalidad* modalidades;
}ListaModalidades;


//int cargarModalidades(sqlite3 *db, ListaModalidades* lmod);
//int ainadirModalidad(sqlite3 *db, Modalidad modalidad);
//int deleteModalidad(sqlite3 *db, Modalidad modalidad);
//int actualizarModalidad(sqlite3 *db, Modalidad modalidad);
void imprimirModalidades(ListaModalidades lmod);

#endif