#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    int socketfd;
    int vettore[DIM] = {-5, 10, 69, 26};
    int somma_pari, somma_dispari;
    double media_pari, media_dispari;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, &somma, sizeof(somma));
    read(socketfd, &media, sizeof(media));

    printf("Somma: %d\n", somma);
    printf("Media: %.2f\n", media);

    close(socketfd);
    return 0;
}