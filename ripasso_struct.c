#include <stdio.h>
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

int ricerca_prezzo(Auto conc[], double ricerca) {
	for(int i=0; i<DIM; i++) {
		if(ricerca== conc[i].prezzo) {
			return i;
			break;
		}
	}
	return -1;
}

void stampa(Auto conc[]) {
	for(int i=0; i<DIM; i++) {
		printf("Modello: [%s], Marca: [%s], Cilindrata: [%d], Prezzo: [%.2f], Anno Immatricolazione: [%d]\n", conc[i].modello_auto, conc[i].marca, conc[i].cilindrata, conc[i].prezzo, conc[i].anno_immatricolazione);
	}
}

int main(int argc, char *argv[])
{
	char modello[100], marca[100];
	int posizione;
	double ricercato;
	Auto a1 = {"modello 1", "marca 1", 80, 600.54, 2009 };
	Auto a2 = {"modello 2", "marca 2", 50, 300.34, 2013 };
	Auto a3 = {"modello 3", "marca 3", 100, 800.53, 1996};
	Auto concessionaria[DIM] = {a1, a2, a3};
	stampa(concessionaria);
	printf("\nInserisci il prezzo della macchina da ricercare\n");
	scanf("%.2f", &ricercato);
	posizione =  ricerca_prezzo(concessionaria, ricercato);
	if(posizione != -1){
	    printf("\nPrezzo [%.2f], Modello [%s]\n", ricercato, concessionaria[posizione].modello_auto);
	}
	else{
	    printf("\nMacchina non presente nella concessionaria\n");
	}
	return 0;
}
