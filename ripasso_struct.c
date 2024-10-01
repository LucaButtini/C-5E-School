#include <stdio.h
#include <stdlib.h>
#include <string.h>
#define DIM 3

typedef struct {
	char modello_auto[100];
	char marca[100];
	int cilindrata;
	double prezzo;
	int anno_immatricolazione;
} Auto;

void stampa(Auto concessionaria[]){
    for(int i=0; i<DIM; i++){
        printf("Modello: [%s], Marca: [%s]")
    }
}

int main(int argc, char *argv[])
{
	char modello[100], marca[100];
	Auto a1 = {"modello 1", "marca 1", 80, 600.54, 2009 };
	Auto a2 = {"modello 2", "marca 2", 50, 300.34, 2013 };
	Auto a3 = {"modello 3", "marca 3", 100, 800.53, 1996};
	Auto concessionaria[DIM] = {a1, a2, a3};
	return 0;
}
