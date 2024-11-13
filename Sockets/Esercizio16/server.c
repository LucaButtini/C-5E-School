
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 4

void calcola_somma(double vett1[], double vett2[], double somma[])
{
    for (int i = 0; i < DIM; i++)
    {
        somma[i] = vett1[i] + vett2[i];
    }
}

void calcola_differenza(double vett1[], double vett2[], double differenza[])
{
    for (int i = 0; i < DIM; i++)
    {
        differenza[i] = vett1[i] - vett2[i];
    }
}

void calcola_prodotto(double vett1[], double vett2[], double prodotto[])
{
    for (int i = 0; i < DIM; i++)
    {
        prodotto[i] = vett1[i] * vett2[i];
    }
}

void calcola_quoziente(double vett1[], double vett2[], double quoziente[])
{
    for (int i = 0; i < DIM; i++)
    {
        quoziente[i] = vett1[i] / vett2[i];
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio), value;
    double vett1[DIM], vett2[DIM], risultato[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0)
    {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nel bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    listen(socketfd, 10);

    for (;;)
    {
        printf("\nServer in ascolto...");

        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vett1, sizeof(vett1));

        read(soa, vett2, sizeof(vett2));

        calcola_somma(vett1, vett2, risultato);
        write(soa, risultato, sizeof(risultato));

        calcola_differenza(vett1, vett2, risultato);
        write(soa, risultato, sizeof(risultato));

        calcola_prodotto(vett1, vett2, risultato);
        write(soa, risultato, sizeof(risultato));

        calcola_quoziente(vett1, vett2, risultato);
        write(soa, risultato, sizeof(risultato));

        close(soa);
    }

    close(socketfd);
    return 0;
}