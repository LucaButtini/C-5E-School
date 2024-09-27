#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 1024

int contiene_lettere(char stringa[]) { // punto 1
  for (int i = 0; i < strlen(stringa); i++) {
    if (!(stringa[i] >= 'A' && stringa[i] <= 'Z' ||
          stringa[i] >= 'a' && stringa[i] <= 'z')) {
      return 0;
      break;
    }
  }
  return 1;
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

int contiene_doppie(char stringa[]) {
  for (int i = 0; i < strlen(stringa) - 1; i++) {
    if (stringa[i] == stringa[i + 1]) {
      return 1;
    }
  }
  return 0;
}

int main() {
  char stringa1[DIM];
  char car;
  int conta;
  printf("Inserisci una stringa a piacere: ");
  scanf("%s", stringa1);
  if (contiene_lettere(stringa1) == 1) {
    printf("\nLa stringa inserita contiene solo lettere\n");
  } else {
    printf("\nLa stringa non contiene solo lettere\n");
  }
  printf("Inserisci la lettera che vuoi ricercare: ");
  scanf(" %c", &car);
  conta = conta_lettere(stringa1, car);
  printf("\nLa lettera è presente %d volte\n", conta);
  if (contiene_doppie(stringa1) == 1) {
    printf("\nLa stringa contiene doppie\n");
  } else {
    printf("\nLa stringa non contiene doppie\n");
  }
  return 0;
}
