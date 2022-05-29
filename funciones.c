#include "funciones.h"
#include "funcionesBD.h"
#include "pais.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "atleta.h"
#include "competicion.h"
#include "modalidad.h"
#include "lugar.h"
#include "ranking.h"
// para linux usar #include <unistd.h>

void limpiarLineas(char *texto, int capacidadaxima)
{
	if ((strlen(texto) == capacidadaxima-1) && (texto[capacidadaxima-2] != '\n'))
		while (getchar() != '\n');
}

char menuPrincipal(){
    printf("Elija lo que quiere hacer: \n");
    printf("    1-Ensenar Atletas \n");
    printf("    2-Ver ranking por paises\n"); 
    printf("    3-Salir\n");
    printf("Seleccione opcion: \n");
    fflush(stdout);
	char linea[5];
	fgets(linea, 3, stdin);
	return *linea;
}

char menuAdmin(){
    printf("Es usted Admistrador o Usuario?\n");
    printf("   1-Administrador\n");
    printf("   2-Usuario\n");
    fflush(stdout);
	char linea[3];
	fgets(linea, 3, stdin);
	return *linea;
}

void menuPrincipalAdmin(sqlite3* db) {

    int opcionint=0;
    while(opcionint != 7){
        //system("cls");
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Gestionar atletas \n");
        printf("    2-Gestionar paises \n");
        printf("    3-Gestionar modalidades \n");
        printf("    4-Gestionar lugares\n");
        printf("    5-Gestionar competiciones\n");
        printf("    6-Gestionar rankings\n");
        printf("    7-Salir \n");
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("la opcion seleccionada es: %i\n", opcionint);
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
        case 6:
            menuRanking(db);
            break;
        case 7:;//SALIR
            break;
        default:
            printf("Caso no contemplado\n");
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
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Atleta \n");
        printf("    2-Ainadir Atleta \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("la opcion seleccionada es: %i\n", opcionint);
        switch (opcionint)
        {
        case 1:;
            int atletaint;
            printf("Seleccione el Atleta: ");
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
                printf("Los datos del atleta seleccionado son:\n");
                printf("    Nombre: %s\n", lper.persona[atletaint].nombre);
                printf("    DNI: %s\n", lper.persona[atletaint].dni);
                printf("    Telefono: %i\n", lper.persona[atletaint].telefono);
                printf("    Pais: %s\n\n", lper.persona[atletaint].pais);
                printf("Elija lo que quiere hacer:\n");
                printf("    1- Modificar Nombre\n");
                printf("    2- Modificar Telefono\n");
                printf("    3- Modificar Pais\n");
                printf("    4- Eliminar este atleta");
                printf("    5- SALIR\n");
                printf("NOTA: No se puede modificar DNI si quiere cambiarlo elimine y añada al atleta de nuevo\n");
                printf("Seleccione una opcion:");
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &opcionedicion);
                printf("la opcion seleccionada es: %i\n",opcionedicion);
                switch (opcionedicion)
                {
                case 1:;
                    strcpy(nuevonombre,"");
                    printf("Nuevo nombre: ");
                    fflush(stdout);
                    fgets(nuevonombre, 20, stdin);
                    fflush(stdin);
                    limpiarFinales(nuevonombre);
                    strcpy(lper.persona[atletaint].nombre, nuevonombre);
                    modificar = 1;
                    
                    break;
                case 2:;
                    strcpy(nuevonombre,"");
                    printf("Nuevo telefono: ");
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
                    printf("Nuevo Pais(Numero): ");
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

            printf("Seleccione nuevo dni(8 numeros y una letra):");
            fflush(stdout);
            fgets(newdni, 10, stdin);
            fflush(stdin);
            limpiarFinales(newdni);
            strcpy(personaNUeva.dni,newdni);

            printf("Seleccione nuevo nombre:");
            fflush(stdout);
            fgets(newnombre, 20, stdin);
            fflush(stdin);
            limpiarFinales(newnombre);
            strcpy(personaNUeva.nombre,newnombre);

            printf("Seleccione nuevo telefono: ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &newtelefono);

            char *p = malloc(sizeof(char)*20);
            imprimirPais(paises);
            printf("Nuevo Pais(Numero): ");
            fflush(stdout);
            fgets(p, 20, stdin);
            fflush(stdin);
            sscanf(p, "%i", &newcdPais);
            printf("%i\n", newcdPais);
            newcdPais--;
            if (newcdPais < 0 || newcdPais >= paises.tamanyo) {
                printf("No has elegido un pais valido\n");
                break;
            }

            printf("Se ha introducido correctamente\n");

            
            personaNUeva.telefono = newtelefono;
            personaNUeva.cdPais = paises.paises[newcdPais].codigo;
            ainadirPersona(db,personaNUeva);
            free(lper.persona);
            cargarAtletas(db, &lper);
            break;
        case 3:;//SALIR
            break;
        default:
            printf("Caso no contemplado\n");
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
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Pais \n");
        printf("    2-Ainadir Pais \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("la opcion seleccionada es: %i\n", opcionint);
        switch (opcionint)
        {
        case 1:;
            int paisint;
            printf("Seleccione el Pais: ");
            fflush(stdout);
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &paisint);
            paisint--;


            int opcionedicion = 0;
            int modificar = 0;
            while(opcionedicion!=3 && opcionedicion!=2){
                modificar = 0;
                system("cls");
                printf("Los datos del pais seleccionado son:\n");
                printf("    Codigo: %i\n", paises.paises[paisint].codigo);
                printf("    Nombre: %s\n", paises.paises[paisint].pais);
                printf("Elija lo que quiere hacer:\n");
                printf("    1- Modificar Nombre\n");
                printf("    2- Eliminar este pais");
                printf("    3- SALIR\n");
                printf("NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada el pais de nuevo\n");
                printf("Seleccione una opcion:");
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &opcionedicion);
                printf("la opcion seleccionada es: %i\n",opcionedicion);

                switch (opcionedicion)
                {
                case 1:;
                    strcpy(newstr,"");
                    printf("Nuevo nombre: ");
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

            printf("Seleccione nuevo codigo(numeros): ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &paisNuevo.codigo);

            printf("Seleccione nuevo nombre: ");
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
            printf("Caso no contemplado\n");
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
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Competicion \n");
        printf("    2-Ainadir Competicion \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
        fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("La opcion seleccionada es: %i\n", opcionint);

        switch (opcionint)
        {
        case 1:;
            int competicionInt;
            printf("Seleccione la competición: ");
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
                printf("Los datos de la competicion seleccionada son:\n");
                printf("    Codigo:      %i\n", lcomp.competicion[competicionInt].CdCompeticion);
                printf("    Lugar:      %s\n", lcomp.competicion[competicionInt].lugar);
                printf("    Organizador: %s\n", lcomp.competicion[competicionInt].organizador);
                printf("    Nombre:      %s\n", lcomp.competicion[competicionInt].nomCompeticion);
                printf("    Fecha:      %i-%i-%i\n", lcomp.competicion[competicionInt].dia, lcomp.competicion[competicionInt].mes, lcomp.competicion[competicionInt].ano);
                printf("Elija lo que quiere hacer:\n");
                printf("    1- Modificar Organizador\n");
                printf("    2- Modificar Nombre\n");
                printf("    3- Modificar Fecha\n");
                printf("    4- Eliminar esta competicion");
                printf("    5- SALIR\n");
                printf("NOTA: No se puede modificar Codigo ni Lugar, si quiere cambiarlo elimine y añada la competicion de nuevo\n");
                printf("Seleccione una opcion:");
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &opcionEdicion);
                printf("la opcion seleccionada es: %i\n",opcionEdicion);

                switch (opcionEdicion)
                {
                case 1:;
                    strcpy(newstr,"");
                    printf("Nuevo organizador: ");
                    fflush(stdout);
                    fgets(newstr, 40, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    strcpy(lcomp.competicion[competicionInt].organizador, newstr);
                    modificar = 1;
                    
                    break;
                
                case 2:;
                    strcpy(newstr,"");
                    printf("Nuevo nombre: ");
                    fflush(stdout);
                    fgets(newstr, 40, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    strcpy(lcomp.competicion[competicionInt].nomCompeticion, newstr);
                    modificar = 1;
                    
                    break;

                case 3:;
                    strcpy(newstr,"");
                    printf("Nuevo anyo: ");
                    fflush(stdout);
                    fgets(newstr, 40, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    sscanf(newstr, "%i", lcomp.competicion[competicionInt].ano);

                    fflush(stdout);
                    strcpy(newstr,"");
                    printf("Nuevo mes: ");
                    fflush(stdout);
                    fgets(newstr, 40, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    sscanf(newstr, "%i", lcomp.competicion[competicionInt].mes);

                    fflush(stdout);
                    strcpy(newstr,"");
                    printf("Nuevo dia: ");
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

        printf("Seleccione nuevo codigo(numeros): ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &nuevaComp.CdCompeticion);

            ListaLugar lLugar;
            cargarLugares(db, &lLugar);
            imprimirLugares(lLugar);
            printf("Seleccione un lugar: ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &nuevaComp.CdLugar);

            printf("Seleccione un nombre de organizador: ");
            fflush(stdout);
            fgets(newstr, 50, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            strcpy(nuevaComp.organizador, newstr);

            printf("Seleccione un nombre para la competicion: ");
            fflush(stdout);
            fgets(newstr, 50, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            strcpy(nuevaComp.nomCompeticion, newstr);

            printf("Seleccione un año: ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &nuevaComp.ano);

            printf("Seleccione un mes: ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &nuevaComp.mes);

            printf("Seleccione un dia: ");
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
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Modalidad \n");
        printf("    2-Ainadir Modalidad \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("la opcion seleccionada es: %i\n", opcionint);
        switch (opcionint)
        {
        case 1:;
            int modalidadint;
            printf("Seleccione la Modalidad: ");
            fflush(stdout);
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &modalidadint);
            modalidadint--;


            int opcionedicion = 0;
            int modificar = 0;
            while(opcionedicion!=3 && opcionedicion!=4){
                modificar = 0;
                system("cls");
                printf("Los datos de la modalidad seleccionado son:\n");
                printf("    Codigo:      %i\n", lmod.modalidades[modalidadint].cd_mod);
                printf("    Descripcion: %s\n", lmod.modalidades[modalidadint].descripcion);
                printf("    Nombre:      %s\n", lmod.modalidades[modalidadint].nom_modalidad);
                printf("Elija lo que quiere hacer:\n");
                printf("    1- Modificar Descripcion\n");
                printf("    2- Modificar Nombre\n");
                printf("    3- Eliminar esta modalidad");
                printf("    4- SALIR\n");
                printf("NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada la modalidad de nuevo\n");
                printf("Seleccione una opcion:");
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &opcionedicion);
                printf("la opcion seleccionada es: %i\n",opcionedicion);

                switch (opcionedicion)
                {
                case 1:;
                    strcpy(newstr,"");
                    printf("Nueva descripcion: ");
                    fflush(stdout);
                    fgets(newstr, 200, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    strcpy(lmod.modalidades[modalidadint].descripcion, newstr);
                    modificar = 1;
                    
                    break;
                case 2:;
                    strcpy(newstr,"");
                    printf("Nuevo nombre: ");
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

            printf("Seleccione nuevo codigo(numeros): ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &nuevaModalidad.cd_mod);

            printf("Seleccione nueva descripcion: ");
            fflush(stdout);
            fgets(newstr, 50, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            strcpy(nuevaModalidad.descripcion, newstr);

            printf("Seleccione nuevo nombre: ");
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
            printf("Caso no contemplado\n");
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
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Lugar \n");
        printf("    2-Ainadir Lugar \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
	    fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("la opcion seleccionada es: %i\n", opcionint);
        switch (opcionint)
        {
        case 1:;
            int lugarint;
            printf("Seleccione el lugar: ");
            fflush(stdout);
            fgets(linea, 3, stdin);
            sscanf(linea, "%i", &lugarint);
            lugarint--;


            int opcionedicion = 0;
            int modificar = 0;
            while(opcionedicion!=4 && opcionedicion!=5){
                modificar = 0;
                system("cls");
                printf("Los datos del lugar seleccionado son:\n");
                printf("    Codigo:    %i\n", lugares.lugar[lugarint].Cd_Lugar);
                printf("    Nombre:    %s\n", lugares.lugar[lugarint].NOM_LUGAR);
                printf("    Localidad: %s\n", lugares.lugar[lugarint].LOC_LUGAR);
                printf("    Pais:      %s\n", lugares.lugar[lugarint].pais);
                printf("Elija lo que quiere hacer:\n");
                printf("    1- Modificar Nombre\n");
                printf("    2- Modificar localidad\n");
                printf("    3- Modificar pais\n");
                printf("    4- Eliminar este lugar");
                printf("    5- SALIR\n");
                printf("NOTA: No se puede modificar Codigo si quiere cambiarlo elimine y añada el lugar de nuevo\n");
                printf("Seleccione una opcion:");
                fflush(stdout);
                fgets(linea, 3, stdin);
                sscanf(linea, "%i", &opcionedicion);
                printf("la opcion seleccionada es: %i\n",opcionedicion);

                switch (opcionedicion)
                {
                case 1:;
                    strcpy(newstr,"");
                    printf("Nuevo nombre: ");
                    fflush(stdout);
                    fgets(newstr, 50, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    strcpy(lugares.lugar[lugarint].NOM_LUGAR, newstr);
                    modificar = 1;
                    
                    break;
                case 2:;
                    strcpy(newstr,"");
                    printf("Nuevo localidad: ");
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
                    printf("Nuevo pais (numero): ");
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

            printf("Seleccione nuevo codigo(numeros): ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &lugarNuevo.Cd_Lugar);

            printf("Seleccione nuevo nombre: ");
            fflush(stdout);
            fgets(newstr, 50, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            strcpy(lugarNuevo.NOM_LUGAR, newstr);

            printf("Seleccione nuevo localidad: ");
            fflush(stdout);
            fgets(newstr, 50, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            strcpy(lugarNuevo.LOC_LUGAR, newstr);

            imprimirPais(paises);
            printf("Seleccione nuevo pais(numeros): ");
            fflush(stdout);
            fgets(newstr, 10, stdin);
            fflush(stdin);
            limpiarFinales(newstr);
            sscanf(newstr, "%i", &newint);
            newint--;

            if (newint < 0 || newint >= paises.tamanyo) {
                printf("No has seleccionado un pais valido\n");
                break;
            }
            lugarNuevo.Cd_Pais = paises.paises[newint].codigo;
            
            ainadirLugar(db, lugarNuevo);
            break;
        case 3:;//SALIR
            break;
        default:
            printf("Caso no contemplado\n");
            break;
        }
        free(lugares.lugar);
        free(paises.paises);
    }
}

char menuRanking(sqlite3* db) {
    Ranking rank;
    char newstr[200];
    double lanzamiento;


    int opcionint = 0;
    while (opcionint != 3) {
        //system("cls");
        printf("\nElija lo que quiere hacer: \n");
        printf("    1-Seleccionar Competidor en Ranking \n");
        printf("    2-Ainadir Competidor en Ranking \n");
        printf("    3-Salir \n");
        fflush(stdout);
        char linea[3];
        fgets(linea, 3, stdin);
        sscanf(linea, "%i", &opcionint);
        printf("La opcion seleccionada es: %i\n", opcionint);

        switch (opcionint)
        {
        case 1:;
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

            printf("\nElija lo que quiere hacer: \n");
            printf("    1-Seleccionar competidor \n");
            printf("    2-Salir \n");
            fflush(stdout);
            char linea[3];
	        fgets(linea, 3, stdin);
            sscanf(linea, "%i", &opcionint);
            printf("la opcion seleccionada es: %i\n", opcionint);
            switch (opcionint) {
                case 1:;
                    int competidorInt;
                    printf("Seleccione al competidor: ");
                    fflush(stdout);
                    fgets(linea, 3, stdin);
                    sscanf(linea, "%i", &competidorInt);
                    competidorInt--;

                    int opcionedicion = 0;
                    int modificar = 0;
                    while (opcionedicion!=2 && opcionedicion!=3) {
                        modificar = 0;
                        system("cls");

                        printf("%s", rank.compite[competidorInt].dniPer);

                        printf("Los datos del competidor seleccionado son:\n");
                        printf("    DNI:    %s\n", rank.compite[competidorInt].dniPer);
                        printf("    Nombre:    %s\n", rank.compite[competidorInt].nomPer);
                        printf("    Lanzamiento: %f\n", rank.compite[competidorInt].lanzamiento);
                        printf("Elija lo que quiere hacer:\n");
                        printf("    1- Modificar Lanzamiento\n");
                        printf("    2- Eliminar este competidor de este ranking\n");
                        printf("    3- SALIR\n");
                        printf("NOTA: No se puede modificar el DNI ni el nombre, para modificar el DNI tendra que eliminar al atleta desde el menu de atleta y para modificar el nombre tendra que modificar al atleta desde su menu\n");
                        printf("Seleccione una opcion:");
                        fflush(stdout);
                        fgets(linea, 3, stdin);
                        sscanf(linea, "%i", &opcionedicion);
                        printf("la opcion seleccionada es: %i\n",opcionedicion);

                        switch (opcionedicion)
                        {
                        case 1:;
                            strcpy(newstr,"");
                            printf("Nueva puntuacion de lanzamiento: ");
                            fflush(stdout);
                            fgets(newstr, 40, stdin);
                            limpiarFinales(newstr);
                            lanzamiento = atof(newstr);
                            rank.compite[competidorInt].lanzamiento = lanzamiento;
                            
                            modificar = 1;
                            break;

                        case 2:;
                            deleteCompetidor(db, rank.compite[competidorInt]);
                            break;
                        
                        default:
                            break;
                        }
                        if (modificar == 0) {
                            actualizarCompetidor(db, rank.compite[competidorInt]);
                        }
                    }
                    break;

                    case 2:;
                    break;
            } break;

            case 2:; //Anyadir Competidor
                    Compite nuevoCompetidor;

                    //ListaPais lPais;
                    cargarPaises(db, &lPais);
                    imprimirPais(lPais);
                    //int paisInt;
                    printf("Seleccione el pais: ");
                    fflush(stdout);
                    fgets(newstr, 3, stdin);
                    sscanf(newstr, "%i", &paisInt);

                    //ListaCompeticion lComp;
                    cargarCompeticionesPorPais(db, &lComp, paisInt);
                    imprimirCompeticiones(lComp);
                    //int competicionInt;
                    printf("Seleccione la competicion: ");
                    fflush(stdout);
                    fgets(newstr, 3, stdin);
                    sscanf(newstr, "%i", &competicionInt);
                    nuevoCompetidor.codCompeticion = competicionInt;

                    //ListaModalidades lMod;
                    cargarModalidades(db, &lMod);
                    imprimirModalidades(lMod);
                    //int modalidadInt;
                    printf("Seleccione la modalidad: ");
                    fflush(stdout);
                    fgets(newstr, 3, stdin);
                    sscanf(newstr, "%i", &modalidadInt);
                    nuevoCompetidor.codModalidad = modalidadInt;

                    ListaPersona lPer;
                    cargarAtletas(db, &lPer);
                    imprimirAtletas(lPer);
                    int personaInt;
                    printf("Seleccione una persona: ");
                    fflush(stdout);
                    fgets(newstr, 3, stdin);
                    sscanf(newstr, "%i", &personaInt);
                    strcpy(nuevoCompetidor.dniPer, lPer.persona[personaInt-1].dni);
                    strcpy(nuevoCompetidor.nomPer, lPer.persona[personaInt-1].nombre);

                    double lanzamiento;
                    printf("Introduce una puntuacion de lanzamiento: ");
                    fflush(stdout);
                    fgets(newstr, 10, stdin);
                    fflush(stdin);
                    limpiarFinales(newstr);
                    lanzamiento = atof(newstr);
                    nuevoCompetidor.lanzamiento = lanzamiento;

                    ainadirCompetidor(db, nuevoCompetidor);
                    free(rank.compite);
                    break;
            

            int opcionEdicion = 0;
            int modificar = 0;
            
            break;

        case 3:;//SALIR
            break;
        
        default:
            break;
        }

        
        break;
    }
}

void cargarDatosPostu(){
    printf("Cargando \n");
    int porcentaje = 0;
    for (int i = 0; i <= 20; i++)
    {
        printf("Lleva un %i porciento\n",porcentaje);
        Sleep(100);
        porcentaje += 5;
    }
    printf("Se ha completado la carga de datos");
}

void monstrarLogo(){
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXxlc:cdXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWd.    .oNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNK0NWMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWk.    .cXMMMMMMMMMMWWWMMMMMMMMMMMMMMWWWNNNXKk;..:0MM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKd:.    .:k000KXXXX0dccdO00K000000000000000000x;..:0MM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNd'.  .   ........''''...,dkO00KKKXXNNWWWMMMMMMMMNKKNMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK; .  .    ...';cccok00OkOKWMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:.....   .:OKXWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXc. .     .xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK:.   .  .:KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWMMMMMMMMK; . ..  .dWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKxcxWMMMMMMM0,       .lNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMWO:'',xWMMMMMMM0, ..   . .ckKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMNXK0NMWx''dXWWMMMMMMMMXo..       ...:dKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMKc.'oXXo.;KMMMMMMMMMMMMMNOl,... . ..  .'oKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMWo   .:;.cKMMMMMMMMMMMMMMMMWXxc,..  .   ..'xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMWK:      '0MMMMMMMMMMMMMMMMMNk:'.. ..:l:.. .oNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMNOxkd;.   .xWMMMMMMMMMMMMMMWKl.. ..;o0WMK;. .kMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMXxkXXd,     .kWMMMMMMMMMMMMWO;..';lOXWMMMK;  .kMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMW0x0NO;        ,0MMMMMMMMWXOx:..:xXNWMMMMMMX:. 'OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMNkxkkc. .'.      oWMMMMMMM0:...:ONMMMMMMMMMMWd..:KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMNO:,:;',:d0NXx'    ,0MMMMMMNo. .oXMMMMMMMMMMMMMO'.,kWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMWx,;xOKXNWMMMMMx.   .xMMMMMMXc.'xWMMMMMMMMMMMMMM0, ..;lodKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMXOOKNMMMMMMMMMMMO.    :KWMMMMW0x0WMMMMMMMMMMMMMMMO,.....,:OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMWKOXWMMMMMMMMMMMMMK;     'xNMMMMMMMMMMMMMMMMMMMMMMMN0OO0KKNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMN00NMMMMMMMMMMMMMMMWd.      cKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMWX0KWMMMMMMMMMMMMMMMMMk.       'kWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWK0KXWMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMWK0NMMMMMMMMMMMMMMMMMMM0,  ,dl.  .oNMMMMMMMMMWWWWNWWMMMMMMMMMMMMMMNl...lXMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMNKXWMMMMMMMMMMMMMMMMMMMMN:  :XWXk:..cKMMMMMMWXkxxddxkXWMMWWNWMMMMMMWd.  ,OX0Oxocclx00OkkKWMMMMMMM\n");
    Sleep(10);
    printf("MWXKNMMMMMMMMMMMMMMMMMMMMMNk,  oWMMMNo. ,kWMN0KWWWWWNNWWWMMXkdllddoodddl,. .'.  .,ldoddlldkKWMMMMMMM\n");
    Sleep(10);
    printf("WXXWMMMMMMMMMMMMMMMMMMMWKo'   :KMMMMMNx' .lkl.lNMMMMMMMMMMMWNXXK0Oxolc;.       .dNMMMMMWWWMMMMMMMMMM\n");
    Sleep(10);
    printf("XNMMMMMMMMMMMMMMMMMMMMXd.  'lONMMMMMMMMXkc.  'OMMMMMMMMMMMMMMMMMMMMMMMWXOo,     :KMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("WMMMMMMMMMMMMMMMMMMMNk,..ckNMMMMMMMMMMMMMWO;.oWMMMMMMMMMMMMMMMMMMMMMMMMMMMXo.    cXMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMWk. ;KWMMMMMMMMMMMMMMMMMXOKMMMMMMMMMMMMMMMMMMMMMMMMMMMMNk'    .cONMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMK: ,OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMW0o,. .';,. .,dXWMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMXo:xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK,.,ld0NWWKko:'':xXMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWd.:XMMMMMMMMMWXx;.,xNMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:;0MMMMMMMMMMMMMN0d::xNMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKx;.:XMMMMMMMMMMMMMMMMKl';xNMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN0xddONMMMMMMMMMMMMMMMMMWKxkNMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
}

void limpiarFinales(char* str) {
    while((str[strlen(str)-1]=='\n'||str[strlen(str)-1]=='\r')&&strlen(str)>0)str[strlen(str)-1]='\0';
}