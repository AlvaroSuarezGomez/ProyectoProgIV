#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionesBD.h"
#include "pais.h"
#include "persona.h"
#include <conio.h>
#define CONTRASENA "admin"
#define BORRAR 8
#define ENTER 13
//gcc main.c funciones.c funcionesBD.c sqlite3.c -o aaa.exe
int main(void){
    char opcion;
    char opcionIntro;
    int fallo = 0;
    int acierto = 0;
    int maxFallo = 5;
    char contrasena[21];
    char encriptar;
   // int opcionIntro;
    sqlite3 *db;
   

    monstrarLogo();
    printf("Bienvenido/a");
    printf("\n");

    int result = sqlite3_open("Basededatos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    
    
    /*while(opcionIntro!=1 && opcionIntro!=2){  Opcion posible??
        printf("Es usted Admistrador o Usuario?\n");
        printf("   1-Administrador\n");
        printf("   2-Usuario\n");
        scanf("%i", &opcionIntro);*/


        opcionIntro = menuAdmin();
        switch (opcionIntro)
        {
            case '1':;
            {
                do{
                    int i = 0; 
                    system("cls");
                    printf("Contrasena: ");
                    
                    while(encriptar = getch()){
                        if(encriptar==ENTER){
                            contrasena[i] = '\0';
                            break;
                        }else if(encriptar==BORRAR){
                            i--;
                            printf("\b \b");
                        
                        }else{
                            printf("*");
                            contrasena[i]=encriptar;
                            i++;
                        }
                    }

                    
                    if(strcmp(CONTRASENA,contrasena)==0){
                        system("cls");
                        ListaPersona lper;
                        ListaPersona* lperp = &lper;
                        result = cargarAtletas(db, lperp); 
                         
                        menuPersona(lperp, db);
                        free(lperp);
                        lperp = NULL;
                        acierto++;
                    }else{
                        printf("\n");
                        printf("Contrasena incorrecta");
                        fallo++;
                        getchar();
                    }
                }while(acierto==0 && fallo<maxFallo);

                break;
            }
           
            case '2':;
            {   
                system("cls");
                do{
                    opcion = menuPrincipal();
                    switch (opcion){
                        case '1':;
                            system("cls");
                            ListaPersona lper;
                            ListaPersona* lperp = &lper;
                            result = cargarAtletas(db, lperp); 
                            imprimirAtletas(lper);
                        
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
                break;
            }
        }

    //}
    
    return 0;
}