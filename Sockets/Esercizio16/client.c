#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 4

int main(int argc, char **argv)
{
    struct sockaddr_in servizio;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd;
    double vett1[DIM] = {25, 44, -7, 48}, vett2[DIM] = {18, 52, 9, -21};
    double somma[DIM], differenza[DIM], prodotto[DIM], quoziente[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, vett1, sizeof(vett1));
    write(socketfd, vett2, sizeof(vett2));

    read(socketfd, somma, sizeof(somma));
    read(socketfd, differenza, sizeof(differenza));
    read(socketfd, prodotto, sizeof(prodotto));
    read(socketfd, quoziente, sizeof(quoziente));

    printf("\nSomma:\n");
    for (int i = 0; i < DIM; i++)
    {
        printf("[%d] %f\n", i, somma[i]);
    }

    printf("\nDifferenza:\n");
    for (int i = 0; i < DIM; i++)
    {
        printf("[%d] %f\n", i, differenza[i]);
    }

    printf("\nProdotto:\n");
    for (int i = 0; i < DIM; i++)
    {
        printf("[%d] %f\n", i, prodotto[i]);
    }

    printf("\nQuoziente:\n");
    for (int i = 0; i < DIM; i++)
    {
        printf("[%d] %f\n", i, quoziente[i]);
    }

    close(socketfd);
    return 0;
}
