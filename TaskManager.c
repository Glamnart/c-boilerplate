#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    char name[50];
    struct Task* next;
} Task;

Task* taskQueue = NULL; // FIFO
Task* undoStack = NULL; // LIFO

void enqueue(char* taskName);
void dequeue();
void pushUndo(char* taskName);
void undoLast();
void showTasks();

int main() {
    int choice;
    char task[50];

    do {
        printf("----------\n1. Add Task\n2. View Tasks\n3. Complete Task\n4. Undo Last Add\n5. Exit\n----------\nChoice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter Task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;
                enqueue(task);
                pushUndo(task);
                break;
            case 2:
                showTasks();
                break;
            case 3:
                dequeue();
                break;
            case 4:
                undoLast();
                break;
            case 5:
                printf("Exiting...\n");
                break;
        }
    } while (choice != 5);
    return 0; 
}

void enqueue(char* taskName)
{
    Task* n = malloc(sizeof(Task)); // Allocating space for a node
    if (n == NULL) // Incase there's no space in memory
    {
        printf("No space in memory.\n\n"); 
        return;
    }
    strcpy (n->name, taskName); // Saving the task in the node
    n->next = NULL; // Making sure the node is the end.
    if (taskQueue == NULL) // If queue is empty
    {
        taskQueue = n;
        printf("Added succesfully\n\n"); 
        return;         
    }
    Task* current = taskQueue; // Initialising a pointer that wil tranverse through the queue
    while (current->next != NULL) // Till it reaches the end
    {
        current = current->next;
    }
    current->next = n; // Connects the node
    printf("Added succesfully\n\n");
    return;
}

void pushUndo(char* taskName)
{
    Task*n = malloc(sizeof(Task)); // Allocating space for a node
      if (n == NULL) // Incase there's no space in memory
    {
        printf("No space in memory.\n\n");
        return;
    }
    strcpy(n->name, taskName); // Saving the task in the node
    n->next = undoStack; // Links new value to previous first 
    undoStack = n; // Links pointer to new value
    return;
}

void showTasks()
{
    if (taskQueue == NULL)// If queue is empty
    {
        printf("No tasks available.\n\n");
        return;
    }
    int i = 1;
    printf("\n.......To-Do List.......\n");
    for(Task* current = taskQueue; current != NULL; current = current->next) // Prints out each task till it reaches null
    {
        
        printf("%i. %s.\n", i, current->name);
        i++;   
    }
    printf("\n");
    return;
}

void dequeue()
{
    if (taskQueue == NULL) // If queue is empty
    {
        printf("No tasks available.\n\n");
        return;
    }
    Task* current_q = taskQueue; // Temp storage for first in queue's location
    taskQueue = taskQueue->next; // Links the pointer to the second in the queue
    free (current_q); // frees the first node

    if (undoStack == NULL) // If stack is empty
        return;
    if(undoStack->next == NULL) // If the stack only has one node
    {
        free(undoStack);
        undoStack = NULL;
        printf("Removed successfully\n\n");
        return;
    }
    Task* current_s = undoStack; // Initialising a pointer that wil tranverse through the stack
    while ((current_s->next)->next != NULL) // Till it reaches the end
    {
        current_s = current_s->next;
    }
    free (current_s->next); // frees the last node
    current_s->next = NULL;
    printf("Removed successfully\n\n");
    return;
    
}

void undoLast()
{
    if (undoStack == NULL) // If stack is empty
    {
        printf("No tasks available.\n\n");
        return;
    }
    Task* current_s = undoStack; // Temp storage for first in stack's location
    undoStack = undoStack->next; // Links the pointer to the second in the stack
    free (current_s); // frees the first node

    if (taskQueue == NULL) // If queue is empty
        return;
    if(taskQueue->next == NULL) // If the queue only has one node
    {
        free(taskQueue);
        taskQueue = NULL;
        printf("Removed successfully\n\n");
        return;
    }
    Task* current_q = taskQueue; // Initialising a pointer that wil tranverse through the queue
    while ((current_q->next)->next != NULL) // Till it reaches the end
    {
        current_q = current_q->next;
    }
    free (current_q->next); // frees the last node
    current_q->next = NULL;
    printf("Removed successfully\n\n");
    return;
}