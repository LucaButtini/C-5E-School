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
    int vettore[DIM] = {-5, 10, 69, 26};
    int min, max;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, &min, sizeof(min));
    read(socketfd, &max, sizeof(max));

    printf("Minimo: %d, Massimo: %d\n", min, max);

    close(socketfd);

    return 0;
}