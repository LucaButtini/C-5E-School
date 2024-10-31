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

#define DIM_STR 1024
#define SERVERPORT 1313

void ordina_stringa(char stringa[])
{
    char temp;
    for (int i = 0; i < strlen(stringa) - 1; i++)
    {
        for (int j = i + 1; j < strlen(stringa); j++)
        {
            if (stringa[i] > stringa[j])
            {
                temp = stringa[i];
                stringa[i] = stringa[j];
                stringa[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char stringa[DIM_STR];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for (;;)
    {
        printf("\nServer in ascolto...");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);

        read(soa, stringa, sizeof(stringa));

        ordina_stringa(stringa);
        write(soa, stringa, sizeof(stringa));

        close(soa);
    }
    close(socketfd);
    return 0;
}