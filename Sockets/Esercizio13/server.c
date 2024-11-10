#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

void confronta_contenuto(char *str1, char *str2, char *messaggio)
{
    int val = strcmp(str1, str2);

    if (val == 0)
    {
        strcpy(messaggio, "Le due stringhe sono uguali.");
    }
    else if (val < 0)
    {
        strcpy(messaggio, "La prima stringa è minore della seconda.");
    }
    else
    {
        strcpy(messaggio, "La prima stringa è maggiore della seconda.");
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str1[DIM], str2[DIM], messaggio[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore nella creazione del socket");
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

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, (socklen_t *)&fromlen);

        read(soa, str1, sizeof(str1));
        read(soa, str2, sizeof(str2));

        write(soa, messaggio, sizeof(messaggio));

        close(soa);
    }

    close(socketfd);
    return 0;
}
