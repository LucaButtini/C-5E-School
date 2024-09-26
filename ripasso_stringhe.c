#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 1024

int contiene_lettere(char stringa[]) { // punto 1
  int check = 1;
  for (int i = 0; i < strlen(stringa); i++) {
    if (!(stringa[i] >= 'A' && stringa[i] <= 'Z' ||
          stringa[i] >= 'a' && stringa[i] <= 'z')) {
      check = 0;
      break;
    }
  }
  return check;
}

int conta_lettere(char stringa[], char car) { // punto 2
  int conta = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if (stringa[i] == car) {
      conta++;
    }
  }
  return conta;
}

int main() {
  char stringa1[DIM];
  char car;
  int conta;
  printf("Inserisci una stringa a piacere: ");
  scanf("%s", stringa1);
  if (contiene_lettere(stringa1) == 1) {
    printf("La stringa inserita contiene solo lettere\n");
  } else {
    printf("La stringa non contiene solo lettere\n");
  }

  printf("Inserisci la lettera che vuoi ricercare: ");
  scanf(" %c", &car);
  conta = conta_lettere(stringa1, car);
  printf("La lettera è presente %d volte\n", conta);
  return 0;
}
