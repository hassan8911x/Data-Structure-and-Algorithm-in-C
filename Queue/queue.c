//Queue : Linear Data structure 
//FIFO: First_In_FIRST_OUT
#include "queue.h"
#include<stdlib.h>


/* Initializing Queue (allocating memory) */
Queue* initQueue(){
	Queue* q=malloc(sizeof(Queue));
	if(q==NULL) return NULL;
	q->front=NULL;
	q->rear=NULL;
	q->size=0;
	return q;
}

//Checking if queue is empty: Operation is constant
int isEmpty(Queue* queue){
	if(queue->size==0) return 1;
	else return 0;
}

/*Time Complexity: O(1)
*/
int enqueue(Queue* queue,void* value){
	Node* newNode=malloc(sizeof(Node));
	if(newNode==NULL) return 0;
	
	newNode->data=value;
	newNode->next=NULL;
	
	if(queue->size==0){
		queue->front=newNode;
		queue->rear=newNode;
		queue->size++;
		return 1;
	}
	queue->rear->next=newNode;
	queue->rear=newNode;
	queue->size++;
	return 1;
}


/*
function's return type is for the operation success flag
returned value is stored in the pointer if passed
*/
int dequeue(Queue* queue,void** item){
	if(queue->size==0) return 0;
	Node* target=queue->front;		//marking front as target for deletion
	*item=target->data;			//storing for deletion
	
	queue->front=queue->front->next;	//moving fornt one step 
	queue->size--;
	
	if(queue->size==0) queue->rear=NULL;	//if size is zero, then marking the rear also null(avoiding dangling pointer)
	
	free(target);
	return 1;
	//constant operations so time complexity: O(1)
}


//Returning the front's data
//Here problem is that -1 may be the value of the front then its ambiguous to return the -1 
//therefore int can be the operation flag and value can be checked by passing the varible
int peek(Queue* queue,void** value){
	if(queue->size==0){
		return 0;
	}
	*value=queue->front->data;
	return 1;
}

int clearQueue(Queue* queue){
	while(queue->front!=NULL){
		Node* target=queue->front;
		queue->front=target->next;
		free(target->data);
		free(target);
	}
	queue->front=NULL;
	queue->rear=NULL;
	queue->size=0;
	return 1;
}









