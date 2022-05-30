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



void imprimirModalidades(ListaModalidades lmod);

#endif