#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIM 1024

int contiene_lettere(char stringa[]){
    int check = 1;
    for(int i=0; i<strlen(stringa); i++){
       if(!(stringa[i]>= 'A' && stringa[i] <= 'Z' || stringa[i]>= 'a' && stringa[i] <= 'z')){
           check = 0;
           break;
       }
    }
    return check;
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
