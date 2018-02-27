// C program for generic linked list
//pulled from https://www.geeksforgeeks.org/generic-linked-list-in-c-2/
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

/* A linked list node */
struct Node
{
    // Any data type can be stored in this node
    JOB job;

    struct Node *next;
};

//each node is of typedef struct JOB
typdef struct JOB {
  // pid_t job_id;
  // char* name_id;
  int status;

}JOB;

/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
void push(struct Node** head_ref, JOB job, size_t data_size)
{
    // Allocate memory for node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->job  = job;
    new_node->next = (*head_ref);

    // // Copy contents of new_data to newly allocated memory.
    // // Assumption: char takes 1 byte.
    // int i;
    // for (i=0; i<data_size; i++)
    //     *(char *)(new_node->data + i) = *(char *)(new_data + i);

    // Change head pointer as new node is added at the beginning
    (*head_ref)    = new_node;
}

/* Function to print nodes in a given linked list. fpitr is used
   to access the function to be used for printing current node data.
   Note that different data types need different specifier in printf() */
void printList(struct Node *node, void (*fptr)(void *))
{
  struct node *temp;
  temp=start;
  while(temp!=NULL)
  {
  printf("%d",temp->job);
  temp=temp->next;
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
    struct Node *start = NULL;

    // Create and print an int linked list
    unsigned int_size = sizeof(int);
    // int arr[] = {10, 20, 30, 40, 50}, i;
    // for (i=4; i>=0; i--)
    JOB j;
    j->status = 10;
    push(&start, j, int_size);
    printf("Created integer linked list is \n");
    printList(start, printInt);


    return 0;
}
