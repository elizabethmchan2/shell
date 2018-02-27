//some code sourced from https://brennan.io/2015/01/16/write-a-shell-in-c/
//partner with Han

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
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MORE_BUFFER 64

#define INITIAL_BUFFER 1024

int *toks[];

#ifndef _INIT_TOKENIZER_H_
#define _INIT_TOKENIZER_H_


int running = 1;

typedef struct tokenizer {
  char *str; //the string to parse
  char *pos; //position in string

}TOKENIZER;

char *get_next_token(TOKENIZER *tokenizer) {
  // if current char is a delimiter, just return it
  // else go until next char is a delimiter
  // return the substring without white spaces
  // return NULL when string ends
  // if (isalpha(tokenizer->str) || isdigit(tokenizer->str)) {
  //   return tokenizer->str;
  // } else {
//
  // }

}

int parse(char *argv[]) { //returns number of tokens

  int i = 0;
  int n = 0;
  char* line;
  line=readline("welcome to the shell: ");
  //ctrl-d
  if (line == NULL) {
    return 0;
  }
  //newline
  if (strcmp(line,"") == 0) {
    return 0;
  }

  //add_history if you want
  char* t;
  t = init_tokenizer(line);
  //how many tokens
  while(get_next_token(t) != NULL) {
    n++;
  }
  //allocate pointers to tokens
  //+1 for the ending NULL
  toks = (char**);
  malloc(sizeof(char*)*(n+1));
  //start from the beginning again
  t = init_tokenizer(line);
  while ((toks[i++]=get_next_token(t)) ! = NULL) {
    return n;
  }


}



//main control loop that runs everything
int main(int argc, char **argv) {

  // TOKENIZER *token;
  // token->str = "hello - $ bitch";
  // printf("%s\n", token->str);

 while(running) {
   printf("Welcome to your shell:  ");
   parse(argv);
 }

  return 0;

}



// #include <setjmp.h>
// #include <errno.h>
// #include <error.h>
// #include <getopt.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>
//
// sigjmp_buf ctrlc_buf;
//
// void handle_signals(int signo) {
//   if (signo == SIGINT) {
//     printf("You pressed Ctrl+C\n");
//     siglongjmp(ctrlc_buf, 1);
//   }
// }
//
// int main (int argc, char **argv)
// {
//    //printf("path is: %s\n", path_string);
//   char * input;
//   char * shell_prompt = "i-shell> ";
//   if (signal(SIGINT, handle_signals) == SIG_ERR) {
//     printf("failed to register interrupts with kernel\n");
//   }
//
//   //set up custom completer and associated data strucutres
//   // setup_readline();
//
//   while ( sigsetjmp( ctrlc_buf, 1 ) != 0 );
//
//   while (1)
//   {
//     input = readline(shell_prompt);
//     if (!input)
//       break;
//     add_history(input);
//
//     //do something with the code
//     // execute_command(input);
//
//   }
//   return 0;
// }
