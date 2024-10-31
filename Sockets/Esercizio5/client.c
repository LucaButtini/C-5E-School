// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
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
    char stringa[DIM_STR];
    int socketfd;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, argv[1], sizeof(argv[1]));

    read(socketfd, stringa, sizeof(stringa));
    printf("Stringa ordinata --> %s\n", stringa);

    close(socketfd);

    return 0;
}