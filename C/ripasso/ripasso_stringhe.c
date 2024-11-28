#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 1024 // Definizione di una costante per la dimensione massima delle stringhe

//punto 1
int contiene_lettere(char stringa[]) {
  for (int i = 0; i < strlen(stringa); i++) {
    if (!(stringa[i] >= 'A' && stringa[i] <= 'Z' ||
          stringa[i] >= 'a' && stringa[i] <= 'z')) {
      return 0; 
      break;    
    }
  }
  return 1; 
}

//punto 2
int conta_lettere(char stringa[], char car) {
  int conta = 0; 
  for (int i = 0; i < strlen(stringa); i++) {
    if (stringa[i] == car) {                      
      conta++;            
    }
  }
  return conta; 
}

//punto 3
void crea_stringhe(char stringa[], char s_pari[], char s_dispari[]) {
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

//punto 4
int contiene_doppie(char stringa[]) {
  for (int i = 0; i < strlen(stringa) - 1; i++) { 
    if (stringa[i] == stringa[i + 1]) { 
      return 1;           
    }
  }
  return 0; 
}

// punto 1.1
int confronta(char stringa1[], char stringa2[]) {
  if (strlen(stringa1) == strlen(stringa2)) { 
    return -1;                                
  } else if (strlen(stringa1) < strlen(stringa2)) { 
    return 0;                  
  } else {                       
    return 1;                   
  }
}

// se un carattere è vocale (punto 1.3)
int verifica_lettera(char lettera) {
  return (lettera == 'a' || lettera == 'e' || lettera == 'i' ||
          lettera == 'o' || lettera == 'u' || lettera == 'A' ||
          lettera == 'E' || lettera == 'I' || lettera == 'O' || lettera == 'U');
}

// punto 1.2
void lettere_comuni(char stringa1[], char stringa2[], char comuni[]) {
  int index = 0;
  int trovato;
  for (int i = 0; i < strlen(stringa1); i++) {
    trovato = 0;
    for (int k = 0; k < index; k++) { // controllo se la lettera è già stata aggiunta
      if (comuni[k] == stringa1[i]) {
        trovato = 1;
        break;
      }
    }
    if (!trovato) { // se la lettera non è già stata trovata
      for (int j = 0; j < strlen(stringa2); j++) { // cerco la lettera nella seconda stringa
        if (stringa1[i] == stringa2[j]) {
          comuni[index++] = stringa1[i]; 
          break; 
        }
      }
    }
  }
  comuni[index] = '\0'; // carattere terminatore
}

// punto 1.3
int conta_vocali(char stringa[]) {
  int conta = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if (verifica_lettera(stringa[i])) {
      conta++;
    }
  }
  return conta; // n vocali
}

// punto 1.4
int conta_consonanti(char stringa[]) {
  int conta = 0;
  for (int i = 0; i < strlen(stringa); i++) {
    if ((stringa[i] >= 'A' && stringa[i] <= 'Z' ||
         stringa[i] >= 'a' && stringa[i] <= 'z') &&
        !verifica_lettera(stringa[i])) {
      conta++;
    }
  }
  return conta; // n consonanti
}

int main() {
  char stringa1[DIM], stringa2[DIM], s_pari[DIM], s_dispari[DIM], comuni[DIM];
  char car;
  int conta, vocali1, consonanti1, vocali2, consonanti2;

  printf("Inserisci una stringa a piacere: ");
  scanf("%s", stringa1);

  // controllo se ci sono solo lettere
  if (contiene_lettere(stringa1) == 1) {
    printf("\nLa stringa inserita contiene solo lettere\n");
  } else {
    printf("\nLa stringa non contiene solo lettere\n");
  }

  // ricerca lettera
  printf("Inserisci la lettera che vuoi ricercare: ");
  scanf(" %c", &car);
  conta = conta_lettere(stringa1, car);
  printf("\nLa lettera è presente %d volte\n", conta);

  // stringhe pari e dispari
  crea_stringhe(stringa1, s_pari, s_dispari);
  printf("\nStringa con i caratteri pari: %s\n", s_pari);
  printf("Stringa con i caratteri dispari: %s\n", s_dispari);

  // contiene doppie
  if (contiene_doppie(stringa1) == 1) {
    printf("\nLa stringa contiene doppie\n");
  } else {
    printf("\nLa stringa non contiene doppie\n");
  }

  // confronto lunghezza
  printf("\n\nInserisci una seconda stringa a piacere: ");
  scanf("%s", stringa2);
  if (confronta(stringa1, stringa2) == -1) {
    printf("\nLe stringhe hanno la stessa lunghezza\n");
  } else if (confronta(stringa1, stringa2) == 0) {
    printf("\nLa stringa 2 è la più lunga\n");
  } else {
    printf("\nLa stringa 1 è la più lunga\n");
  }

  // lettere comuni
  lettere_comuni(stringa1, stringa2, comuni);
  printf("\nLe lettere comuni sono: %s", comuni);

  // numero vocali
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

  // numero consonanti
  if (consonanti1 > consonanti2) {
    printf("\nLa stringa 1 ha più consonanti\n");
  } else if (consonanti1 < consonanti2) {
    printf("\nLa stringa 2 ha più consonanti\n");
  } else {
    printf("\nLe stringhe hanno lo stesso numero di consonanti\n");
  }

  return 0;
}
