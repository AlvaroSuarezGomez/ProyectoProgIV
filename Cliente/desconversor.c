#include "desconversor.h"
#include <string.h>
#include <stdlib.h>
#define TAMAINO_SENDBUFF 1024

void desconversorlpais(ListaPais* lpais, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
	//while(strcmp(stringLeft, '$')){
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lpais->tamanyo = atoi(temporal);
	lpais->paises = (Pais*) malloc(sizeof(Pais)*lpais->tamanyo);
	stringLeft++;
	for(int i = 0; i < lpais->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lpais->paises[i].codigo = atoi(temporal);

		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lpais->paises[i].pais, temporal);
		stringLeft++;
	}
	//lpais->tamanyo = (int) nfilas;
	//lpais->paises = (Pais*) malloc(sizeof(Pais)*nfilas);
	
}
//$numeroElementos&dni[0]$nombre[0]$telefono[1]$pais[0]$cdPais[0]&dni[1]$...$cdPais[numeroElementos -1]$

void desconversorlper(ListaPersona* lper, char* frase){
	char* stringLeft;
	char temporal[1024];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0; 
	strcpy(temporal, "");
	while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
	temporal[i] = '\0';
	lper ->numero = atoi(temporal);
	lper->persona = (Persona*) malloc(sizeof(Persona)*lper->numero);
	stringLeft++;
	for(int i = 0; i<lper->numero; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].dni, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].nombre, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		lper->persona[i].telefono = atoi(temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].pais, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		lper->persona[i].cdPais = atoi(temporal);
		stringLeft++;
    }
}

/*
void desconversorlmod(ListaModalidades* lmod, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lmod->tamanyo = atoi(temporal);
	lmod->modalidades = malloc(sizeof(Modalidad)*lmod->tamanyo);
	stringLeft++;
	for(int i = 0; i < lmod->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lmod->modalidades[i].cd_mod = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lmod->modalidades[i].descripcion, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lmod->modalidades[i].nom_modalidad, temporal);
		stringLeft++;
	}
}

void desconversorllug(ListaLugar* llug, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	llug->tamanyo = atoi(temporal);
	llug->lugar = malloc(sizeof(Lugar)*llug->tamanyo);
	stringLeft++;
	for(int i = 0; i < llug->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		llug->lugar[i].Cd_Lugar = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].NOM_LUGAR, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].LOC_LUGAR, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		llug->lugar[i].Cd_Pais = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].pais, temporal);
		stringLeft++;
	}
}

void desconversorlcomp(ListaCompeticion* lcomp, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lcomp->tamanyo = atoi(temporal);
	lcomp->competicion = malloc(sizeof(Competicion)*lcomp->tamanyo);
	stringLeft++;
	for(int i = 0; i < lcomp->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].CdCompeticion = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].CdLugar = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].lugar, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].organizador, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].nomCompeticion, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].dia = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].mes = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].ano = atoi(temporal);
		stringLeft++;
	}
}*/