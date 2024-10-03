#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 38 // dimensione libreria

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

void leggi_file()
{

}

int main(int argc, char *argv[])
{
    

    return 0;
}
