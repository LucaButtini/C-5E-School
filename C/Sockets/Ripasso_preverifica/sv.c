#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 4

void alterna_vett(int vett[])
{
    int temp;
    for (int i = 0; i < DIM - 1; i += 2)
    {
        temp = vett[i];
        vett[i] = vett[i + 1];
        vett[i + 1] = temp;
    }
}

int frequenza_componente(int vett[], int primo_valore)
{
    int conta = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (primo_valore == vett[i])
            conta++;
    }
    return conta;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen = sizeof(addr_remoto), vettore[DIM], frequenza, primo_valore;

    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_family = AF_INET;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Errore socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)) < 0)
    {
        perror("Errore bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    listen(socketfd, 10);

    for (;;)
    {
        printf("Server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);

        read(soa, vettore, sizeof(vettore));

       
        primo_valore = vettore[0];

        
        alterna_vett(vettore);

        
        write(soa, vettore, sizeof(vettore));

        
        frequenza = frequenza_componente(vettore, primo_valore);

        
        write(soa, &frequenza, sizeof(frequenza));

        close(soa);
    }
    close(socketfd);
    return 0;
}
