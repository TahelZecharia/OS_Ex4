/*

*/
#pragma once

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <stdbool.h>
#include "malloc.h"

# define malloc(x) _malloc(x);
# define free(x) _free(x);

void push(char* val); 
void pop();
void display();
char* top();
char* stack_handler(char* str, char* input, char* output);

struct Node {
   char data[1024];
   struct Node *next;
};

struct Node* stack = NULL;

#define BACKLOG 10   // how many pending connections queue will hold

pthread_mutex_t lock;

char* stack_handler(char* str, char* input, char* output){

    pthread_mutex_lock(&lock);
    
    char* out = NULL;

    // a) PUSH:
    if(strcmp(str, "PUSH") == 0) {

        push(input);
    }

    // b) POP:
    else if(strcmp(str, "POP") == 0) {

        pop();
    }

    // c) TOP:
    else if(strcmp(str, "TOP") == 0) {

        out = top();
    }

    // d) DISPLAY FOR TESTING:
    else if(strcmp(str, "DISPLAY") == 0) {

        display(); 
    }
         
    else {

        printf("Invalid");
    }

    pthread_mutex_unlock(&lock);
    
    return out;
}

void push(char* val) {

    printf("*** PUSH FUNC ***\n");
    printf("The pushed element is :%s\n", val);
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newnode->data,val);
    newnode->next = stack;
    stack = newnode;

}

void pop() {

    printf("*** POP FUNC ***\n");

   if(stack==NULL){
        printf("Error : Trying to pop from empty stack\n");
        return;
   }
   
   else {
      
      printf("The popped element is : %s\n", stack->data);
      struct Node* copy = stack;
      stack = stack->next;
      free(copy);
   }
}

void display() {

    printf("*** DISPLAY FUNC ***\n");
   
   struct Node* ptr;
   
   if(stack==NULL){
        printf("Stack is empty\n");
        return;
   
   } else {
      
      ptr = stack;
      printf("Stack elements are:\n");
      
      while (ptr != NULL) {
         
         printf("%s", ptr->data);
         printf(", ");
         ptr = ptr->next;
      
      }
      printf("\n");
   }
}

char* top(){

    printf("*** TOP FUNC ***\n");
   
    if(stack==NULL){
        
        printf("Stack is empty\n");
        return NULL;
   
    } else {
       
        struct Node* ptr;
        ptr = stack;
        printf("The top element is: %s\n", ptr->data);
        return ptr->data;
    }
}
