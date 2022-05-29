#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionesBD.h"
#include "pais.h"
#include <conio.h>
#include "atleta.h"
#include "pais.h"
#include "ranking.h"
#include "competicion.h"
#include "modalidad.h"
#define CONTRASENA "admin"
#define BORRAR 8
#define ENTER 13
//gcc main.c funciones.c funcionesBD.c sqlite3.c -o aaa.exe
int main(void){
    FILE* ficherolog;
    ficherolog = fopen("logger.txt", "w");
    fprintf(ficherolog, "Empezamos\n");
    fclose(ficherolog);
    ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "Comienzo de Programa:\n\n");
    fclose(ficherolog);
    char opcion;
    char opcionIntro;
    int fallo = 0;
    int acierto = 0;
    int maxFallo = 5;
    char contrasena[21];
    char encriptar;
    // int opcionIntro;
    
    sqlite3 *db;
    int result = sqlite3_open("Basededatos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    crearTablas(db);
    
    /*while(opcionIntro!=1 && opcionIntro!=2){  Opcion posible??
        printf("Es usted Admistrador o Usuario?\n");
        printf("   1-Administrador\n");
        printf("   2-Usuario\n");
        scanf("%i", &opcionIntro);*/


        opcionIntro = menuAdmin();
        ficherolog = fopen("logger.txt", "a");
        fprintf(ficherolog, "Se ha seleccionado la opcion %c(1- Admin 2- Usuario)\n", opcionIntro);
        fclose(ficherolog);
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
                            if (i == 0) continue;
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
                        result = cargarAtletas(db, &lper); 
                         
                        menuPrincipalAdmin(db);
                        free(lper.persona);
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
                    ficherolog = fopen("logger.txt", "a");
                    fprintf(ficherolog, "Menu principal mostrado y selecciona opcion %c\n", opcion);
                    fclose(ficherolog);
                    switch (opcion){
                        case '1':;
                            system("cls");
                            ficherolog = fopen("logger.txt", "a");
                            fprintf(ficherolog, "Comenzando carga de atletas...\n");
                            fclose(ficherolog); 
                            ListaPersona lper;
                            result = cargarAtletas(db, &lper); 
                            imprimirAtletas(lper);
                        
                            free(lper.persona);
                            break;
                        case '2': ;
                                system("cls");
                                Ranking rank;
                                char linea[3];

                                ListaPais lPais;
                                cargarPaises(db, &lPais);
                                imprimirPais(lPais);
                                int paisInt;
                                printf("Seleccione el pais: ");
                                fflush(stdout);
                                fgets(linea, 3, stdin);
                                sscanf(linea, "%i", &paisInt);

                                ListaCompeticion lComp;
                                cargarCompeticionesPorPais(db, &lComp, paisInt);
                                imprimirCompeticiones(lComp);
                                int competicionInt;
                                printf("Seleccione la competicion: ");
                                fflush(stdout);
                                fgets(linea, 3, stdin);
                                sscanf(linea, "%i", &competicionInt);

                                ListaModalidades lMod;
                                cargarModalidades(db, &lMod);
                                imprimirModalidades(lMod);
                                int modalidadInt;
                                printf("Seleccione la modalidad: ");
                                fflush(stdout);
                                fgets(linea, 3, stdin);
                                sscanf(linea, "%i", &modalidadInt);

                                cargarRanking(db, &rank, modalidadInt, competicionInt);
                                
                                imprimirRanking(rank);
                                free(rank.compite);
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
    
    sqlite3_close(db);
    return 0;
}