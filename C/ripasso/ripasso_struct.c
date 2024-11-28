#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 3

typedef struct {
  char modello_auto[100];
  char marca[100];
  int cilindrata;
  int prezzo;
  int anno_immatricolazione;
} Auto;

void stampa_prezzi(Auto conc[]) {
  int max = 0, min = INT_MAX, pos_min, pos_max;
  for (int i = 0; i < DIM; i++) {
    if (conc[i].prezzo > max) {
      max = conc[i].prezzo;
      pos_max = i;
    } else if (conc[i].prezzo < min) {
      min = conc[i].prezzo;
      pos_min = i;
    }
  }
  printf("\nPrezzo più alto: %d, modello: %s\n", conc[pos_max].prezzo,
         conc[pos_max].modello_auto);
  printf("\nPrezzo più basso: %d, modello: %s\n", conc[pos_min].prezzo,
         conc[pos_min].modello_auto);
}

int ricerca_prezzo(Auto conc[], int ricerca) {
  for (int i = 0; i < DIM; i++) {
    if (ricerca == conc[i].prezzo) {
      return i;
      break;
    }
  }
  return -1;
}

void ordina_auto(Auto conc[]) {
  Auto temp;
  for (int i = 0; i < DIM - 1; i++) {
    for (int j = 0; j < DIM - 1 - i; j++) {
      if (conc[j].anno_immatricolazione > conc[j + 1].anno_immatricolazione) {
        temp = conc[j];
        conc[j] = conc[j + 1];
        conc[j + 1] = temp;
      }
    }
  }
}

void stampa(Auto conc[]) {
  for (int i = 0; i < DIM; i++) {
    printf("Modello: [%s], Marca: [%s], Cilindrata: [%d], Prezzo: [%d], Anno "
           "Immatricolazione: [%d]\n",
           conc[i].modello_auto, conc[i].marca, conc[i].cilindrata,
           conc[i].prezzo, conc[i].anno_immatricolazione);
  }
}

int main(int argc, char *argv[]) {
  char modello[100], marca[100];
  int posizione;
  int ricercato;
  Auto a1 = {"modello 1", "marca 1", 80, 60, 2009};
  Auto a2 = {"modello 2", "marca 2", 50, 300, 2013};
  Auto a3 = {"modello 3", "marca 3", 100, 800, 1996};
  Auto concessionaria[DIM] = {a1, a2, a3};
  ordina_auto(concessionaria);
  stampa(concessionaria);
  stampa_prezzi(concessionaria);
  printf("\nInserisci il prezzo della macchina da ricercare\n");
  scanf("%d", &ricercato);
  posizione = ricerca_prezzo(concessionaria, ricercato);
  if (posizione != -1) {
    printf("\nPrezzo [%d], Modello [%s]\n", ricercato,
           concessionaria[posizione].modello_auto);
  } else {
    printf("\nMacchina non presente nella concessionaria\n");
  }
  return 0;
}
