#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 4
#define SERVERPORT 1313

int main()
{
    struct sockaddr_in servizio;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int vett1[DIM] = {-5, 10, 69, 26}, vett2[DIM] = {13, 34, -3, 9}, somma[DIM], sottrazione[DIM], moltiplicazione[DIM], socketfd;
    double divisione[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nella connessione al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    write(socketfd, vett1, sizeof(vett1));
    write(socketfd, vett2, sizeof(vett2));

    // Ricezione dei risultati dal server
    read(socketfd, somma, sizeof(somma));
    read(socketfd, sottrazione, sizeof(sottrazione));
    read(socketfd, moltiplicazione, sizeof(moltiplicazione));
    read(socketfd, divisione, sizeof(divisione));

    // Stampa dei risultati
    printf("Somma: ");
    for (int i = 0; i < DIM; i++)
        printf("%d ", somma[i]);
    printf("\n");

    printf("Sottrazione: ");
    for (int i = 0; i < DIM; i++)
        printf("%d ", sottrazione[i]);
    printf("\n");

    printf("Moltiplicazione: ");
    for (int i = 0; i < DIM; i++)
        printf("%d ", moltiplicazione[i]);
    printf("\n");

    printf("Divisione: ");
    for (int i = 0; i < DIM; i++)
        printf("%.2f ", divisione[i]);
    printf("\n");

    close(socketfd);
    return 0;
}
