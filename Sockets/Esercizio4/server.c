// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1313

// Funzione per contare le occorrenze del carattere 'car' nella stringa 'str'
int conta_occorrenze(char car, char str[])
{
    int conta = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == car)
            conta++;
    }
    return conta;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str[DIM];
    char car;
    int occorrenze;

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
        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

            read(soa, str, sizeof(str));
        read(soa, &car, sizeof(char));

        printf("Stringa ricevuta: %s\n", str);
        printf("Carattere ricevuto: %c\n", car);

        occorrenze = conta_occorrenze(car, str);
        printf("Il carattere è presente %d volte\n", occorrenze);

        write(soa, &occorrenze, sizeof(int));

        close(soa);
    }

    close(socketfd);
    return 0;
}
