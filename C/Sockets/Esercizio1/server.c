// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define DIM_STR 1024
#define SERVERPORT 1313

void stringa_in_maiuscola(char stringa[])
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        stringa[i] = toupper(stringa[i]);
    }
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, soa, fromlen = sizeof(servizio), cons, voc;
    char stringa[DIM_STR], risposta[DIM_STR];

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
        stringa_in_maiuscola(stringa);
        strcpy(risposta, stringa);
        printf("Stringa inviata: %s", risposta);
        write(soa, risposta, strlen(risposta) + 1);
        close(soa);
    }
    return 0;
}
