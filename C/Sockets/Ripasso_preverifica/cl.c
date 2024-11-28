#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 4
/*Scrivere il codice di un'applicazione socket client-server in linguaggio C. L'applicazione deve
consentire al client di inviare al server un vettore di numeri interi maggiori di zero. Il server dovrà
analizzare il vettore ricevuto dal client e restituire al client: il vettore con le componenti alternate a
due a due (esempio: Vettore inserito: 1,2,3,4 - vettore alternato: 2,1,4,3 ) e la frequenza della prima
componente all’interno del vettore stesso (esempio: Vettore inserito: 1,2,1,4 - la prima componente
si ripete 2 volte all’interno del vettore).*/

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    int socketfd, vettore[DIM] = {1, 2, 1, 4}, freq;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("errore socket");
        exit(EXIT_FAILURE);
    }

    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("errore connect");
        exit(EXIT_FAILURE);
    }
    write(socketfd, vettore, sizeof(vettore));

    read(socketfd, vettore, sizeof(vettore));

    for (int i = 0; i < DIM; i++)
    {
        printf("%d\n", vettore[i]);
    }

    read(socketfd, &freq, sizeof(freq));
    printf("\n%d\n", freq);
    close(socketfd);
    return 0;
}
