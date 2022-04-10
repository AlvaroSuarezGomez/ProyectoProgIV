#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionesBD.h"

int main(void){
    char opcion;
    char opcion2;
    sqlite3 *db;

    int result = conectarBase("AtletasC.sqbpro",db);

	
    do{
        opcion = menuPrincipal();
        switch (opcion){
            case '1':
                espaciosEntreMenus();
                result = ensenarAtletas(db);
                break;
            case '2':
                
                do{
                    espaciosEntreMenus();
                    opcion2 = menuPaises();
                    switch (opcion2)
                    {
                    case '1':
                        printf("Has dado 1\n");
                        break;
                    
                    case '2':
                        printf("Has dado 2\n");
                        break;

                    case '3':
                        printf("Has dado 3\n");
                        break;

                    case'4':
                        printf("Has dado 4\n");
                        break;
                    case'5':
                        printf("Has dado 5\n");
                        espaciosEntreMenus();
                        break;
                    }
                }while (opcion2 != '5');        
                break;
            case '3':
                printf("Agur crack :)\n");
                break;
        }
        
    } while (opcion != '3');
    return 0;
    
}