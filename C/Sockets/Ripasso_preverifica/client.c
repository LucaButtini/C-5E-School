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
    struct sockaddr_in servizio;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd;
    char messaggio[DIM];

    if (argc != 2)
    {
        perror("Errore argomenti");
        exit(EXIT_FAILURE);
    }

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0)
    {
        perror("Errore creazione socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore connect");
        exit(EXIT_FAILURE);
    }

    write(socketfd, argv[1], sizeof(argv[1]));

    read(socketfd, messaggio, sizeof(messaggio));

    printf("%s\n", messaggio);

    close(socketfd);

    return 0;
}