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

//each node is of typedef struct JOB
typedef struct {
  // pid_t job_id;
  // char* name_id;
  int status;

}JOB;

/* A linked list node */
struct Node{
    // Any data type can be stored in this node
    JOB job;

    struct Node *next;
};



/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
void push(struct Node** head_ref, JOB job, size_t data_size)
{
    // Allocate memory for node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->job  = job;
    new_node->next = (*head_ref);

    // Change head pointer as new node is added at the beginning
    (*head_ref)    = new_node;
}

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


/* Function to print nodes in a given linked list. fpitr is used
   to access the function to be used for printing current node data.
   Note that different data types need different specifier in printf() */
 void printList(struct Node *node, void (*fptr)(void *))
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
    struct Node *start = NULL;
    // Create and print an int linked list
    unsigned int_size = sizeof(int);
    JOB j1;
    j1.status = 10;
    push(&start, j1, int_size);
    JOB j2;
    j2.status = 40;
    push(&start, j2, int_size);

    printList(start, printInt);
    deleteNode(&start, 10);
    printf("Created integer linked list is \n");
    printList(start, printInt);


    return 0;
}
