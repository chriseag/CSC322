#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_ARGS 10

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  char *filename = argv[1];
  char line[MAX_LINE_LENGTH];
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Error: failed to open file %s\n", filename);
    exit(1);
  }

  pid_t pid, wait_pid;
  int status;

  while (fgets(line, MAX_LINE_LENGTH, fp)) {
    // Remove trailing newline character
    if (line[strlen(line)-1] == '\n') {
      line[strlen(line)-1] = '\0';
    }

    char *args[MAX_ARGS];
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid = fork();

    if (pid == -1) {
      printf("Error: failed to fork\n");
      exit(1);
    } else if (pid == 0) {
      // Child process
      if (execvp(args[0], args) == -1) {
        printf("Error: failed to execute command %s\n", args[0]);
        exit(1);
      }
    }
  }

  // Wait for all child processes to finish
  while ((wait_pid = wait(&status)) != -1);

  fclose(fp);
  return 0;
}
