#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_STR 100
#define DIM 38 // Dimensione della libreria (numero massimo di libri)
#define BUFFER_DIM 1024

typedef struct
{
    char title[DIM_STR];
    char author[DIM_STR];
    int year;
    float price;
    char genre[DIM_STR];
} Libro;

Libro libreria[DIM];

// Funzione per leggere il file CSV e popolare la libreria
void leggi_file()
{
    char buffer[BUFFER_DIM];
    int riga = 0;
    FILE *file = fopen("libreria_libri.csv", "r");
    Libro libro;

    if (file == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(1);
    }

    while (fgets(buffer, BUFFER_DIM, file))
    {
        if (riga == 0)
        {
            riga++;
            continue;
        }

        char *value = strtok(buffer, ",");
        if (value == NULL)
            break;

        strcpy(libro.title, value);

        value = strtok(NULL, ",");
        strcpy(libro.author, value);

        value = strtok(NULL, ",");
        libro.year = atoi(value);

        value = strtok(NULL, ",");
        libro.price = atof(value);

        value = strtok(NULL, ",\n");
        strcpy(libro.genre, value);

        // Inserisce il libro nella libreria
        libreria[riga - 1] = libro;
        riga++;
        if (riga - 1 >= DIM)
            break;
    }
    fclose(file);
}

// Funzione per stampare tutti i libri della libreria
void stampa_libreria()
{
    for (int i = 0; i < DIM; i++)
    {
        printf("Title: %s\n", libreria[i].title);
        printf("Author: %s\n", libreria[i].author);
        printf("Year: %d\n", libreria[i].year);
        printf("Price: %.2f\n", libreria[i].price);
        printf("Genre: %s\n", libreria[i].genre);
        printf("-----------------------------------------------\n");
    }
}

int main(int argc, char *argv[])
{
    leggi_file();
    stampa_libreria();
    return 0;
}
