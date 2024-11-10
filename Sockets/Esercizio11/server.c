// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int conta_pari(int vett[])
{
    int conta = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (vett[i] % 2 == 0)
            conta++;
    }
    return conta;
}

int conta_dispari(int vett[])
{
    int conta = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (vett[i] % 2 != 0)
            conta++;
    }
    return conta;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    int vettore[DIM], pari, dispari;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nel binding");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    listen(socketfd, 10);

    for (;;)
    {
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, (socklen_t *)&fromlen);

        read(soa, vettore, sizeof(vettore));

        pari = conta_pari(vettore);
        dispari = conta_dispari(vettore);

        write(soa, &pari, sizeof(pari));
        write(soa, &dispari, sizeof(dispari));

        close(soa);
    }

    close(socketfd);
    return 0;
}