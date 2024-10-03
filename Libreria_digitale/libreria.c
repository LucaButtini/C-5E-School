#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 38 // dimensione libreria
#define BUFFER_DIM 1024

typedef struct {
    char title[TITLE_SIZE];
    char author[AUTHOR_SIZE];
    int year;
    float price;
} Libro;

typedef enum {
    ADVENTURE,
    DYSTOPIAN,
    FANTASY,
    GOTHIC,
    HISTORICAL_FICTION,
    LITERARY_FICTION,
    MEMOIR,
    MODERNIST,
    MYSTERY,
    PHILOSOPHICAL,
    POETRY,
    ROMANCE,
    MAGICAL_REALISM,
    EXISTENTIALIST,
    PLAY,
    SCIENCE_FICTION,
    CATEGORY_COUNT 
} Categoria;

Libro libreria[DIM];

//https://www.geeksforgeeks.org/relational-database-from-csv-files-in-c/
void leggi_file(){
    char buffer[BUFFER_DIM];
    int colonna=0, riga=0;
    FILE *file = fopen("libreria_libri.csv", "r");
    if(file == NULL){
        printf("Errore apertura file\n");
        exit(1); 
    }
while(fgets(buffer, BUFFER_DIM,file)){
    colonna=0;
    riga++;
    if(riga==1){
        char *value = strok(buffer, ",");
        while(value){
            if(colonna==0)
            {
                
            }
        }
    }
}

}

int main(int argc, char *argv[])
{
    if(argc!= 2){
        printf("Errore numero argomenti\n");
        exit(1);
    }

    return 0;
}
