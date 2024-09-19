#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <bool.h>
#define DIM 50



void menu ()
{
    printf("1 -> Stampa\n");
    printf("2 -> Stampa Invertito\n");
    printf("3 -> Stampa somma e media\n");
    printf("4-> Stampa Pari\n");
    printf("5 -> Stampa Dipari\n");
    printf("6 -> Ricerca\n");
    printf("7 -> Elimina\n");
    printf("8 -> Alterni\n");
    printf("9 -> Ordinamento\n");
    printf("10 -> Esci\n");
    
}

int main()
{
    int scelta;
    bool esci = false;
    int numeri[DIM];
    
    do{
        menu();printf("Inserisci la scelta:\n");
        scanf("%d", &scelta);
        switch(scelta)
            {
            case 1:
            printf("dsds\n");    
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            break;
            case 9:
            break;
            case 10:
            esci = 1;
            default:
            printf("Scela errata\n");
            break;
            }
    }while(esci==0);
    return 0;
}
