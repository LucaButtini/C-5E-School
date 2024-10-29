// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM_STR 1024
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore argomenti\n");
        exit(-1);
    }

    struct sockaddr_in servizio;
    int socketfd, check = 0;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, argv[1], strlen(argv[1]) + 1);
    read(socketfd, &check, sizeof(int));

    if (check)
        printf("La stringa è palindroma\n");
    else
        printf("La stringa non è palindroma\n");

    close(socketfd);
    return 0;
}
