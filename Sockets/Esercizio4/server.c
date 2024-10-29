// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM_STR 1024
#define SERVERPORT 1313

int conta_occorrenze(char stringa[], char car)
{
    int conta = 0;
    for (int i = 0; i < strlen(stringa); i++)
    {
        if (car == stringa[i])
            conta++;
    }
    return conta; 
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, soa, fromlen = sizeof(servizio), occorrenze;
    char car, stringa[DIM_STR];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for (;;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);

        read(soa, stringa, sizeof(stringa));
        read(soa, &car, sizeof(car));

        occorrenze = conta_occorrenze(stringa, car);

        write(soa, &occorrenze, sizeof(int));

        close(soa);
    }

    return 0;
}
