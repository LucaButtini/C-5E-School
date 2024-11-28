// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1313

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    char str[DIM];
    char car;
    int socketfd, occorrenze;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

  
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    
    printf("Inserisci una stringa:\n");
    scanf("%s", str);
    printf("Inserisci un carattere da ricercare:\n");
    scanf(" %c", &car);


    write(socketfd, str, sizeof(str));
    write(socketfd, &car, sizeof(char));

    
    read(socketfd, &occorrenze, sizeof(int));
    printf("Occorrenze del carattere '%c': %d\n", car, occorrenze);

    
    close(socketfd);
    return 0;
}
