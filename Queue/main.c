#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

int main(){
	Queue* queue=initQueue();
	int* element_1=malloc(sizeof(int));
	*element_1=10;
	int enqueueResult1=enqueue(queue,element_1);
	
	int* element_2=malloc(sizeof(int));
	*element_2=20;
	int enqueueResult2=enqueue(queue,element_2);
	
	printf("Front: %d\nRear: %d\nSize:%d\n",*(int*)queue->front->data,*(int*)queue->rear->data,queue->size);
	
	int* dequeuedElement;
	*dequeuedElement;
	int dequeueResult=dequeue(queue,(void**)&dequeuedElement);
	
	printf("Dequeued Element : %d\nNewsize : %d\n",*(int*)dequeuedElement,queue->size);
	
	
	free(dequeuedElement);
	clearQueue(queue);
	free(queue);
	return 0;
}
