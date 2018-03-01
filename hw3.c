#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

// declare linked-list
struct node {
  JOB job;
  struct Node *next;
} Node;

typedef struct job {
  pid_t job_id; // pid of process
  char* name_id;
  int fg_bg;
  //int status;
} JOB;

void s_handler(int signal, siginfo_t *info, void * t);
JOB create_job();
void backgrounding();

int main(){
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

  // 1. parse() the command line
  // 2. match "&" with backgrouding
  // 3. backgrounding()

  return 0;
} // main()


// !TEST THIS
void s_handler(int signal, siginfo_t *info, void * t){
  pid_t child_id = sig_info->si.pid;
  printf("Stopped       %s\n", child_id);
} // signal_handler()

JOB create_job(pid_t jobID, char* nameID) {
   JOB j;
   j.job_id = jobID;
   j.name_id = nameID;
   //j.status = ?
   return j;
} //create_job()

void backgrounding(){ //! what does backgrounding takes in ?
  pid_t pid;
  pid_t pgid;
  JOB j;

  pid = fork();

  // 2a. PARENT PROCESS
  if (pid > 0){
    // ? SHOULD 0. & 1. be inside of if (pid > 0) ?
    // 0. create_job()
    j = create_job(pid, argc[0]); //! Check with Lizzy, argc[0] might be declared in her program

    // block();
    // 1. ! add_job() to linked list
    // unblock();

    // 2. Handle SIGCHLD
    struct sigaction sa;
    sa.sa_sigaction= (void*)s_handler;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD,&sa, NULL);

    /* 3. ! Handle concurrency with linked-list updating
        . block() and unblock() wrapping around the critical region : updating the linked-list :

        block()
        update the list
        unblock()

    */
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

    /*3. exec child*/
    execvp(*tokens[0], *tokens[1]); // ! check if parameters are right,
                                    //*token is declared as char **tokens
  } // if
  else {printf("Error forking\n");} // else
} // backgrounding()

void block(){

} //block()
void unblock(){

} //unblock()

// ctrl - c
