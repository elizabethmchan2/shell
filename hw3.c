//some code sourced from https://brennan.io/2015/01/16/write-a-shell-in-c/
//partner with Han
//emacs -nw hw4.c&
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

void backgrounding(char** args);

/******************************************/ //PARSING START

#define MORE_BUFFER 64

#define INITIAL_BUFFER 1024

typedef struct{
  pid_t job_id;
  char* name_id;
  int status; //0 is suspended, 1 is running;
  int fg_or_bg; //0 is fg, 1 is bg
} JOB;

// declare linked-list
struct Node {
  JOB job;
  struct Node *next;
};

struct Node* head = NULL;//global head

// void init_linkedlist(){
//   struct Node* head = NULL;
//   struct Node* last = NULL;
// }

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
}

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
}

//fork the child process and changes the running status (therefore changes while loop) if it does/doesn’t work
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
}

//executes the commands taken in from split_line function
int execute(char **args){
  int i;
  if (args[0] == NULL) {
    return 1;
  }

  if (strcmp(*args,"exit") == 0) {
    exit(EXIT_SUCCESS);
  }

  return fork_child(args);
}


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

// Add new job to end of linked list
void append(struct Node** head_ref, JOB job){
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = *head_ref;  /* used in step 5*/

    new_node->job = job;

    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
} //append

void deleteNode(struct Node **head_ref, pid_t job_id){
    // Store head node
    struct Node* temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->job.job_id == job_id) // if (temp != NULL && temp->job.job_id == job_id)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->job.job_id  != job_id)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory
} //deleteNode

void printList(struct Node *node){
   while (node != NULL)
   {
      printf("%d\n", node->job.job_id);
      node = node->next;
       // printf("%s\n",node);
   }
} //printList

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

}

void backgrounding(char** args){ //! what does backgrounding takes in ?
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
  }



//   pid_t pid;
//   pid_t pgid;
//   JOB j;
//
//   sigset_t sig;
//   sigemptyset(&sig);
//   sigaddset(&sig, SIGCHLD);
//
//   pid = fork();
//
//   // 2a. PARENT PROCESS
//   if (pid > 0){
//     // ? SHOULD 0. & 1. be inside of if (pid > 0) ?
//     // 0. create_job()
//     //j = create_job(pid, "emacs"); //! Check with Lizzy, argc[0] might be declared in her program
//
//     /* 2. ! Handle concurrency with linked-list updating
//         . block() and unblock() wrapping around the critical region : updating the linked-list :
//         block()
//         update the list
//         unblock()*/
//
//     //block(sig);
//     // 1. ! add_job() to linked list
//     //unblock(sig);
//
//     // 3. Handle SIGCHLD
//     struct sigaction sa;
//     memset(&sa,0,sizeof(sa));
//     sa.sa_sigaction= (void*)s_handler;
//     sa.sa_flags = SA_RESTART | SA_SIGINFO;
//     sigaction(SIGCHLD,&sa, NULL);
//   } //if
//
//   // 2b. CHILD PROCESS
//   else if (pid == 0){ // CHILD PROCESS
//     /*1. Set signums back to default */
//     signal(SIGINT, SIG_DFL);
//     signal(SIGTERM, SIG_DFL);
//     signal(SIGTTIN, SIG_DFL);
//     signal(SIGTTOU, SIG_DFL);
//     signal(SIGTSTP, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
//
//      /*2. setpgid(0,0);
//           a. create a new process group
//         (?) pgid? of child process => getppid()? */
//
//
// //****************************CHECKED BACKGROUNDING
//     // check if & exists first
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
//
//
//     free(tests);
//     free(args);
  // } // else if
  // else {printf("Error forking\n");} // else
} //
/******************************************/ //BACKGROUNDING ENDS



/******************************************/ //MAIN STARTS
//main control loop that runs everything
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

// The parent removes job when the child terminates
// How do we know when the child terminates?
//
// When the OS sends signal SIGCHLD to the parent process

// Does that means we have to handle remove_job() in SIGCHLD handler ?
// But first you have to find out if the child actually terminated, because
