// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    int socketfd;
    int vettore[DIM] = {10, -5, 69, 26};

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, vettore, sizeof(vettore));

    for (int i = 0; i < DIM; i++)
    {
        printf("[%d] --> %d\n", i, vettore[i]);
    }

    close(socketfd);
    return 0;
}