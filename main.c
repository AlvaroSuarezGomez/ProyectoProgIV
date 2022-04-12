#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionesBD.h"
//gcc main.c funciones.c funcionesBD.c sqlite3.c -o aaa.exe
int main(void){
    char opcion;
    char opcion2;
    sqlite3 *db;

    monstrarLogo();
    printf("Bienvenidos : ");
    printf("\n");

    int result = sqlite3_open("Basededatos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}

	
    do{
        opcion = menuPrincipal();
        switch (opcion){
            case '1':;
                system("cls");
                ListaPersona lper;
                ListaPersona* lperp = &lper;
                result = cargarAtletas(db, lperp); 
                printf("AaA");
                
                menuPersona(lperp, db);
                free(lperp);
                lperp = NULL;
                break;
            case '2': ;
                    system("cls");
                    ListaPais paises;
                    ListaPais* paisesp = &paises;
                    result = cargarPaises(db, paisesp);
                    imprimirPais(paises);
                break;
            case '3':
                system("cls");
                printf("Agur crack :)\n");
                break;
        }
        
    } while (opcion != '3');
    return 0;
}