#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 50

void menu() {
  printf("1 -> Stampa\n");
  printf("2 -> Stampa Invertito\n");
  printf("3 -> Stampa somma e media\n");
  printf("4 -> Stampa Pari\n");
  printf("5 -> Stampa Dispari\n");
  printf("6 -> Ricerca\n");
  printf("7 -> Elimina\n");
  printf("8 -> Alterni\n");
  printf("9 -> Ordinamento\n");
  printf("10 -> Esci\n");
}

void stampa(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void stampa_invertito(int arr[], int size) {
  for (int i = size - 1; i >= 0; i--) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void somma_media(int arr[], int size) {
  int somma = 0;
  for (int i = 0; i < size; i++) {
    somma += arr[i];
  }
  float media = (float)somma / size;
  printf("Somma: %d, Media: %.2f\n", somma, media);
}

void stampa_pari(int arr[], int size) {
  printf("Numeri pari: ");
  for (int i = 0; i < size; i++) {
    if (arr[i] % 2 == 0) {
      printf("%d ", arr[i]);
    }
  }
  printf("\n");
}

void stampa_dispari(int arr[], int size) {
  printf("Numeri dispari: ");
  for (int i = 0; i < size; i++) {
    if (arr[i] % 2 != 0) {
      printf("%d ", arr[i]);
    }
  }
  printf("\n");
}

void ricerca(int arr[], int size, int val) {
  bool found = false;
  for (int i = 0; i < size; i++) {
    if (arr[i] == val) {
      printf("Numero %d trovato alla posizione %d\n", val, i + 1);
      found = true;
      break;
    }
  }
  if (!found) {
    printf("Numero non trovato.\n");
  }
}

int elimina(int arr[], int size, int val) {
  int i;
  for (i = 0; i < size; i++) {
    if (arr[i] == val) {
      break;
    }
  }

  if (i < size) {
    for (int j = i; j < lungh - 1; j++) {
      arr[j] = arr[j + 1];
    }
    size--;
    printf("Numero %d eliminato.\n", val);
  } else {
    printf("Numero non trovato.\n");
  }

  return size;
}

void alterni(int arr[], int size) {
  for (int i = 0; i < size - 1; i += 2) {
    int temp = arr[i];
    arr[i] = arr[i + 1];
    arr[i + 1] = temp;
  }
  stampa(arr, size);
}

void ordinamento(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  stampa(arr, size);
}

int main() {
  int scelta, lungh = 0;
  bool esci = false;
  int numeri[DIM];

  srand(time(NULL)); // Initialize random number generator

  // Populating the array with random numbers
  printf("Inserire il numero di elementi nel vettore (max %d): ", DIM);
  scanf("%d", &size);
  if (size > DIM) {
    printf("Numero troppo grande, ridotto a %d.\n", DIM);
    size = DIM;
  }

  for (int i = 0; i < size; i++) {
    numeri[i] = rand() % 100; // Random numbers between 0 and 99
  }

  do {
    menu();
    printf("Inserisci la scelta:\n");
    scanf("%d", &scelta);
    switch (scelta) {
    case 1:
      stampa(numeri, size);
      break;
    case 2:
      stampa_invertito(numeri, size);
      break;
    case 3:
      somma_media(numeri, size);
      break;
    case 4:
      stampa_pari(numeri, size);
      break;
    case 5:
      stampa_dispari(numeri, size);
      break;
    case 6: {
      int val;
      printf("Inserisci il numero da cercare: ");
      scanf("%d", &val);
      ricerca(numeri, size, val);
      break;
    }
    case 7: {
      int val;
      printf("Inserisci il numero da eliminare: ");
      scanf("%d", &val);
      size = elimina(numeri, size, val);
      break;
    }
    case 8:
      alterni(numeri, size);
      break;
    case 9:
      ordinamento(numeri, size);
      break;
    case 10:
      esci = true;
      break;
    default:
      printf("Scelta errata.\n");
      break;
    }
  } while (!esci);

  return 0;
}
