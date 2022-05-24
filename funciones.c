#include "funciones.h"
#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
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

char menuPersona(ListaPersona* lper, sqlite3 *db){
    
    char newstr[20];
    char newnombre[20];
    int newtelefono;
    int newcdPais;
    char newdni[9];
    char newPais[20];
    ListaPais paises;
    cargarPaises(db, &paises);
	int opcionint=0;
    while(opcionint != 3){
        
        system("cls");
        imprimirAtletas(*lper);
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


            int opcionedicion;
            char nuevonombre[20];
            int telefono;
            int modificar;
            while(opcionedicion!=5){
                modificar = 0;
                system("cls");
                printf("Los datos del atleta seleccionado son:\n");
                printf("    Nombre: %s\n", lper->persona[atletaint].nombre);
                printf("    DNI: %s\n", lper->persona[atletaint].dni);
                printf("    Telefono: %i\n", lper->persona[atletaint].telefono);
                printf("    Pais: %s\n\n", lper->persona[atletaint].pais);
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
                    strcpy(lper->persona[atletaint].nombre, nuevonombre);
                    modificar = 1;
                    
                    break;
                case 2:;
                    strcpy(nuevonombre,"");
                    printf("Nuevo telefono: ");
                    fflush(stdout);
                    fgets(nuevonombre, 8, stdin);
                    sscanf(nuevonombre, "%i", &telefono);
                    lper->persona[atletaint].telefono = telefono;
                    modificar = 1;
                    break;
                case 3:;
                    
                    imprimirPais(paises);
                    strcpy(nuevonombre,"");
                    printf("Nuevo Pais(Numero): ");
                    fflush(stdout);
                    fgets(nuevonombre, 20, stdin);
                    sscanf(nuevonombre, "%i", &telefono);
                    for(int i = 0; i<paises.tamanyo;i++){
                        if(paises.paises[i].codigo == telefono){
                            strcpy(lper->persona[atletaint].pais, paises.paises[i].pais);
                            lper->persona[atletaint].cdPais = telefono;
                            modificar = 1;
                        }
                    }
                    break;
                case 4:;
                    deletePersona(db, lper->persona[atletaint]);
                    
                    break;

                default:
                    break;
                }
                if(modificar == 1){
                    //deletePersona(db, lper->persona[atletaint].dni);
                    //ainadirPersona(db, lper->persona[atletaint]);
                }


            }
            

            break;
        case 2:;//Ainadir atleta
            

            strcpy(newnombre, "");
            newtelefono = 0;
            newcdPais = 0;
            strcpy(newdni, "");
            strcpy(newPais, "");

            printf("Seleccione nuevo dni(8 numeros y una letra):");
            fflush(stdout);
            fgets(newdni, 10, stdin);

            printf("Seleccione nuevo nombre:");
            fflush(stdout);
            fgets(newnombre, 20, stdin);

            printf("Seleccione nuevo telefono: ");
            fflush(stdout);
            fgets(newstr, 8, stdin);
            sscanf(newstr, "%i", &telefono);

            char *p = malloc(sizeof(char)*20);
            imprimirPais(paises);
            printf("Nuevo Pais(Numero): ");
            fflush(stdout);
            fgets(p, 20, stdin);
            sscanf(p, "%i", &newcdPais);
            for(int i = 0; i<paises.tamanyo;i++){
                if(paises.paises[i].codigo == newcdPais){      
                    strcpy(newPais, paises.paises[i].pais);
                    newcdPais = paises.paises[i].codigo;
                }
            }
            printf("Se ha introducido correctamente\n");

            Persona personaNUeva;
            strcpy(personaNUeva.dni,newnombre);
            strcpy(personaNUeva.nombre,newnombre);
            personaNUeva.telefono = newtelefono;
            personaNUeva.cdPais = newcdPais;
            ainadirPersona(db,personaNUeva);
            cargarAtletas(db, lper);
            break;
        case 3:;//SALIR
            break;
        default:
            printf("Caso no contemplado\n");
            break;
        }
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



