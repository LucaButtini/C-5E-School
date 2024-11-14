#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 3
#define SERVERPORT 1313

int main(int arcg, char *argv[])
{
    struct sockaddr_in servizio;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, arr[DIM] = {3, -8, 12}, ris;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0)
    {
        perror("Errore socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore connect");
        exit(EXIT_FAILURE);
    }

    write(socketfd, arr, sizeof(arr));

    read(socketfd, &ris, sizeof(ris));

    printf("%d\n", ris);

    close(socketfd);

    return 0;
}