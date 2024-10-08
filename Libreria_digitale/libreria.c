#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_STR 100
#define BUFFER_DIM 1024
#define DIM 38 // Dimensione della libreria come numero massimo di libri dal file CSV

typedef struct
{
    char title[DIM_STR];
    char author[DIM_STR];
    int year;
    float price;
    char genre[DIM_STR];
} Libro;

typedef struct
{
    char nome[DIM_STR];
    Libro *libri;
    int num_libri;
} Categoria;

// Array di puntatori a categorie
Categoria *categorie[DIM];
int num_categorie = 0;

Categoria *crea_categoria(char nome[])
{
    for (int i = 0; i < num_categorie; i++)
    {
        if (strcmp(categorie[i]->nome, nome) == 0)
        {
            return categorie[i];
        }
    }
    Categoria *categoria = malloc(sizeof(Categoria));
    strcpy(categoria->nome, nome);
    categoria->libri = malloc(sizeof(Libro) * DIM);
    categoria->num_libri = 0;
    categorie[num_categorie++] = categoria;
    return categoria;
}

// Funzione per aggiungere un libro alla categoria specifica
void libro_categoria(Libro libro)
{
    Categoria *categoria = crea_categoria(libro.genre);
    categoria->libri[categoria->num_libri++] = libro;
}

// Funzione per leggere il file CSV e popolare le categorie
void leggi_file()
{
    char buffer[BUFFER_DIM];
    int riga = 0;
    FILE *file = fopen("libreria_libri.csv", "r");

    if (file == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(1);
    }

    while (fgets(buffer, BUFFER_DIM, file))
    {
        if (riga == 0)
        { // Salta la riga di intestazione
            riga++;
            continue;
        }

        Libro libro;
        char *value = strtok(buffer, ",");
        strcpy(libro.title, value);

        value = strtok(NULL, ",");
        strcpy(libro.author, value);

        value = strtok(NULL, ",");
        libro.year = atoi(value);

        value = strtok(NULL, ",");
        libro.price = atof(value);

        value = strtok(NULL, ",\n");
        strcpy(libro.genre, value);

        libro_categoria(libro);
        riga++;
    }
    fclose(file);
}

// Funzione per stampare tutti i libri suddivisi per categoria
void stampa_categorie()
{
    for (int i = 0; i < num_categorie; i++)
    {
        Categoria *categoria = categorie[i];
        printf("-----------------------------------------------\n");
        printf("Categoria: %s\n", categoria->nome);
        printf("Numero di libri: %d\n\n", categoria->num_libri);
        for (int j = 0; j < categoria->num_libri; j++)
        {
            Libro libro = categoria->libri[j];
            printf("Title: %s\n", libro.title);
            printf("Author: %s\n", libro.author);
            printf("Year: %d\n", libro.year);
            printf("Price: %.2f\n\n", libro.price);
        }
    }
}

// Funzione per liberare la memoria allocata
void libera_memoria()
{
    for (int i = 0; i < num_categorie; i++)
    {
        free(categorie[i]->libri);
        free(categorie[i]);
    }
}

int main()
{
    leggi_file();
    stampa_categorie();
    libera_memoria();
    return 0;
}
