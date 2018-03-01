// test1:
// Han's Notes:
//    I'm taking out the parser and strictly testing my backgrounding and linked-list job

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>
#include <sys/types.h>
#include <ctype.h>

#include "ll.h"

void backgrounding(char** args);


typedef struct{
  pid_t job_id;
  char* name_id;
  int status; //0 is suspended, 1 is running;
  int fg_or_bg; //0 is fg, 1 is bg
} JOB;

struct Node {
  JOB job;
  struct Node *next;
};

struct Node* head = NULL;


/******************************************/ //PARSING START
/******************************************/ //PARSING END


/******************************************/ //LINKED LIST STARTS
JOB create_job(pid_t job_id, char* name_id) {
  //, int status, int fg_or_bg
   JOB j;
   j.job_id = job_id;
   j.name_id = name_id;
   // j.status = status;
   // j.fg_or_bg = fg_or_bg;
   return j;

} //create_job()

/******************************************/ //LINKED LIST ENDS


/******************************************/ //BACKGROUNDING STARTS
// !TEST THIS
void s_handler(int signal, siginfo_t *info, void * t){
  pid_t child_id = info->si_pid;
  printf("Stopped       %s\n", child_id);
} // signal_handler()

void block(sigset_t sig){
  sigprocmask(SIG_BLOCK,&sig,NULL);
} //block()

void unblock(sigset_t sig){
  sigprocmask(SIG_UNBLOCK,&sig,NULL);
} //unblock()

void backgrounding(char** args){
    pid_t pid;
    pid_t pgid;
    JOB j;

    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig, SIGCHLD);

    pid = fork();

    // 2a. PARENT PROCESS
    if (pid > 0){
      // ? SHOULD 0. & 1. be inside of if (pid > 0) ?
      // 0. create_job()
      //j = create_job(pid, "emacs"); //! Check with Lizzy, argc[0] might be declared in her program

      // 2. ! Handle concurrency with linked-list updating
      // know: pid is now the child process pid
      block(sig);
      create_job(); //is this the right place to put create_job()?
      append(&head, pid);
      unblock(sig);


      // The parent removes job when the child terminates
      // How do we know when the child terminates?
      // When the OS sends signal SIGCHLD to the parent process

      // Does that means we have to handle remove_job() in SIGCHLD handler ?
      // But first you have to find out if the child actually terminated, because
      block(sig);
      // remove_job()
      unblock(sig);

      // 3. Handle SIGCHLD
      struct sigaction sa;
      memset(&sa,0,sizeof(sa));
      sa.sa_sigaction= (void*)s_handler;
      sa.sa_flags = SA_RESTART | SA_SIGINFO;
      sigaction(SIGCHLD,&sa, NULL);
    } //if

    // 2b. CHILD PROCESS
    else if (pid == 0){ // CHILD PROCESS
      /*1. Set signums back to default */
      signal(SIGINT, SIG_DFL);
      signal(SIGTERM, SIG_DFL);
      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);

       /*2. setpgid(0,0);
            a. create a new process group
          (?) pgid? of child process => getppid()? */


  //****************************CHECKED BACKGROUNDING
      // check if & exists first
  //     char* line = "&";
  //     int bufsize = MORE_BUFFER;
  //     int position = 0;
  //     char **tests = malloc(bufsize * sizeof(char*)); //pointer to the array of string char
  //     char *test;
  //     char *end_pointer = NULL;
  //
  //       // if (!tests) {
  //       //   fprintf(stderr, "error: allocation error\n");
  //       //   exit(EXIT_FAILURE);
  //       // }
  //
  //     test = strtok(line, " \t\r\n\a");
  //     while (test != NULL) {
  //       tests[position] = test;
  //       position++;
  //       test = strtok(NULL, " \t\r\n\a");
  //     }//while
  //
  //     //when you have reached the end of tests, put a null pointer at the end of tests
  //     tests[position] = end_pointer;
  //
  //     // execvp("./h",tests);
  // //*********************************8888888
  //     // execvp("")
  //     free(tests);
      free(args);
    } // else if
    else {printf("Error forking\n");} // else
} //backgrounding()

/******************************************/ //BACKGROUNDING ENDS

/******************************************/ //MAIN STARTS
  int main(int argc, char **argv) {
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    char *line;
    char **args;
    int status = 0;

   do {
     printf("Welcome to your shell:  ");
     line = read_line();
     args = split_line(line);
     if (goto_backgrounding(args) > 0) {
       backgrounding(args);
     } else {
     status = execute(args);
     }
     free(line);
     free(args);
   } while(status);

     // 1. parse() the command line
     // 2. match "&" with backgrouding
     // 3. backgrounding()
     return 0;

  } // main()
/******************************************/ //MAIN ENDS
