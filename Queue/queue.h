#ifndef Queue_H
#define Queue_H

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct Queue{
	Node* front;
	Node* rear;
	int size;
}Queue;

Queue* initQueue();
int enqueue(Queue* queue,int value);
int isEmpty(Queue* queue);
int dequeue(Queue* queue,int* item);
int peek(Queue* queue,int* value);
void clearQueue(Queue* queue);

#endif
