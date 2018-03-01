/* I don't have a parser, so I just need to assign to my input
I'm not very sure if backgrounding works
I also need my linked list to work with my backgrounding */



// This is the original parser for test 1 that I took out here
#define MORE_BUFFER 64
#define INITIAL_BUFFER 1024

// reads whole input line
char *read_line(void){
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
        fprintf(stderr, "error: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
} //readline()

//takes in return value from read_line and splits the line
char **split_line(char *line){

  //check if & exists first
  int bufsize = MORE_BUFFER;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  // char * pch;
  // pch=strchr(line,'&');
  // if (pch!=NULL) {
  //   while (pch!=NULL) {
  //     printf ("found at %ld\n",pch-line+1);
  //     goto_backgrounding();
  //     pch=strchr(pch+1,'&');
  //   }
  // } else {
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
  // }
  tokens[position] = NULL;
  return tokens;

  free(tokens);
} //split_line()

int fork_child(char **args){
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
} //fork_child

int execute(char **args){
  int i;
  if (args[0] == NULL) {
    return 1;
  }

  if (strcmp(*args,"exit") == 0) {
    exit(EXIT_SUCCESS);
  }

  return fork_child(args);
} //execute

int goto_backgrounding(char** args) {
  int j = 0;
  int num = 0;
  while(args[j] !=  NULL) {
    // printf("%s\n", args[j]);
    //IMPLEMENT ; THING HERE ///////////////////////////////////////--->
    char* pch;
    pch=strchr(args[j],'&');
    while (pch!=NULL){
      // printf ("found in %s at %d\n",args[j], pch-args[j]+1);
      num++;
      pch=strchr(pch+1,'&');
    }
    j++;
  }

  // char* pch;
  // pch=strchr(line,'&');
  // while (pch!=NULL){
  //   printf ("found at %d\n",pch-line+1);
  //   num++;
  //   pch=strchr(pch+1,'&');
  //
  // }
  // printf("num: %d\n", num);
  return num;

} //goto_backgrounding


//Lizzy's original part of parser inside void backgrounding(char** args){}
void backgrounding(char** args){

  // printf("working\n");

  //MAKE A NEW CHAR** THAT CONTAINS THE NEW ARGS TO RETURN AND THE FIRST IS THE FIRST TO PASS ITNO EXECVP
  //SECOND AND FURTHER IS ARGUMENTS

  // use instead to remove the &
  // https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
  int k = 0;
  while(args[k] !=  NULL) {
    // printf("in backgrounding: %s\n", args[k]);
    char* pch;
    pch=strchr(args[k],'&');
    if (pch!=NULL){
      // printf ("found in %s at %d\n",args[k], pch-args[k]);
      // printf("%s\n", args[k]);
      int bufsize = MORE_BUFFER;
      int position = 0;
      char **tokens = malloc(bufsize * sizeof(char*));
      char *token;

        if (!tokens) {
        fprintf(stderr, "error: allocation error\n");
        exit(EXIT_FAILURE);
      }

      token = strtok(args[k], "&");

      while (token != NULL) {
        tokens[position] = token;
        printf("%s\n", tokens[position]);
        position++;

        if (position >= bufsize) {
          bufsize += MORE_BUFFER;
          tokens = realloc(tokens, bufsize * sizeof(char*));
          if (!tokens) {
            fprintf(stderr, "error: allocation error\n");
            exit(EXIT_FAILURE);
          }
        }

        token = strtok(NULL, "&");
        tokens[position] = NULL;

      }
    pch=strchr(pch+1,'&');
    free(tokens);
    }
  k++;
  } //while
}
