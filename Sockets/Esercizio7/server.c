// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int somma_pari(int vettore[], int n)
{
    int somma = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 == 0)
        { // Numero pari
            somma += vettore[i];
        }
    }
    return somma;
}

// Funzione per calcolare la somma dei numeri dispari
int somma_dispari(int vettore[], int n)
{
    int somma = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 != 0)
        { // Numero dispari
            somma += vettore[i];
        }
    }
    return somma;
}

// Funzione per contare i numeri pari
int conta_pari(int vettore[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 == 0)
        {
            count++;
        }
    }
    return count;
}

// Funzione per contare i numeri dispari
int conta_dispari(int vettore[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 != 0)
        {
            count++;
        }
    }
    return count;
}

double calcola_media(int somma, int conteggio)
{
    if (conteggio == 0)
    {
        return 0; 
    }
    else
    {
        return (double)somma / conteggio;
    }
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    int vettore[DIM];
    int somma_pari, somma_dispari;
    double media_pari, media_dispari;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for (;;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vettore, sizeof(vettore));

        somma = calcola_somma(vettore);
        media = calcola_media(somma);

        write(soa, &somma, sizeof(somma));
        write(soa, &media, sizeof(media));
        close(soa);
    }
    close(socketfd);
    return 0;
}