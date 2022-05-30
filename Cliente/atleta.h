#ifndef _ATLETA_H_
#define _ATLETA_H_


typedef struct{
    char dni[10];
    char nombre[20];
    int telefono;
    char pais[20];
    int cdPais;
}Persona;

typedef struct{
    int numero;
    Persona* persona;
}ListaPersona;


void imprimirAtletas(ListaPersona lper);

#endif