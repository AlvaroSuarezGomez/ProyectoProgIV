#include "atleta.h"
#include "pais.h"
#include "modalidad.h"
#include "competicion.h"
#include "lugar.h"
#include "ranking.h"

#ifndef _DESCONVERSOR_H_
#define _DESCONVERSOR_H_

void desconversorlcomp(ListaCompeticion* lcomp, char* frase);
void desconversorllug(ListaLugar* llug, char* frase);
void desconversorlmod(ListaModalidades* lmod, char* frase);
void desconversorlper(ListaPersona* lper, char* frase);
void desconversorlpais(ListaPais* lpais, char* frase);
void desconversorRanking(Ranking* rank, char* frase);

#endif