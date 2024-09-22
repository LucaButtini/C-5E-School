#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void stampa(int numeri[], int dim) {
  for (int i = 0; i < dim; i++) {
    printf("[%d] --> %d\n", i, numeri[i]);
  }
}
void stampa_contrario(int numeri[], int dim) {
  for (int i = dim - 1; i > 0; i--) {
    printf("[%d] --> %d\n", i, numeri[i]);
  }
}
void media_somma(int numeri[], int dim) {
  int somma = 0;
  float media = 0;
  for (int i = 0; i < dim; i++) {
    somma += numeri[i];
  }
  media = (float)somma / dim;
  printf("MEDIA --> [%.2f], SOMMA --> [%d]\n", media, somma);
}

void menu() {
  printf("\n1 -> Stampa\n");
  printf("2 -> Stampa Invertito\n");
  printf("3 -> Stampa somma e media\n");
  printf("4-> Stampa Pari\n");
  printf("5 -> Stampa Dipari\n");
  printf("6 -> Ricerca\n");
  printf("7 -> Elimina\n");
  printf("8 -> Alterni\n");
  printf("9 -> Ordinamento\n");
  printf("10 -> Esci\n\n");
}

int main() {
  int scelta, dim = 0;
  int esci = 0;
  srand(time(NULL));
  printf("Inserisci la dimensione dell'array\n");
  scanf("%d", &dim);
  int numeri[dim];
  for (int i = 0; i < dim; i++) {
    numeri[i] = rand() % 100;
  }

  do {
    menu();
    printf("Inserisci la scelta:\n");
    scanf("%d", &scelta);
    switch (scelta) {
    case 1:
      stampa(numeri, dim);
      break;
    case 2:
      stampa_contrario(numeri, dim);
      break;
    case 3:
      media_somma(numeri, dim);
      break;
    case 4:

      break;
    case 5:

      break;
    case 6: {
      int val;
      printf("Inserisci il numero da cercare: ");
      scanf("%d", &val);
      break;
    }
    case 7: {
      int val;
      printf("Inserisci il numero da eliminare: ");
      scanf("%d", &val);
      break;
    }
    case 8:
      break;
    case 9:

      break;
    case 10:
      esci = 1;
      break;
    default:
      printf("Scelta errata.\n");
      break;
    }
  } while (!esci);
  return 0;
}
