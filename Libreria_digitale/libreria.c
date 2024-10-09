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

Categoria *categorie[DIM];
int num_categorie = 0;

/*Categoria *crea_categoria(char nome[])
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
}*/
Categoria *crea_categoria(char nome[])
{
    nome[strcspn(nome, "\n")] = '\0';
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
    Libro libro;

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

// Funzione per stampare i libri di una categoria specifica
void stampa_libri_categoria(char nome_categoria[])
{
     nome_categoria[strcspn(nome_categoria, "\n")] = '\0';
    for (int i = 0; i < num_categorie; i++)
    {
        if (strcmp(categorie[i]->nome, nome_categoria) == 0)
        {
            printf("Libri nella categoria \"%s\":\n", categorie[i]->nome);
            for (int j = 0; j < categorie[i]->num_libri; j++)
            {
            printf("Categoria: %s\n", categorie[i]->nome);
            printf("Title: %s\n", categorie[i]->libri[j].title);
            printf("Author: %s\n", categorie[i]->libri[j].author);
            printf("Year: %d\n", categorie[i]->libri[j].year);
            printf("Price: %.2f\n", categorie[i]->libri[j].price);
            printf("----------------------------\n");
            }
            return; 
        }
    }
    printf("Categoria non trovata\n");
}

// Funzione per stampare tutti i libri nella libreria con la loro categoria
void stampa()
{
    printf("Elenco dei libri nella libreria:\n");
    for (int i = 0; i < num_categorie; i++)
    {
        for (int j = 0; j < categorie[i]->num_libri; j++)
        {
            printf("Categoria: %s\n", categorie[i]->nome);
            printf("Title: %s\n", categorie[i]->libri[j].title);
            printf("Author: %s\n", categorie[i]->libri[j].author);
            printf("Year: %d\n", categorie[i]->libri[j].year);
            printf("Price: %.2f\n", categorie[i]->libri[j].price);
            printf("----------------------------\n");
        }
    }
}


// Funzione per cercare un libro specifico in base al titolo
Libro *ricerca_libro(char titolo[])
{
    for (int i = 0; i < num_categorie; i++)
    {
        for (int j = 0; j < categorie[i]->num_libri; j++)
        {
            if (strcmp(categorie[i]->libri[j].title, titolo) == 0)
            {
                return &categorie[i]->libri[j];
            }
        }
    }
   return NULL;
}


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
    char titolo_ricerca[DIM_STR], categoria_ricerca[DIM_STR];
    leggi_file();
    stampa();
    //prova ricerca categoria
    printf("\nCerca libri di una categoria specifica\n");
    fgets(categoria_ricerca, DIM_STR, stdin);
    categoria_ricerca[strcspn(categoria_ricerca, "\n")] = '\0';
    stampa_libri_categoria(categoria_ricerca);

    //prova ricerca per nome
    printf("\nCerca libro per titolo\n");
    fgets(titolo_ricerca, DIM_STR, stdin);
    titolo_ricerca[strcspn(titolo_ricerca, "\n")] = '\0';
    Libro *libro_trovato=ricerca_libro(titolo_ricerca);
    if (libro_trovato != NULL)
    {
        printf("\nLibro trovato:\n");
        printf("Title: %s\n", libro_trovato->title);
        printf("Author: %s\n", libro_trovato->author);
        printf("Year: %d\n", libro_trovato->year);
        printf("Price: %.2f\n", libro_trovato->price);
        printf("Genre: %s\n", libro_trovato->genre);
    }
    else
    {
        printf("Libro non trovato\n");
    }

    libera_memoria();
    return 0;
}
