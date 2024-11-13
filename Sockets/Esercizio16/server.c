#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

int main()
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd, soa, fromlen = sizeof(addr_remoto), vett1[DIM], vett2[DIM], somma[DIM], sottrazione[DIM], moltiplicazione[DIM];
    double divisione[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore creazione socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nel binding");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    listen(socketfd, 10);

    for (;;)
    {
        printf("Server in ascolto...\n");

        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vett1, sizeof(vett1));
        read(soa, vett2, sizeof(vett2));

        for (int i = 0; i < DIM; i++)
        {
            somma[i] = vett1[i] + vett2[i];
            sottrazione[i] = vett1[i] - vett2[i];
            moltiplicazione[i] = vett1[i] * vett2[i];

            // Controllo della divisione per zero
            if (vett2[i] != 0)
            {
                divisione[i] = (double)vett1[i] / vett2[i];
            }
            else
            {
                divisione[i] = 0;
            }
        }

        write(soa, somma, sizeof(somma));
        write(soa, sottrazione, sizeof(sottrazione));
        write(soa, moltiplicazione, sizeof(moltiplicazione));
        write(soa, divisione, sizeof(divisione));

        close(soa);
    }

    close(socketfd);
    return 0;
}