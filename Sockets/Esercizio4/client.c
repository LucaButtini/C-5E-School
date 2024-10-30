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
    struct sockaddr_in servizio;
    int socketfd, occorrenze = 0;
    char stringa[DIM_STR], car;

    printf("Inserisci una stringa: ");
    scanf("%s", stringa);

    printf("Inserisci un carattere da contare: ");
    scanf(" %c", &car);

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    write(socketfd, stringa, strlen(stringa) + 1);
    write(socketfd, &car, 1);

    read(socketfd, &occorrenze, sizeof(int));
    printf("Occorrenze del carattere '%c': %d\n", car, occorrenze);

    close(socketfd);
    return 0;
}
