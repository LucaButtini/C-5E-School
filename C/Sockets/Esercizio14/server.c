#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

int contiene_doppie(char stringa[])
{
    for (int i = 0; i < strlen(stringa) - 1; i++)
    {
        if (stringa[i] == stringa[i + 1])
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd, soa, fromlen = sizeof(addr_remoto), valore;
    char stringa[DIM];

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

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, (socklen_t *)&fromlen);

        read(soa, stringa, sizeof(stringa));

        valore = contiene_doppie(stringa);

        write(soa, &valore, sizeof(valore));

        close(soa);
    }

    close(socketfd);
    return 0;
}