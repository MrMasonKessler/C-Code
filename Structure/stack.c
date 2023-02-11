#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//This represents a node that will be in my stack
struct node{
    int data;
    struct node *next;
};
//We talked about typedef in class, and it seemed more convenient than having to write out the full thing each time
typedef struct node node;


//This defines the top node in the list, which originially starts as null.
node *top;


//These are my function prototypes
void initialize();
void push(int value);
int pop();
int first();
int isempty();
void show(node *head);


//Does tests in order to fulfill screenshot requirements
int main(){
    initialize();
    show(top);
    push(10);
    show(top);
    push(20);
    show(top);
    push(30);
    show(top);
    pop();
    show(top);
    push(40);
    show(top);
    pop();
    show(top);
    pop();
    show(top);
    push(50);
    show(top);
    return 0;
}


//This actually starts the top node by setting it to null.
//This allows for the nodes in my stack to start being read.
void initialize(){
    top = NULL;
}


//Puts some int value onto the top of the stack
void push(int value){
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp -> data = value;
    tmp -> next = top;
    top = tmp;
}


int pop(){
    node *tmp;
    int n;
    tmp = top;
    n = tmp->data;
    top = top->next;
    free(tmp);
    return n;
}


int first(){
    return top->data;
}


int isempty(){
    return top==NULL;
}


void show(node *head){
    if(head == NULL){
        printf("NULL\n");
    }
    else{
        printf("%d\t", head -> data);
        show(head->next);
    }
}



