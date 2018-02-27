#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// declare linked-list
struct Node {
  JOB job;
  struct Node *next;
};

typedef struct job {
  pid_t jobid; //pid of process
  char* name_id;
  int status;
} JOB;


int main(){
  //SIGINT, SIGTERM, SIGTTIN, SIGTTOU, SIGTSTP, SIGQUIT
  sigset_t set;
  sigprocmask();
  return 0;
} // main()

void signal_handler(){
  printf("%d\n", jobid);
  printf("Stopped       %s\n", name_id); //the name of the process child that stopped
} //signal_handler()

int execute(){
  pid_t pid;
  pid = fork();
  struct sigaction act;

  memset(&act, '/0',sizeof(act));

  if (pid < 0) { // Parent process
    //if your child process is bg, continue to accept commands
    //if (){ //struct job?

    act.sa_sigaction = &signal_handler;
    // print Stopped
    sigaction(SIGCHLD, &act, NULL);
    //add to job list

    }
    //else, wait()
  }
  else if (pid == 0){ //Child process
    //execute command and arguments
  }
  else {
    printf(Error forking.);
  }
} //execute()
