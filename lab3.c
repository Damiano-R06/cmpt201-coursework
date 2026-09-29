#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_word(char *words[], int *count, const char *buffer) {

  words[*count] = malloc(strlen(buffer) + 1);
  strcpy(words[*count], buffer);

  (*count)++;
}

void printWords(char *words[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s", words[i]);
  }
}

void freeWords(char *words[], int count) {
  for (int i = 0; i < count; i++) {
    free(words[i]);
  }
}

int main(void) {
  char *words[5];
  int count = 0;

  char *buffer = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter input: ");

    if (getline(&buffer, &size, stdin) == -1) {
      break;
    }

    add_word(words, &count, buffer);

    if (strcmp(buffer, "print\n") == 0) {
      printWords(words, count);
    }
  }

  free(buffer);
  freeWords(words, count);
}
