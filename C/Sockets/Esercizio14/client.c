#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

int main()
{
    struct sockaddr_in servizio;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    int socketfd, valore;
    char stringa[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore nella connessione al server");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Inserisci una stringa: ");
    scanf("%s", stringa);

    write(socketfd, stringa, sizeof(stringa));

    read(socketfd, &valore, sizeof(valore));

    if (valore)
    {
        printf("\nLa stringa contiene doppie\n");
    }
    else
    {
        printf("\nLa stringa non contiene doppie\n");
    }

    close(socketfd);
    return 0;
}