// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int vettore[DIM] = {-5, 10, 69, 26}, socketfd;
    int pari, dispari;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore creazione socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nella connessione al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, &pari, sizeof(pari));
    read(socketfd, &dispari, sizeof(dispari));

    printf("Pari: %d, dispari: %d\n", pari, dispari);

    close(socketfd);
    return 0;
}