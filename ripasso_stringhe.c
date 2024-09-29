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

void crea_stringhe(char stringa[], char s_pari[], char s_dispari[]) { // punto 3
  int pari = 0, dispari = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if (i % 2 == 0) {
      s_pari[pari++] = stringa[i];
    } else {
      s_dispari[dispari++] = stringa[i];
    }
  }
  s_pari[pari] = '\0';
  s_dispari[dispari] = '\0';
}

int contiene_doppie(char stringa[]) { // punto 4
  for (int i = 0; i < strlen(stringa) - 1; i++) {
    if (stringa[i] == stringa[i + 1]) {
      return 1;
    }
  }
  return 0;
}

int confronta(char stringa1[], char stringa2[]) { // punto 1.1
  if (strlen(stringa1) == strlen(stringa2)) {
    return -1;
  } else if (strlen(stringa1) < strlen(stringa2)) {
    return 0;
  } else {
    return 1;
  }
}

int verifica_lettera(char lettera) {
  return (lettera == 'a' || lettera == 'e' || lettera == 'i' ||
          lettera == 'o' || lettera == 'u' || lettera == 'A' ||
          lettera == 'E' || lettera == 'I' || lettera == 'O' || lettera == 'U');
}

int conta_vocali(char stringa[]) { // 1.3
  int conta = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if (verifica_lettera(stringa[i])) {
      conta++;
    }
  }
  return conta;
}

int conta_consonanti(char stringa[]) { // 1.4
  int conta = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if ((stringa[i] >= 'A' && stringa[i] <= 'Z' ||
         stringa[i] >= 'a' && stringa[i] <= 'z') &&
        !verifica_lettera(stringa[i])) {
      conta++;
    }
  }
  return conta;
}

int main() {
  char stringa1[DIM], stringa2[DIM], s_pari[DIM], s_dispari[DIM];
  char car;
  int conta, vocali1, consonanti1, vocali2, consonanti2;
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
  crea_stringhe(stringa1, s_pari, s_dispari);
  printf("\nStringa con i caratteri pari: %s\n", s_pari);
  printf("Stringa con i caratteri dispari: %s\n", s_dispari);
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
  vocali1 = conta_vocali(stringa1);
  vocali2 = conta_vocali(stringa2);
  consonanti1 = conta_consonanti(stringa1);
  consonanti2 = conta_consonanti(stringa2);
  if (vocali1 > vocali2) {
    printf("\nLa stringa 1 ha più vocali\n");
  } else if (vocali1 < vocali2) {
    printf("\nLa stringa 2 ha più vocali\n");
  } else {
    printf("\nLe stringhe hanno lo stesso numero di vocali\n");
  }
  if (consonanti1 > consonanti2) {
    printf("\nLa stringa 1 ha più consonanti\n");
  } else if (consonanti1 < consonanti2) {
    printf("\nLa stringa 2 ha più consonanti\n");
  } else {
    printf("\nLe stringhe hanno lo stesso numero di consonanti\n");
  }
  return 0;
}
