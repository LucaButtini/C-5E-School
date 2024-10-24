// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define DIM_STR 1024
#define SERVERPORT 1313

void conta_cons_e_voc(char stringa[], int *cons, int *voc)
{
    char lettera;
    *voc = 0;
    *cons = 0;

    for (int i = 0; i < strlen(stringa); i++)
    {
        lettera = tolower(stringa[i]);
        if (isalpha(lettera))
        {
            if (lettera == 'a' || lettera == 'e' || lettera == 'i' || lettera == 'o' || lettera == 'u')
                (*voc)++;
            else
                (*cons)++;
        }
    }
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, soa, fromlen = sizeof(servizio), cons, voc;
    char stringa[DIM_STR], risposta[DIM_STR];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for (;;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);
        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);
        read(soa, stringa, sizeof(stringa));
        conta_cons_e_voc(stringa, &cons, &voc);
        int len = snprintf(risposta, sizeof(risposta), "Stringa -> [%s], Vocali -> [%d], Consonanti -> [%d]\n", stringa, voc, cons);
        if (len >= sizeof(risposta))
        {
            fprintf(stderr, "Attenzione: l'output è stato troncato!\n");
        }
        write(soa, risposta, strlen(risposta) + 1);
        close(soa);
    }
    close(socketfd);
    return 0;
}
