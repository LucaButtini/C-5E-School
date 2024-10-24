#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 512
#define SERVERPORT 1313

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Argomenti errati!\n");
        exit(1);
    }
    struct sockaddr_in servizio;
    int socketfd;   // identificatore della socket
    char str1[DIM]; // dati dei socket
    // settaggio del socket locale
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // impostazione del transport endpoint creazione della socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // richiesta di connessione al server
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    // scrivo sulla socket
    write(socketfd, argv[1], sizeof(argv[1]));
    // leggo dal server
    read(socketfd, str1, sizeof(str1));
    printf("\nStringhe ricevute: %s", str1);
    // chiudo il client
    close(socketfd);
    return 0;
}