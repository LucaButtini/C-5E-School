// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

#define DIM_STR 1024
#define SERVERPORT 1313

int confronta_stringhe(char str1[], char str2[])
{
    if (strlen(str1) == strlen(str2))
        return -1;
    else if (strlen(str1) < strlen(str2))
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str1[DIM_STR], str2[DIM_STR];
    int confronto;

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

        read(soa, str1, sizeof(str1));
        read(soa, str2, sizeof(str2));

        confronto = confronta_stringhe(str1, str2);
        
        write(soa, &confronto, sizeof(confronto));

        close(soa);
    }
    close(socketfd);
    return 0;
}