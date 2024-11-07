// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

#define DIM 4
#define SERVERPORT 1313

int calcola_max(int vettore[])
{
    int max = vettore[0];
    for (int i = 0; i < DIM; i++)
    {
        if (vettore[i] > max)
            max = vettore[i];
    }
    return max;
}

int calcola_min(int vettore[])
{
    int min = vettore[0];
    for (int i = 0; i < DIM; i++)
    {
        if (vettore[i] < min)
            min = vettore[i];
    }
    return min;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    int vettore[DIM];
    int min, max;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for (;;)
    {
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vettore, sizeof(vettore));

        min = calcola_min(vettore);
        max = calcola_max(vettore);

        write(soa, &min, sizeof(min));
        write(soa, &max, sizeof(max));

        close(soa);
    }
    close(socketfd);
    return 0;
}