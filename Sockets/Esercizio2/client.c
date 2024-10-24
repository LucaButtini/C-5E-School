// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM_STR 1024
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore: fornire una stringa come argomento.\n");
        exit(-1);
    }
    char risposta[DIM_STR];
    struct sockaddr_in servizio;
    int socketfd;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    write(socketfd, argv[1], strlen(argv[1]) + 1);
    read(socketfd, risposta, sizeof(risposta));
    printf("%s", risposta);
    close(socketfd);
    return 0;
}
