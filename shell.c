//some code sourced from https://brennan.io/2015/01/16/write-a-shell-in-c/
//collaborated with Ju-Han, Kellie and Han

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MORE_BUFFER 64

#define INITIAL_BUFFER 1024

int running = 1;


// reads whole input line
char *read_line(void)
{
  int bufsize = INITIAL_BUFFER;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "error: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += INITIAL_BUFFER;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}




//takes in return value from read_line and splits the line
char **split_line(char *line)
{
  int bufsize = MORE_BUFFER;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "error: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n\a");
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += MORE_BUFFER;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "error: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n\a");
  }
  tokens[position] = NULL;
  return tokens;
}



//fork the child process and changes the running status (therefore changes while loop) if it does/doesn’t work
int fork_child(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1 || pid < 0) {
      perror("error");
    }
    exit(EXIT_FAILURE);
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

//executes the commands taken in from split_line function
int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  if (strcmp(*args,"exit") == 0) {
    running = 0;
    exit(EXIT_SUCCESS);
  }

  return fork_child(args);
}

//main control loop that runs everything
int main(int argc, char **argv) {

 char *line;
 char **args;
 int status;

 while(running) {
   printf("Welcome to your shell:  ");
   line = read_line();
   args = split_line(line);
   status = execute(args);

   free(line);
   free(args);
 }

  return 0;

}
