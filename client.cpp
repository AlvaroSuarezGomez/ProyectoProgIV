#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "funciones.h"
#include "sqlite3.h"
#include "funcionesBD.h"
#include "pais.h"
#include "atleta.h"
#define CONTRASENA "admin"
#define BORRAR 8
#define ENTER 13

using namespace std;


int main(void) {

    char opcion;
    char opcionIntro;
    int fallo = 0;
    int acierto = 0;
    int maxFallo = 5;
    char contrasena[21];
    char encriptar;
    
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
                    cout<<"Contrasena: "<<endl;
                    
                    while(encriptar = getch()){
                        if(encriptar==ENTER){
                            contrasena[i] = '\0';
                            break;
                        }else if(encriptar==BORRAR){
                            if (i == 0) continue;
                            i--;
                            cout<<"\b \b"<<endl;
                        
                        }else{
                            cout<<"*"<<endl;
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
                        cout<<"\n"<<end;
                        cout<<"Contrasena incorrecta"<<endl;
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
                                ListaPais paises;
                                ListaPais* paisesp = &paises;
                                result = cargarPaises(db, paisesp);
                                imprimirPais(paises);
                            break;
                        case '3':
                            system("cls");
                            cout<<"Agur crack :)"<<"\n";
                            break;
                    }
                    
                } while (opcion != '3');
                break;
            }
        }

void menuPrincipalAdmin(sqlite3* db) {

    int opcionint=0;
    while(opcionint != 6){
        //system("cls");
        cout<<"\nElija lo que quiere hacer:"<<"\n";
        cout<<"    1-Gestionar atletas"<<"\n";
        cout<<"    2-Gestionar paises"<<"\n";
        cout<<"    3-Gestionar modalidades"<<"\n";
        cout<<"    4-Gestionar lugares"<<"\n";
        cout<<"    5-Gestionar competiciones"<<"\n";
        cout<<"    6-Salir"<<"\n";
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        cout<<"la opcion seleccionada es:"<<opcionint<<"\n";
        switch (opcionint)
        {
        case 1:;
            menuPersona(db);
            break;
        case 2:
            menuPais(db);
            break;
        case 3:
            menuModalidades(db);
        case 4:
            menuLugares(db);
            break;
        case 5:
            menuCompeticiones(db);
            break;
        case 6:;//SALIR
            break;
        default:
            cout<<"Caso no contemplado"<<"\n";
            break;
        }
    }

}

    char menuPersona(sqlite3 *db){
        ListaPais paises;
        ListaPersona lper;
        char newstr[20];
        char newnombre[20];
        int newtelefono;
        int newcdPais;
        char newdni[10];
        char newPais[20];
        int opcionint=0;
        while(opcionint != 3){
            cargarPaises(db, &paises);
            cargarAtletas(db, &lper);
            //system("cls");
            imprimirAtletas(lper);
            cout<<"\nElija lo que quiere hacer:"<< "\n";
            cout<<"    1-Seleccionar Atleta"<< "\n";
            cout<<"    2-Ainadir Atleta"<< "\n";
            cout<<"    3-Salir"<< "\n";
            fflush(stdout);
            char linea[3];
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            cout<<"la opcion seleccionada es:"<<opcionint<<"\n";
            switch (opcionint)
            {
            case 1:;
                int atletaint;
                cout<<"Seleccione el Atleta: "<<endl;
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &atletaint);
                atletaint--;


                int opcionedicion = 0;
                char nuevonombre[20];
                int telefono;
                int modificar = 0;
                while(opcionedicion!=5 && opcionedicion!=4){
                    modificar = 0;
                    system("cls");
                    cout<<"Los datos del atleta seleccionado son:"<<"\n";
                    printf("    Nombre: %s\n", lper.persona[atletaint].nombre);
                    printf("    DNI: %s\n", lper.persona[atletaint].dni);
                    printf("    Telefono: %i\n", lper.persona[atletaint].telefono);
                    printf("    Pais: %s\n\n", lper.persona[atletaint].pais);
                    cout<<"Elija lo que quiere hacer:"<<"\n";
                    cout<<"    1- Modificar Nombre"<<"\n";
                    cout<<"    2- Modificar Telefono"<<"\n";
                    cout<<"    3- Modificar Pais"<<"\n";
                    cout<<"    4- Eliminar este atleta"<<"\n";
                    cout<<"    5- SALIR"<<"\n";
                    cout<<"NOTA: No se puede modificar DNI si quiere cambiarlo elimine y añada al atleta de nuevo"<<"\n";
                    cout<<"Seleccione una opcion:"<<endl;
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &opcionedicion);
                    cout<<"la opcion seleccionada es:"<<opcionedicion<<"\n";
                    switch (opcionedicion)
                    {
                    case 1:;
                        strcpy(nuevonombre,"");
                        cout<<"Nuevo nombre: "<<endl;
                        fflush(stdout);
                        fgets(nuevonombre, 20, stdin);
                        fflush(stdin);
                        limpiarFinales(nuevonombre);
                        strcpy(lper.persona[atletaint].nombre, nuevonombre);
                        modificar = 1;
                        
                        break;
                    case 2:;
                        strcpy(nuevonombre,"");
                        cout<<"Nuevo telefono: "<<endl;
                        fflush(stdout);
                        fgets(nuevonombre, 8, stdin);
                        fflush(stdin);
                        limpiarFinales(nuevonombre);
                        telefono = atoi(nuevonombre);
                        lper.persona[atletaint].telefono = telefono;
                        modificar = 1;
                        break;
                    case 3:;
                        
                        imprimirPais(paises);
                        strcpy(nuevonombre,"");
                        cout<<"Nuevo Pais(Numero): "<<endl;
                        fflush(stdout);
                        fgets(nuevonombre, 20, stdin);
                        fflush(stdin);
                        limpiarFinales(nuevonombre);
                        telefono = atoi(nuevonombre);
                        for(int i = 0; i<paises.tamanyo;i++){
                            if(paises.paises[i].codigo == telefono){
                                strcpy(lper.persona[atletaint].pais, paises.paises[i].pais);
                                lper.persona[atletaint].cdPais = telefono;
                                modificar = 1;
                            }
                        }
                        break;
                    case 4:;
                        deletePersona(db, lper.persona[atletaint]);
                        
                        break;
                    default:
                        break;
                    }
                    if(modificar == 1){
                        actualizarPersona(db, lper.persona[atletaint]);
                    }


                }
                

                break;
            case 2:;//Ainadir atleta
                Persona personaNUeva;

                strcpy(newnombre, "");
                newtelefono = 0;
                newcdPais = 0;
                strcpy(newdni, "");
                strcpy(newPais, "");

                cout<<"Seleccione nuevo dni(8 numeros y una letra):"<<endl;
                fflush(stdout);
                fgets(newdni, 10, stdin);
                fflush(stdin);
                limpiarFinales(newdni);
                strcpy(personaNUeva.dni,newdni);

                cout<<"Seleccione nuevo nombre:"<<endl;
                fflush(stdout);
                fgets(newnombre, 20, stdin);
                fflush(stdin);
                limpiarFinales(newnombre);
                strcpy(personaNUeva.nombre,newnombre);

                cout<<"Seleccione nuevo telefono: "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &newtelefono);

                char *p = malloc(sizeof(char)*20);
                imprimirPais(paises);
                cout<<"Nuevo Pais(Numero): "<<endl;
                fflush(stdout);
                fgets(p, 20, stdin);
                fflush(stdin);
                sscanf(p, "%i", &newcdPais);
                cout<< newcdPais<<"\n";
                newcdPais--;
                if (newcdPais < 0 || newcdPais >= paises.tamanyo) {
                    cout<<"No has elegido un pais valido"<<"\n";
                    break;
                }

                cout<<"Se ha introducido correctamente"<<"\n";

                
                personaNUeva.telefono = newtelefono;
                personaNUeva.cdPais = paises.paises[newcdPais].codigo;
                ainadirPersona(db,personaNUeva);
                free(lper.persona);
                cargarAtletas(db, &lper);
                break;
            case 3:;//SALIR
                break;
            default:
                cout<<"Caso no contemplado"<<"\n";
                break;
            }
            free(lper.persona);
            free(paises.paises);
        }
    }

    char menuPais(sqlite3 *db){
        ListaPais paises;
        char newstr[50];
        int opcionint=0;
        while(opcionint != 3){
            cargarPaises(db, &paises);
            //system("cls");
            imprimirPais(paises);
            cout<<"\nElija lo que quiere hacer:"<< "\n";
            cout<<"    1-Seleccionar Pais"<< "\n";
            cout<<"    2-Ainadir Pais"<< "\n";
            cout<<"    3-Salir"<< "\n";
            fflush(stdout);
            char linea[3];
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            cout<<"la opcion seleccionada es:"<<opcionint<<"\n";
            switch (opcionint)
            {
            case 1:;
                int paisint;
                cout<<"Seleccione el Pais: "<<endl;
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &paisint);
                paisint--;


                int opcionedicion = 0;
                int modificar = 0;
                while(opcionedicion!=3 && opcionedicion!=2){
                    modificar = 0;
                    system("cls");
                    cout<<"Los datos del pais seleccionado son:"<<"\n";
                    printf("    Codigo: %i\n", paises.paises[paisint].codigo);
                    printf("    Nombre: %s\n", paises.paises[paisint].pais);
                    cout<<"Elija lo que quiere hacer:"<<"\n";
                    cout<<"    1- Modificar Nombre"<<"\n";
                    cout<<"    2- Eliminar este pais"<<"\n";
                    cout<<"    3- SALIR"<<"\n";
                    cout<<"NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada el pais de nuevo"<<"\n";
                    cout<<"Seleccione una opcion:"<<endl;
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &opcionedicion);
                    cout<<"la opcion seleccionada es:"<<opcionedicion<<"\n";

                    switch (opcionedicion)
                    {
                    case 1:;
                        strcpy(newstr,"");
                        cout<<"Nuevo nombre: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 20, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(paises.paises[paisint].pais, newstr);
                        modificar = 1;
                        
                        break;
                    case 2:;
                        deletePais(db, paises.paises[paisint]);
                        break;

                    default:
                        break;
                    }
                    if(modificar == 0){
                        actualizarPais(db, paises.paises[paisint]);
                    }


                }
                
                break;
            case 2:;//Ainadir pais
                Pais paisNuevo;

                cout<<"Seleccione nuevo codigo(numeros): "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &paisNuevo.codigo);

                cout<<"Seleccione nuevo nombre: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(paisNuevo.pais, newstr);

                
                ainadirPais(db, paisNuevo);
                free(paises.paises);
                cargarPaises(db, &paises);
                break;
            case 3:;//SALIR
                break;
            default:
                cout<<"Caso no contemplado"<<"\n";
                break;
            }
            free(paises.paises);
        }
    }

    char menuCompeticiones(sqlite3 *db) {
        ListaCompeticion lcomp;
        char newstr[200];
        int opcionint = 0;
        while (opcionint != 3) {
            cargarCompeticiones(db, &lcomp);
            //system("cls");
            imprimirCompeticiones(lcomp);
            cout<<"\nElija lo que quiere hacer:"<< "\n";
            cout<<"    1-Seleccionar Competicion"<< "\n";
            cout<<"    2-Ainadir Competicion"<< "\n";
            cout<<"    3-Salir "<<"\n";
            fflush(stdout);
            char linea[3];
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            cout<<"La opcion seleccionada es:"<<opcionint<<"\n";

            switch (opcionint)
            {
            case 1:;
                int competicionInt;
                cout<<"Seleccione la competición: "<<endl;
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &competicionInt);
                competicionInt--;

                int opcionEdicion = 0;
                int modificar = 0;

                while (opcionEdicion != 4 && opcionEdicion != 5)
                {
                    modificar = 0;
                    system("cls");
                    cout<<"Los datos de la competicion seleccionada son:"<<"\n";
                    printf("    Codigo:      %i\n", lcomp.competicion[competicionInt].CdCompeticion);
                    printf("    Lugar:      %s\n", lcomp.competicion[competicionInt].lugar);
                    printf("    Organizador: %s\n", lcomp.competicion[competicionInt].organizador);
                    printf("    Nombre:      %s\n", lcomp.competicion[competicionInt].nomCompeticion);
                    printf("    Fecha:      %i-%i-%i\n", lcomp.competicion[competicionInt].dia, lcomp.competicion[competicionInt].mes, lcomp.competicion[competicionInt].ano);
                    cout<<"Elija lo que quiere hacer:"<<"\n";
                    cout<<"    1- Modificar Organizador"<<"\n";
                    cout<<"    2- Modificar Nombre"<<"\n";
                    cout<<"    3- Modificar Fecha"<<"\n";
                    cout<<"    4- Eliminar esta competicion"<<endl;
                    cout<<"    5- SALIR"<<"\n";
                    cout<<"NOTA: No se puede modificar Codigo ni Lugar, si quiere cambiarlo elimine y añada la competicion de nuevo"<<"\n";
                    cout<<"Seleccione una opcion:"<<endl;
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &opcionEdicion);
                    cout<<"la opcion seleccionada es:"<< opcionEdicion <<"\n";

                    switch (opcionEdicion)
                    {
                    case 1:;
                        strcpy(newstr,"");
                        cout<<"Nuevo organizador: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lcomp.competicion[competicionInt].organizador, newstr);
                        modificar = 1;
                        
                        break;
                    
                    case 2:;
                        strcpy(newstr,"");
                        cout<<"Nuevo nombre: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lcomp.competicion[competicionInt].nomCompeticion, newstr);
                        modificar = 1;
                        
                        break;

                    case 3:;
                        strcpy(newstr,"");
                        cout<<"Nuevo anyo: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        sscanf(newstr, "%i", lcomp.competicion[competicionInt].ano);

                        fflush(stdout);
                        strcpy(newstr,"");
                        cout<<"Nuevo mes: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        sscanf(newstr, "%i", lcomp.competicion[competicionInt].mes);

                        fflush(stdout);
                        strcpy(newstr,"");
                        cout<<"Nuevo dia: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        sscanf(newstr, "%i", lcomp.competicion[competicionInt].dia);

                        modificar = 1;


                        break;

                    case 4:;
                        deleteCompeticion(db, lcomp.competicion[competicionInt]);
                        break;

                    default:
                        break;
                    }
                    if(modificar == 0){
                        actualizarCompeticion(db, lcomp.competicion[competicionInt]);
                    }
                }
                
                break;

            case 2:;

            Competicion nuevaComp;

            cout<<"Seleccione nuevo codigo(numeros): "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaComp.CdCompeticion);

                ListaLugar lLugar;
                cargarLugares(db, &lLugar);
                imprimirLugares(lLugar);
                cout<<"Seleccione un lugar: "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaComp.CdLugar);

                cout<<"Seleccione un nombre de organizador: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(nuevaComp.organizador, newstr);

                cout<<"Seleccione un nombre para la competicion: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(nuevaComp.nomCompeticion, newstr);

                cout<<"Seleccione un año: "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaComp.ano);

                cout<<"Seleccione un mes: "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaComp.mes);

                cout<<"Seleccione un dia: "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaComp.dia);

                ainadirCompeticion(db, nuevaComp);
                free(lcomp.competicion);
                cargarCompeticiones(db, &lcomp);
                break;

            case 3:;//SALIR
                break;
            
            default:
                break;
            }

            
            break;
        }
    }

    char menuModalidades(sqlite3 *db){
        ListaModalidades lmod;
        char newstr[200];
        int opcionint=0;
        while(opcionint != 3){
            cargarModalidades(db, &lmod);
            //system("cls");
            imprimirModalidades(lmod);
            cout<<"\nElija lo que quiere hacer:"<< "\n";
            cout<<"    1-Seleccionar Modalidad"<<"\n";
            cout<<"    2-Ainadir Modalidad"<< "\n";
            cout<<"    3-Salir"<< "\n";
            fflush(stdout);
            char linea[3];
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            cout<<"la opcion seleccionada es:"<<opcionint<< "\n";
            switch (opcionint)
            {
            case 1:;
                int modalidadint;
                cout<<"Seleccione la Modalidad: "<<endl;
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &modalidadint);
                modalidadint--;


                int opcionedicion = 0;
                int modificar = 0;
                while(opcionedicion!=3 && opcionedicion!=4){
                    modificar = 0;
                    system("cls");
                    cout<<"Los datos de la modalidad seleccionado son:"<<"\n";
                    printf("    Codigo:      %i\n", lmod.modalidades[modalidadint].cd_mod);
                    printf("    Descripcion: %s\n", lmod.modalidades[modalidadint].descripcion);
                    printf("    Nombre:      %s\n", lmod.modalidades[modalidadint].nom_modalidad);
                    cout<<"Elija lo que quiere hacer:"<<"\n");
                    cout<<"    1- Modificar Descripcion"<<"\n";
                    cout<<"    2- Modificar Nombre"<<"\n";
                    cout<<"    3- Eliminar esta modalidad"<<endl;
                    cout<<"    4- SALIR"<<"\n";
                    cout<<"NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada la modalidad de nuevo"<<"\n";
                    cout<<"Seleccione una opcion:"<<endl;
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &opcionedicion);
                    cout<<"la opcion seleccionada es:"<<opcionedicion<<"\n";

                    switch (opcionedicion)
                    {
                    case 1:;
                        strcpy(newstr,"");
                        cout<<"Nueva descripcion: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 200, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lmod.modalidades[modalidadint].descripcion, newstr);
                        modificar = 1;
                        
                        break;
                    case 2:;
                        strcpy(newstr,"");
                        cout<<"Nuevo nombre: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 40, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lmod.modalidades[modalidadint].nom_modalidad, newstr);
                        modificar = 1;
                        
                        break;
                    case 3:;
                        deleteModalidad(db, lmod.modalidades[modalidadint]);
                        break;

                    default:
                        break;
                    }
                    if(modificar == 0){
                        actualizarModalidad(db, lmod.modalidades[modalidadint]);
                    }


                }
                
                break;
            case 2:;//Ainadir modalidad
                Modalidad nuevaModalidad;

                cout<<"Seleccione nuevo codigo(numeros): "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &nuevaModalidad.cd_mod);

                cout<<"Seleccione nueva descripcion: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(nuevaModalidad.descripcion, newstr);

                cout<<"Seleccione nuevo nombre: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(nuevaModalidad.nom_modalidad, newstr);

                ainadirModalidad(db, nuevaModalidad);
                free(lmod.modalidades);
                cargarModalidades(db, &lmod);
                break;
            case 3:;//SALIR
                break;
            default:
                cout<<"Caso no contemplado"<<"\n";
                break;
            }
            free(lmod.modalidades);
            cargarModalidades(db, &lmod);
        }
    }

    char menuLugares(sqlite3 *db){
        ListaPais paises;
        ListaLugar lugares;
        char newstr[50];
        int newint;
        int opcionint=0;
        while(opcionint != 3){
            cargarLugares(db, &lugares);
            cargarPaises(db, &paises);
            //system("cls");
            imprimirLugares(lugares);
            cout<<"\nElija lo que quiere hacer:" <<"\n");
            cout<<"    1-Seleccionar Lugar"<<"\n";
            cout<<"    2-Ainadir Lugar"<< "\n";
            cout<<"    3-Salir"<< "\n";
            fflush(stdout);
            char linea[3];
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            cout<<"la opcion seleccionada es:"<< opcionint<<"\n";
            switch (opcionint)
            {
            case 1:;
                int lugarint;
                cout<<"Seleccione el lugar: "<<endl;
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &lugarint);
                lugarint--;


                int opcionedicion = 0;
                int modificar = 0;
                while(opcionedicion!=4 && opcionedicion!=5){
                    modificar = 0;
                    system("cls");
                    cout<<"Los datos del lugar seleccionado son:"<<"\n";
                    printf("    Codigo:    %i\n", lugares.lugar[lugarint].Cd_Lugar);
                    printf("    Nombre:    %s\n", lugares.lugar[lugarint].NOM_LUGAR);
                    printf("    Localidad: %s\n", lugares.lugar[lugarint].LOC_LUGAR);
                    printf("    Pais:      %s\n", lugares.lugar[lugarint].pais);
                    cout<<"Elija lo que quiere hacer:"<<"\n";
                    cout<<"    1- Modificar Nombre"<<"\n";
                    cout<<"    2- Modificar localidad"<<"\n";
                    cout<<"    3- Modificar pais"<<"\n";
                    cout<<"    4- Eliminar este lugar"<<"\n";
                    cout<<"    5- SALIR"<<"\n";
                    cout<<"NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada el lugar de nuevo"<<"\n";
                    cout<<"Seleccione una opcion:"<<endl;
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &opcionedicion);
                    cout<<"la opcion seleccionada es:"<< opcionedicion<<"\n";

                    switch (opcionedicion)
                    {
                    case 1:;
                        strcpy(newstr,"");
                        cout<<"Nuevo nombre: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 50, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lugares.lugar[lugarint].NOM_LUGAR, newstr);
                        modificar = 1;
                        
                        break;
                    case 2:;
                        strcpy(newstr,"");
                        cout<<"Nuevo localidad: "<<endl;
                        fflush(stdout);
                        fgets(newstr, 50, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        strcpy(lugares.lugar[lugarint].LOC_LUGAR, newstr);
                        modificar = 1;
                        
                        break;
                    case 3:;
                        imprimirPais(paises);
                        strcpy(newstr,"");
                        cout<<"Nuevo pais (numero): "<<endl;
                        fflush(stdout);
                        fgets(newstr, 10, stdin);
                        fflush(stdin);
                        limpiarFinales(newstr);
                        sscanf(newstr, "%i", &newint);
                        newint--;
                        if (newint >= 0 && newint < paises.tamanyo) {
                            modificar = 1;
                            lugares.lugar[lugarint].Cd_Pais = paises.paises[newint].codigo;
                        }
                        break;
                    case 4:;
                        deleteLugar(db, lugares.lugar[lugarint]);
                        break;

                    default:
                        break;
                    }
                    if(modificar == 0){
                        actualizarLugar(db, lugares.lugar[lugarint]);
                    }


                }
                
                break;
            case 2:;//Ainadir pais
                Lugar lugarNuevo;

                cout<<"Seleccione nuevo codigo(numeros): "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &lugarNuevo.Cd_Lugar);

                cout<<"Seleccione nuevo nombre: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(lugarNuevo.NOM_LUGAR, newstr);

                cout<<"Seleccione nuevo localidad: "<<endl;
                fflush(stdout);
                fgets(newstr, 50, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                strcpy(lugarNuevo.LOC_LUGAR, newstr);

                imprimirPais(paises);
                cout<<"Seleccione nuevo pais(numeros): "<<endl;
                fflush(stdout);
                fgets(newstr, 10, stdin);
                fflush(stdin);
                limpiarFinales(newstr);
                sscanf(newstr, "%i", &newint);
                newint--;

                if (newint < 0 || newint >= paises.tamanyo) {
                    cout<<"No has seleccionado un pais valido"<<"\n";
                    break;
                }
                lugarNuevo.Cd_Pais = paises.paises[newint].codigo;
                
                ainadirLugar(db, lugarNuevo);
                break;
            case 3:;//SALIR
                break;
            default:
                cout<<"Caso no contemplado"<<"\n";
                break;
            }
            free(lugares.lugar);
            free(paises.paises);
        }
    }

    void cargarDatosPostu(){
        cout<<"Cargando"<< "\n";
        int porcentaje = 0;
        for (int i = 0; i <= 20; i++)
        {
            cout<<"Lleva un"<<porcentaje<< "porciento"<<"\n";
            Sleep(100);
            porcentaje += 5;
        }
        cout<<"Se ha completado la carga de datos"<<endl;
    }
    
	return 0;
}