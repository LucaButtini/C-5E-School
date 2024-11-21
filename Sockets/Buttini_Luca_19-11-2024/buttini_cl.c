// client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// BUTTINI LUCA FILA 2 5E

#define DIM 120         // dimensione stringa
#define SERVERPORT 1313 // porta server

int main(int argc, char *argv[])
{
    // struttura servizio
    struct sockaddr_in servizio;

    // assegnazione valori ai campi della struct servizio
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); // indirizzo ip uso INADDR_ANY
    servizio.sin_family = AF_INET;                // famiglia socket, AF_INET, riferita agli IPv4
    servizio.sin_port = htons(SERVERPORT);        // porta per il collegamento, uso la 1313

    // descriptor socket
    int socketfd;
    // stringhe 1 e 2 e risultato caratteri comuni
    char str1[DIM], str2[DIM], risultato[DIM];

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // controllo che socket venga creata correttamente
    if (socketfd < 0)
    {
        // comunicazione errore con funzione perror
        perror("Errore creazione del socket");
        // uscita dal programma in caso di errore
        exit(EXIT_FAILURE);
    }

    // creazione e controllo connect, che venga fatta correttamente
    if (connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        // comunicazione errore
        perror("Errore connect");
        // chiusura connessione
        close(socketfd);
        // uscita dal programma in caso di errore
        exit(EXIT_FAILURE);
    }
    // inserimento prima stringa
    printf("Inserisci la prima stringa: ");
    scanf("%s", str1);

    // inserimento seconda stringa
    printf("Inserisci la seconda stringa: ");
    scanf("%s", str2);

    // invio al server le stringhe
    write(socketfd, str1, sizeof(str1));
    write(socketfd, str2, sizeof(str2));

    // leggo dal server il risulato
    read(socketfd, risultato, sizeof(risultato));

    // stampo il risultato, i caratteri comuni delle due stringhe
    printf("Comuni: %s\n", risultato);

    // chiudo connessione socketfd
    close(socketfd);
    return 0;
}