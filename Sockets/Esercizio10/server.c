#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

void confronta_lunghezza(const char *str1, const char *str2, char *messaggio)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 > len2)
    {
        strcpy(messaggio, "La prima stringa è più lunga della seconda.");
    }
    else if (len1 < len2)
    {
        strcpy(messaggio, "La seconda stringa è più lunga della prima.");
    }
    else
    {
        strcpy(messaggio, "Le due stringhe hanno la stessa lunghezza.");
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str1[DIM], str2[DIM];
    char messaggio[DIM];

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

        confronta_lunghezza(str1, str2, messaggio);

        write(soa, messaggio, sizeof(messaggio));

        close(soa);
    }

    close(socketfd);
    return 0;
}
