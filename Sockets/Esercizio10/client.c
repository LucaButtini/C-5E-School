#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 120
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char str1[DIM], str2[DIM];
    char messaggio[DIM];
    int socketfd;

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

    printf("Inserisci la prima stringa: ");
    fgets(str1, DIM, stdin);
    str1[strcspn(str1, "\n")] = 0;

    printf("Inserisci la seconda stringa: ");
    fgets(str2, DIM, stdin);
    str2[strcspn(str2, "\n")] = 0;

    write(socketfd, str1, sizeof(str1));
    write(socketfd, str2, sizeof(str2));

    read(socketfd, messaggio, sizeof(messaggio));
    printf("Risultato dal server: %s\n", messaggio);

    close(socketfd);
    return 0;
}
