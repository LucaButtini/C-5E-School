#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0)
    {
        perror("Errore creazione socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore binding");
        exit(EXIT_FAILURE);
    }

    listen(socketfd, 10);

    for (;;)
    {
        printf("Server in ascolto...\n");

        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, str, sizeof(str));

        write(soa, str, sizeof(str));

        close(soa);
    }
    close(socketfd);
    return 0;
}