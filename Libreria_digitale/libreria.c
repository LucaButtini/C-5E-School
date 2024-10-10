#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_STR 100
#define BUFFER_DIM 1024
#define DIM 38 // dimensione libreria

typedef struct
{
    char title[DIM_STR];  // titolo libro
    char author[DIM_STR]; // autore libro
    int year;             // anno pubblicazione libro
    float price;          // prezzo libro
    char genre[DIM_STR];  // genere del libro
} Libro;                  // struttura libro

typedef struct
{
    char nome[DIM_STR]; // nome categoria
    Libro *libri;       // puntatore ad array di libri
    int num_libri;
} Categoria; // struttura categoria

Categoria *categorie[DIM]; // array di categorie
int num_categorie = 0;     // contatore di categorie

void rimuovi_newline(char *str)
{
    size_t len = strlen(str); // Calcola la lunghezza della stringa di input
    // Se l'ultimo carattere è un carattere di nuova riga
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0'; // Sostituisce il newline con un terminatore di stringa
    }
    // Rimuovi eventuali spazi finali
    while (len > 0 && (str[len - 1] == ' '))
    {
        str[--len] = '\0'; // Riduce la lunghezza della stringa, sostituendo gli spazi finali con il terminatore
    }
    // Inizializza una variabile per individuare l'inizio della stringa
    size_t start = 0;
    // Rimuovi eventuali spazi iniziali
    while (str[start] == ' ')
    {
        start++; // Incrementa l'indice di partenza per saltare gli spazi iniziali
    }
    // Se ci sono spazi iniziali da rimuovere
    if (start > 0)
    {
        // Sposta la stringa a sinistra, sovrascrivendo gli spazi iniziali
        memmove(str, str + start, len - start + 1); // Copia la parte rimanente della stringa
    }
}

// funzione che crea la categoria
Categoria *crea_categoria(char nome[])
{
    nome[strcspn(nome, "\n")] = '\0'; // rimozione il newline
    for (int i = 0; i < num_categorie; i++)
    {
        if (strcmp(categorie[i]->nome, nome) == 0) // cerco categoria se già esiste
        {
            return categorie[i]; // ritorna la categoria
        }
    }
    Categoria *categoria = malloc(sizeof(Categoria)); // allocazione memoria per creare la categoria
    strcpy(categoria->nome, nome);
    categoria->libri = malloc(sizeof(Libro) * DIM); // allocazione memoria
    categoria->num_libri = 0;                       // num libri inizializzato
    categorie[num_categorie++] = categoria;         // aggiunta categoria
    return categoria;                               // ritorno categoria
}

// Funzione per aggiungere un libro alla categoria specifica
void libro_categoria(Libro libro)
{
    Categoria *categoria = crea_categoria(libro.genre); // crea o ottiene la categoria
    categoria->libri[categoria->num_libri++] = libro;   // aggiungo libro alla categoria
}

// Funzione per leggere il file CSV e popolare le categorie
void leggi_file()
{
    char buffer[BUFFER_DIM];                       // buffer per lettura del file
    int riga = 0;                                  // contatore righe
    FILE *file = fopen("libreria_libri.csv", "r"); // apertura del file csv
    Libro libro;

    if (file == NULL) // controllo se file è aperto corretamente
    {
        printf("Errore nell'apertura del file\n");
        exit(1);
    }

    while (fgets(buffer, BUFFER_DIM, file)) // lettura righe di un file
    {
        if (riga == 0) // Salta la riga di intestazione
        {
            riga++;
            continue;
        }
        // uso la funzione token per popolare la struct libro
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

        libro_categoria(libro); // aggiungo libro alla categoria corrispondente
        riga++;
    }
    fclose(file); // chiusura file
}

// Funzione per stampare i libri di una categoria specifica
void stampa_libri_categoria(char nome_categoria[])
{
    // nome_categoria[strcspn(nome_categoria, "\n")] = '\0'; // rimuovo il newline
    rimuovi_newline(nome_categoria);
    for (int i = 0; i < num_categorie; i++)
    {
        rimuovi_newline(categorie[i]->nome);
        if (strcmp(categorie[i]->nome, nome_categoria) == 0) // ricerco la categoria
        {
            printf("Libri nella categoria \"%s\":\n", categorie[i]->nome);
            for (int j = 0; j < categorie[i]->num_libri; j++)
            {
                printf("Categoria: %s\n", categorie[i]->nome);
                printf("Title: %s\n", categorie[i]->libri[j].title);
                printf("Author: %s\n", categorie[i]->libri[j].author);
                printf("Year: %d\n", categorie[i]->libri[j].year);
                printf("Price: %.2f\n", categorie[i]->libri[j].price);
                printf("---------------------------------------------------\n");
            }
            return; // esce dalla funzione se è stata trovata la categoria
        }
    }
    printf("Categoria non trovata\n"); // se non è trovata
}

// Funzione per stampare tutti i libri nella libreria
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

// Funzione per cercare un libro in base al titolo
Libro *ricerca_libro(char titolo[])
{
    for (int i = 0; i < num_categorie; i++)
    {
        for (int j = 0; j < categorie[i]->num_libri; j++)
        {
            if (strcmp(categorie[i]->libri[j].title, titolo) == 0) // ricerco il nome
            {
                return &categorie[i]->libri[j]; // ritorno puntatore al libro
            }
        }
    }
    return NULL; // se non trovato ritorno null
}

// funzione stampa del menu
void menu()
{
    printf("\n[1] -> STAMPA LIBRERIA\n");
    printf("[2] -> STAMPA PER CATEGORIA\n");
    printf("[3] -> RICERCA NOME\n");
    printf("[4] -> ESCI\n");
}
// funzione per liberare la memoria dopo le malloc
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
    int scelta, esci = 0;
    char titolo_ricerca[DIM_STR], categoria_ricerca[DIM_STR]; // stringhe nome e categoria di ricerca
    leggi_file();                                             // lettura file csv
    do
    {
        menu(); // visualizzazione menu
        printf("Inserisci la scelta: ");
        scanf("%d", &scelta); // scelta menu
        getchar();            // tolgo il newline dal buffer di input
        switch (scelta)
        {
        case 1:
            // stampa tutti i libri
            stampa();
            break;
        case 2:
            // ricerca categoria e stampa libri per categoria
            printf("\nCerca libri di una categoria specifica\n");
            fgets(categoria_ricerca, DIM_STR, stdin);
            //scanf("%[^\n]s", categoria_ricerca);                        // inserimento categoria
            categoria_ricerca[strcspn(categoria_ricerca, "\n")] = '\0'; // tolgo il newline
            stampa_libri_categoria(categoria_ricerca);
            // se lung maggiore di 0 o la fine != a \n
            break;
        case 3:
            // ricerca libro per titolo e stampa
            printf("\nCerca libro per titolo\n");
            fgets(titolo_ricerca, DIM_STR, stdin);                // inserimento titolo
            titolo_ricerca[strcspn(titolo_ricerca, "\n")] = '\0'; // tolgo il newline
            Libro *libro_trovato = ricerca_libro(titolo_ricerca);
            if (libro_trovato != NULL) // se il libro è stato trovato
            {
                printf("\nLibro trovato:\n");
                printf("Title: %s\n", libro_trovato->title);
                printf("Author: %s\n", libro_trovato->author);
                printf("Year: %d\n", libro_trovato->year);
                printf("Price: %.2f\n", libro_trovato->price);
                printf("Genre: %s\n", libro_trovato->genre);
            }
            else // se non è stato trovato
            {
                printf("Libro non trovato\n");
            }
            break;
        case 4:
            esci = 1; // flag per uscire dal ciclo
            break;
        default: // se la scelta è errata
            printf("Scelta errata\n");
            break;
        }
    } while (!esci);
    libera_memoria(); // libero la mmemoria
    return 0;
}
