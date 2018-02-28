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
#include <stdbool.h>

//each node is of typedef struct JOB
typedef struct {
  pid_t job_id;
  char* name_id;
  int status; //0 is stopped, 1 in running
  // int fg_bg; //0 for foreground, 1 for backgrounding
  // termios

}JOB;

/* A linked list node */
struct Node{
    JOB job;
    struct Node *next;
};

struct Node* head = NULL;

// void init_linkedlist(){
  // struct Node* head = NULL;
// }
//
// JOB create_job(pid_t jobID, char* nameID, int stat) {
//   JOB j;
//   j.job_id = jobID;
//   j.status = nameID;
//   j.name_id = stat;
//   return j;
// }


/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
void push(struct Node** head, JOB job, size_t data_size)
{
    // Allocate memory for node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->job  = job;
    new_node->next = (*head);

    // Change head pointer as new node is added at the beginning
    (*head)    = new_node;
} //end of push()


// *********************************************
void append(struct Node** head_ref, JOB job)
{
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
}
// *******************************************




/* Given a reference (pointer to pointer) to the head of a list
   and a key, deletes the first occurrence of key in linked list */
void deleteNode(struct Node **head_ref, int key)
{
    // Store head node
    struct Node* temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->job.status == key)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->job.status  != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory
}

bool exists(struct Node **head_ref, int key) {
  // int temp; //false
  while (head != NULL) {
    if (head->job.status!=key)  {
        return 1; //true
        // printf("job status %d\n",head->job.status);

      // } else {
      //
        break; //doesn't delete first node, but still appends to the end

      }
      head = head->next;

  }
  return 0;
}

/* Function to print nodes in a given linked list.*/
 void printList(struct Node *node)
 {
     while (node != NULL)
     {
        printf("%d\n", node->job.status);
        node = node->next;
         // printf("%s\n",node);
     }
 }

 // Function to print an integer
 void printInt(void *n)
 {
    printf(" %d", *(int *)n);
 }

 // Function to print a float
 void printFloat(void *f)
 {
   printf(" %f", *(float *)f);
 }
/* Driver program to test above function */
int main()
{

  // Create and print an int linked list
  JOB j1;
  // j1.job_id;
  j1.status = 10;
  append(&head, j1);
  JOB j2;
  j2.status = 40;
  append(&head, j2);
  JOB j3;
  j3.status = 50;
  append(&head, j3);
  JOB j4;
  j4.status = 60;
  append(&head, j4);
  JOB j5;
  j5.status = 70;
  append(&head, j5);

  // printList(head);
  // deleteNode(&head, 10);
  // printf("Created integer linked list is \n");
  // printList(head);

  // struct Node* check_node = head;
  // int status = 10;
  int status = 10;
  // int status = 40;
  // printf("%d\n", );

  if (exists(&head, status)==1) {
    // struct Node *start = NULL;
      // JOB j;
      // // j = create_job(getpid(), char* nameID, 0);
      // // struct Node* last = NULL;
      // // append(&last, j);
      JOB j3;
      j3.status = status;
      append(&head, j3);

  }



  printList(head);


  return 0;
}
