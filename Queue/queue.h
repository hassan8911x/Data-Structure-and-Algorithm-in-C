#ifndef Queue_H
#define Queue_H

typedef struct Node{
	void* data;		
	struct Node* next;
} Node;

typedef struct Queue{
	Node* front;
	Node* rear;
	int size;
}Queue;

Queue* initQueue();
int enqueue(Queue* queue,void* value);
int isEmpty(Queue* queue);
int dequeue(Queue* queue,void** item);
int peek(Queue* queue,void** value);
int clearQueue(Queue* queue);

#endif
