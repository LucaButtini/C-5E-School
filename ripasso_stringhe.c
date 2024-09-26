#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define DIM 1024

int contiene_lettere(char stringa[]){
    int check_lettera = 1; 
    for(int i=0; i<strlen(stringa); i++){
        if(!isalpha(stringa[i])){ //utilizzata con la lib ctype.h controlla se una stringa contiene solo lettere
            check_lettera = 0;
            break;
        }
    }
    return check_lettera;
}

int main()
{
    char stringa1[DIM];
    printf("Inserisci una stringa a piacere: ");
    scanf("%s", stringa1);
    if(contiene_lettere(stringa1) == 1 ){
        printf("La stringa inserita contiene solo lettere\n");
    }else{
        printf("La stringa non contiene solo lettere\n");
    }
    return 0;
}
