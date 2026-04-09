#include<stdio.h>
#include<stdlib.h>
/* Stack:
LIFO: Last-In-First-out
Operations are O(1)
only caring about top element (random access is restricted)
Using Singly linked list
*/
typedef struct Node{
	int data;
	struct Node* next;
}Node;

typedef struct Stack{
	Node* top;			//head of the list
	int length;
}Stack;


/*
Push:
1.list is empty (then making newnode's next as top which is already null and top reference to new node)
2.List is not empty (then newnode's next to top mean existing node and setting value)
Time Complexity: Constant
*/
int push(Stack* stack,int value){
	Node* newNode=malloc(sizeof(Node));
	if(newNode==NULL) return 0;
	
	newNode->data=value;
	newNode->next=stack->top;
	
	stack->length++;
	stack->top=newNode;
	return 1;
}


/*
Pop: Remove the top element and return its value
Constant Operation: O(1)
*/
int pop(Stack* stack){
	if(stack->top==NULL) return 0;
	Node* target=stack->top;
	int popValue=target->data;
	
	stack->top=target->next;
	stack->length--;
	free(target);
	return popValue;
}

//returning the top's value in O(1)
int peek(Stack* stack){
	if(stack->length==0) return -1;
	return stack->top->data;
}

int isEmpty(Stack* stack){
	return stack->length==0? 1: 0;
}

int stackSize(Stack* stack){
	return stack->length;
}

void clearStack(Stack* stack){
	if(stack->length==0) printf("Stack Already empty\n");
	Node* target=NULL;
	while(stack->top!=NULL){
		pop(stack);
	}
	stack->length=0;
	printf("Memory cleared\n");
}

int main(){
	Stack* stack=malloc(sizeof(Stack));
	stack->length=0;
	stack->top=NULL;
	
	int x=push(stack,10);
	int y=push(stack,20);
	int z=push(stack,30);
	
	printf("Top : %d\n",stack->top->data);
	printf("Length: %d\n",stack->length);
	printf("Popped: %d\n",pop(stack));
	printf("New Length: %d\n",stack->length);
	clearStack(stack);
	return 0;
}
