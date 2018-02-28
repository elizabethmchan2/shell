#include <string.h>
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
  pid_t job_id; //pid of process
  char* name_id;
  int status;
} JOB;

struct Node* head; //global head

// void init_linkedlist(){
//   struct Node* head = NULL;
//   struct Node* last = NULL;
// }

int main(){
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

  // parse() the command line
  // match the right command with the right function
    // if backgrounding, call backgrounding()

  // add_job();
  return 0;
} // main()

void signal_handler(){
  printf("%d\n", job_id);
  printf("Stopped       %s\n", name_id); //the name of the process child that stoppedstruct Node* last = NULL;
} // signal_handler()


void backgrounding(){ // what does backgrounding takes in ?
  pid_t pid;
  pid_t pgid;

  pid = fork();
  if (pid == 0){ //child
   signal(SIGINT, SIG_DFL);
   signal(SIGTERM, SIG_DFL);
   signal(SIGTTIN, SIG_DFL);
   signal(SIGTTOU, SIG_DFL);
   signal(SIGTSTP, SIG_DFL);
   signal(SIGQUIT, SIG_DFL);

   // setpgid(0,0); // create a new process group
                  // pgid? of child process => getppid()?
    JOB j;
    j = create_job(getpid(), char* nameID, 0);
    struct Node* last = NULL;
    append(&last, j);


 } // if
  else if (pid > 0){ //parent

    // somehow have to get the child process pid for first parameter
    // setpgid(child process' pid,);
    struct Node* check_node = head;
    while (check_node != NULL)
    {
        //printf("%d\n", node->job.job_id);
      if (check_node->job.job_id!=pid)  {
      //struct Node *start = NULL;
        JOB j;
        j = create_job(getpid(), char* nameID, 0);
        struct Node* last = NULL;
        append(&last, j);
    }
      check_node = check_node->next;
  }

  } // else if
  else {
    printf("Error forking\n");
  } // else

  // add child to the job linked-list
  // run, exec()?
  // when child process stops, register SIGCHLD, signal_handler with sigaction()

  pid_t pid;
  pid = fork();
  struct sigaction act;

  memset(&act, '/0', sizeof(act));

  if (pid < 0) { // Parent process
    // if your child process is bg, continue to accept commands
    // if (){ //struct job?

    act.sa_sigaction = &signal_handler;
    // print Stopped
    sigaction(SIGCHLD, &act, NULL);
    // add to job list

    }
    // else, wait()
  }
  else if (pid == 0){ //Child process
    // execute command and arguments
  }
  else {
    printf(Error forking.);
  }
} // execute()

// ctrl - c
