#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM_STR 100
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore argomenti\n");
        exit(-1);
    }
    char stringa[DIM_STR];
    struct sockaddr_in servizio;
    int socketfd;
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr_in *)&servizio, sizeof(servizio));
    write(socketfd, argv[1], sizeof(argv[1]));
    close(socketfd);
    return 0;
}