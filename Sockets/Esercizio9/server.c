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

void bubble_sort(int numeri[])
{
    int temp;
    for (int i = 0; i < DIM - 1; i++)
    {
        for (int j = 0; j < DIM - 1 - i; j++)
        {
            if (numeri[j] > numeri[j + 1])
            {
                temp = numeri[j];
                numeri[j] = numeri[j + 1];
                numeri[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    int vettore[DIM];

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

        bubble_sort(vettore);

        write(soa, vettore, sizeof(vettore));
        
        close(soa);
    }
    close(socketfd);
    return 0;
}