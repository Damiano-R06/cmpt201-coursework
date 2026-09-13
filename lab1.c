#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char *buffer = NULL;
  size_t sizeAllocated = 0;

  printf("Please enter some text: ");

  ssize_t numChar = getline(&buffer, &sizeAllocated, stdin);

  if (numChar == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  char *saveptr;
  char *token = strtok_r(buffer, " \n", &saveptr);

  if (token == NULL) {
    printf("No tokens found.");
    exit(EXIT_FAILURE);
  }

  printf("Tokens:\n");

  while (token != NULL) {
    printf("%s\n", token);

    token = strtok_r(NULL, " \n", &saveptr);
  }

  free(buffer);
  buffer = NULL;

  return 0;
}
