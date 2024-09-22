#include <bool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu() {
  printf("1 -> Stampa\n");
  printf("2 -> Stampa Invertito\n");
  printf("3 -> Stampa somma e media\n");
  printf("4-> Stampa Pari\n");
  printf("5 -> Stampa Dipari\n");
  printf("6 -> Ricerca\n");
  printf("7 -> Elimina\n");
  printf("8 -> Alterni\n");
  printf("9 -> Ordinamento\n");
  printf("10 -> Esci\n");
}

int main() {
  int scelta, dim = 0;
  bool esci = false;
  srand(time(NULL));
  printf("Inserisci la dimensione dell'array\n");
  scanf("%d", &dim);
  int numeri[dim];
  for (int i = 0; i < size; i++) {
    numeri[i] = rand() % 100; // Random numbers between 0 and 99
  }
  do {
    menu();
    printf("Inserisci la scelta:\n");
    scanf("%d", &scelta);
    switch (scelta) {
    case 1:
      printf("dsds\n");
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      esci = 1;
    default:
      printf("Scela errata\n");
      break;
    }
  } while (esci == 0);
  return 0;
}
