// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DIM 4
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    int socketfd;
    int vettore[DIM] = {-5, 10, 69, 26};
    int somma_pari, somma_dispari;
    double media_pari, media_dispari;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, &somma_pari, sizeof(somma_pari));
    read(socketfd, &media_pari, sizeof(media_pari));
    read(socketfd, &somma_dispari, sizeof(somma_dispari));
    read(socketfd, &media_dispari, sizeof(media_dispari));

    printf("Somma dei numeri pari: %d\n", somma_pari);
    printf("Media dei numeri pari: %.2f\n", media_pari);
    printf("Somma dei numeri dispari: %d\n", somma_dispari);
    printf("Media dei numeri dispari: %.2f\n", media_dispari);

    close(socketfd);
    return 0;
}
