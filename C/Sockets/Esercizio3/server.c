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

int palindroma(char stringa[])
{
    for (int i = 0; i < strlen(stringa) / 2; i++)
    {
        if (stringa[i] != stringa[strlen(stringa) - 1 - i])
            return 0;
    }
    return 1;
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, soa, fromlen = sizeof(servizio), cons, voc, check = 0;
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
        check = palindroma(stringa);
        write(soa, &check, sizeof(int));
        close(soa);
    }
    return 0;
}
