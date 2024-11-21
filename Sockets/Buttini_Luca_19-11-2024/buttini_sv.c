// server
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

// funzione per salvare nella stringa risulato i caratteri comuni delle due stringhe (no doppioni)
void comuni(char str1[], char str2[], char risultato[])
{
    int index = 0; // indice stringa risultato
    // cicli for per iterare nelle due stringhe
    for (int i = 0; i < strlen(str1); i++)
    {
        for (int j = 0; j < strlen(str2); j++)
        {
            // controllo se i caratteri sono comuni
            if (str1[i] == str2[j])
                risultato[index++] = str1[i]; // assegno il carattere comune a risulato
        }
    }
}

int main(int argc, char *argv[])
{
    // struttura servizio e addr_remoto
    struct sockaddr_in servizio, addr_remoto;

    // assegnazione valori ai campi della struct servizio
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); // indirizzo ip uso INADDR_ANY
    servizio.sin_family = AF_INET;                // famiglia socket, AF_INET, riferita agli IPv4
    servizio.sin_port = htons(SERVERPORT);        // porta per il collegamento, uso la 1313

    // descriptor socket e dimensione addr_remoto
    int socketfd, soa, fromlen = sizeof(addr_remoto);

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

    // creazione e controllo del binding
    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        // comunicazione errore con funzione perror
        perror("Errore binding");
        // chiusura connessione
        close(socketfd);
        // uscita dal programma in caso di errore
        exit(EXIT_FAILURE);
    }

    // ascolta per connessioni su un socket, ne accetta al massimo 10
    listen(socketfd, 10);

    // ciclo infinito
    for (;;)
    {
        // stampa messaggio server in ascolto
        printf("Server in ascolto...\n");

        // flush dello stream dati
        fflush(stdout);

        // accetta connessione socket
        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        // leggo dal client le due stringhe
        read(soa, str1, sizeof(str1));
        read(soa, str2, sizeof(str2));

        // chiamata alla funzione per trovare i caratteri comuni nelle due stringhe
        comuni(str1, str2, risultato);

        // invio al client il risulato
        write(soa, risultato, sizeof(risultato));

        // chiudo connessione soa
        close(soa);
    }
    // chiudo connessione socketfd
    close(socketfd);
    return 0;
}