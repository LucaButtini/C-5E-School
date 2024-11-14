#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 3
#define SERVERPORT 1313

int ritorna(int arr[])
{
    for (int i = 0; i < DIM; i++)
    {
        if (arr[i] < 0)
            return arr[i];
    }
    return 0;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(addr_remoto), arr[DIM], ris;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore creazione socket");
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

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, arr, sizeof(arr));

        ris = ritorna(arr);

        write(soa, &ris, sizeof(ris));

        close(soa);
    }
    close(socketfd);
}