// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

#define DIM_STR 1024
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Errore argomenti\n");
        exit(-1);
    }

    struct sockaddr_in servizio;
    int socketfd, confronto = 0;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, argv[1], strlen(argv[1]) + 1);
    write(socketfd, argv[2], strlen(argv[2]) + 1);

    read(socketfd, &confronto, sizeof(confronto));

    if (confronto == -1)
    {
        printf("\nLe stringhe hanno la stessa lunghezza\n");
    }
    else if (confronto == 0)
    {
        printf("\nLa stringa 2 è la più lunga\n");
    }
    else
    {
        printf("\nLa stringa 1 è la più lunga\n");
    }

    close(socketfd);
    return 0;
}
