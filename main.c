#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char opcion;
    char opcion2;
    do{
        opcion = menuPrincipal();
        switch (opcion){
            case '1':
                printf("Has dado 1\n");
                break;
            case '2':
                
                do{
                    for (int i=0; i<101 ; i++){
                        printf("\n");
                    }
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
                        return 0;
                        break;
                    }
                }while (opcion2 != "q");        
                break;
            case '3':
                printf("Has dado 3\n");
                break;
            case '4':
                return 0;
        }
        
    } while (opcion!= "q");
    return 0;
    
}


















    // if (opcion == 1)
    // {
    //     /* code */

    // }else if (opcion == 2)
    // {
    //     char opcionPais;
    //     opcionPais = menuPaises();

    // }else if (opcion ==3)
    // {
        

    // }else if (opcion == 4)
    // {
    //     printf("Gracias por su visita\n Esperemos que vuelva dentro de poco :)");
    //     return 0;
    // }
