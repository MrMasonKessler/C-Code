#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node{
    int data;
    struct node *next;
};
typedef struct node node;




struct queue{
    int size;
    node *front;
    node *back;
};
typedef struct queue queue;




struct queue* initialize();
void enqueue(int value, queue *q);
int dequeue();
int first();
int isempty();
void show(node *head);
void getsize();




int main(){
    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);
    show(q->front);
    enqueue(10,q);
    show(q->front);
    enqueue(20,q);
    show(q->front);
    enqueue(30,q);
    show(q->front);
    dequeue(q);
    show(q->front);
    enqueue(40,q);
    show(q->front);
    dequeue(q);
    show(q->front);
    dequeue(q);
    show(q->front);
    enqueue(50,q);
    show(q->front);
    return 0;
}




struct queue* initialize(){
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
    queue->size=0;
    queue->front=NULL;
    queue->back=NULL;
    return queue;
}




void getsize(queue *q){
    printf("The size of the queue is: %c\n",q->size);
}




void enqueue(int value, queue *q){
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp -> data = value;
    tmp -> next = NULL;
    if(!isempty(q)){
        q->back->next = tmp;
        q->back=tmp;
    }
    else{
        q->front=tmp;
        q->back=tmp;
    }
    q->size++;
}




int dequeue(queue *q){
    node *tmp;
    node* result = q->front->next;
    tmp = q->front;
    q->front = q->front->next;
    q->size--;
    free(tmp);
    return result->data;
}




int first(queue *q){
    return q->front->data;
}




int isempty(queue *q){
    return q->back==NULL;
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



