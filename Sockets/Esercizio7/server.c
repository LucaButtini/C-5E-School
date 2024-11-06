// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int calcola_somma_pari(int vettore[], int n)
{
    int somma = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 == 0)
        {
            somma += vettore[i];
        }
    }
    return somma;
}


int calcola_somma_dispari(int vettore[], int n)
{
    int somma = 0;
    for (int i = 0; i < n; i++)
    {
        if (vettore[i] % 2 != 0)
        {
            somma += vettore[i];
        }
    }
    return somma;
}


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
    double media = 0.0;
    if (conteggio > 0)
    {
        media = (double)somma / conteggio;
    }
    return media;
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
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vettore, sizeof(vettore));

        
        somma_pari = calcola_somma_pari(vettore, DIM);
        somma_dispari = calcola_somma_dispari(vettore, DIM);
        media_pari = calcola_media(somma_pari, conta_pari(vettore, DIM));
        media_dispari = calcola_media(somma_dispari, conta_dispari(vettore, DIM));

      
        write(soa, &somma_pari, sizeof(somma_pari));
        write(soa, &media_pari, sizeof(media_pari));
        write(soa, &somma_dispari, sizeof(somma_dispari));
        write(soa, &media_dispari, sizeof(media_dispari));

        close(soa);
    }

    close(socketfd);
    return 0;
}
