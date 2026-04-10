#include<stdio.h>
#include "queue.h"

int main(){
	Queue* queue=initQueue();
	int x=enqueue(queue,10);
	int y=enqueue(queue,20);
	int z=enqueue(queue,30);
	
	printf("Front: %d and Length: %d\n",queue->front->data,queue->size);
	printf("Rear: %d\n",queue->rear->data);
	
	int dequeueItem=0;
	int zx=dequeue(queue,&dequeueItem);
	if(z!=0){
		printf("Dequeued: %d and now size is: %d",dequeueItem,queue->size);
		
	}
	return 0;
}

