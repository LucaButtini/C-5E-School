#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

void lettere_comuni(char str1[], char str2[], char comuni[])
{
    int pos = 0;

    for (int i = 0; str1[i] != '\0'; i++)
    {
        for (int j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
            {
                comuni[pos++] = str1[i]; 
                break;                   
            }
        }
    }
    comuni[pos] = '\0'; 
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd, soa, fromlen = sizeof(addr_remoto);
    char str1[DIM], str2[DIM], comuni[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore creazione socket");
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

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, str1, sizeof(str1));
        read(soa, str1, sizeof(str2));

        lettere_comuni(str1, str2, comuni);

        write(soa, comuni, sizeof(comuni));

        close(soa);
    }

    close(socketfd);
    return 0;
}