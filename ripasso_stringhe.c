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

int contiene_doppie(char stringa[]) { // punto 4
  for (int i = 0; i < strlen(stringa) - 1; i++) {
    if (stringa[i] == stringa[i + 1]) {
      return 1;
    }
  }
  return 0;
}

int confronta(char stringa1[], char stringa2[]) { //punto 1.1
  if (strlen(stringa1) == strlen(stringa2)) {
    return -1;
  } else if (strlen(stringa1) < strlen(stringa2)) {
    return 0;
  } else {
    return 1;
  }
}

int main() {
  char stringa1[DIM], stringa2[DIM];
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
  printf("\n\nInserisci una seconda stringa a piacere: ");
  scanf("%s", stringa2);
  if (confronta(stringa1, stringa2) == -1) {
    printf("Le stringhe hanno la stessa lunghezza\n");
  } else if (confronta(stringa1, stringa2) == 0) {
    printf("La stringa 2 è la più lunga\n");
  } else {
    printf("La stringa 1 è la più lunga\n");
  }
  return 0;
}
