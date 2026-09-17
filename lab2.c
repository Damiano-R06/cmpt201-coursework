#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  char *buffer = NULL; // myString
  size_t allocated = 0;

  while (1) {
    printf("Enter programs to run. \n> ");

    ssize_t numChar = getline(&buffer, &allocated, stdin);

    if (numChar == -1) {
      perror("getline() failed");
      break;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    pid_t pid = fork();

    if (pid == 0) {
      execl(buffer, buffer, NULL);
      printf("Exec failure\n");
      exit(EXIT_FAILURE);
    } else {
      waitpid(pid, NULL, 0);

      printf("You typed: %s \n", buffer);
    }
  }

  free(buffer);
  buffer = NULL;

  return 0;
}
