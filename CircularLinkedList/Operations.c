//Circular Doubly Linked List
//Imporvement: making length variable to avoid transverse O(n)
//2. No need to type cast when making a new node
#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;		//for saving reference of next node
	struct Node* prev;		// previous pointer's reference
} Node;


typedef struct Property{
	Node* head;		//for saving the pointer head
	int length;		// length saving
} Property;


/*
Insert At Head:
0.memory allocation failed
1. list is null 
2.nodes are present
Time Complexity: O(1) 
*/
int insertAtHead(Property* list,int value){
	
	Node* newNode=malloc(sizeof(Node));
	if(newNode==NULL) return 0; //mean memory allocation failed(a rare case)
	newNode->data=value;
	
	if(list->head==NULL){
		newNode->next=newNode;
		newNode->prev=newNode;
		
		list->head=newNode;
		list->length++;
		return 1;
		
	}else{
		Node* last=list->head->prev;
		Node* head=list->head;
		newNode->next=head;
		head->prev=newNode;
		
		last->next=newNode;
		newNode->prev=last;
		list->length++;
		
		list->head=newNode;
		return 1;		
	}
}


/*
Insert At last : node whose next will be head (bcz its circular)
1. List empty
0. Memory alloc failed
2. Nodes present so modify the links
Time complexity will be constant
*/
int insertAtLast(Property* list,int value){
	Node* newNode=malloc(sizeof(Node));
	if(newNode==NULL) return 0;
	newNode->data=value;
	
	if(list->head==NULL){
		newNode->next=newNode;
		newNode->prev=newNode;
		list->head=newNode;
		list->length++;
		return 1;
	}else{
		Node* last=list->head->prev;
		last->next=newNode;
		newNode->prev=last;
		
		newNode->next=list->head;
		list->head->prev=newNode;
		
		list->length++;
		return 1;
	}
}


/*
Insert At Position:
0. position is <=0 || position >length+1
1. List is empty 
	a.position is 1
	b.any other is invalid
2.List is not empty
	a.position is 1 then calling insert at head
	b.position is length+1 then calling insert at end
	c.transversing and find correct position to insert
	
Time Complexity: O(n) in worst case if we looped otherwise constant
*/
int insertAtPosition(Property* list,int value,int position){
	int length=list->length;
	if(position<=0 || position>length+1) return 0;	//invalid position
	if(list->head==NULL){
		if(position==1) return insertAtHead(list,value);
		else return 0;
	}
	else{
		if(position==1) return insertAtHead(list,value);
		else if(position ==length+1) return insertAtLast(list,value);
		else{
			Node* temp=list->head;
			int counter=1;
			while(temp->next!=list->head){
				if(counter+1==position) break;
				counter++;
				temp=temp->next;
			}
			Node* newNode=malloc(sizeof(Node));
			newNode->data=value;
			newNode->prev=temp;
			newNode->next=temp->next;
			
			temp->next=newNode;
			newNode->next->prev=newNode;
			
			list->length++;
			return 1;
		}
	}
}


/*Delete Head  Functions:
1.List is empty		then returning 1 for list is empty(or 0 to indicate operation not performed)
2. One node only	then delete it or leave at least one nodde
3. Many nodes		then deleting the head and second become head

Time Complexity : O(1) 
Space Complexity is also constant
*/
int deleteHead(Property* list){
	if(list->head==NULL) return 0;		//case 1
	else if(list->head->next==list->head){		//second case
		free(list->head);
		list->head=NULL;
		list->length--;
		return 1;
	}else{						//third case
		Node* last=list->head->prev;
		Node* target=list->head;
		last->next=target->next;
		target->next->prev=last;
		
		list->head=target->next;
		list->length--;
		
		free(target);
		return 1;
	}
}


/* Delete Last
Cases are same like delete head.
Time complexity: O(1)
*/
int deleteLast(Property* list){
	if(list->head==NULL) return 0; //mean no operation performed
	if(list->head->next==list->head){
		free(list->head);
		list->head=NULL;
		list->length--;
		return 1;
	}
	else{
		Node* target=list->head->prev;
		Node* newLast=target->prev;
		
		newLast->next=list->head;
		list->head->prev=newLast;
		
		list->length--;
		
		free(target);
		return 1;
	}
}


/* Delete At Specific Position:
1.List is empty
2.position is invalid( <=0 || >length )
3.Constant Operations:
	1.position 1 calling deleteHead
	2.position == length calling deleteLast
4. Transversing and deleting specific Node (n operations in worst case)
*/
int deleteAtPosition(Property* list,int position){
	int length=list->length;
	if(position<=0 || position>length ||list->head==NULL)
		return 0;
	else if(position==1){
		return deleteHead(list);
	}
	else if(position==length){
		return deleteLast(list);
	}
	else{
		Node* target=list->head;
		int counter=1;
		while(target->next!=list->head){
			if(counter==position) break;
			counter++;
			target=target->next;
		}
		//after loop, temp is at the target node
		target->prev->next=target->next;
		target->next->prev=target->prev;
		free(target);
		list->length--;
		return 1;
	}
}


/*  Optimized Delete at position
If position < mid transverse from start to that position
else if position > mid transverse in backward manner and less operations
This will perform n/2 operations( effecient in large lists)
Time Complexity: O(n/2) = O(n) 
*/
int deleteAtPositionOptimized(Property* list,int position){
	int length=list->length;
	if(position<=0 || position>length || list->head==NULL) return 0;
	else if (position==1){
		return deleteHead(list);
	}
	else if(position==length){
		return deleteLast(list);
	}else{
		int mid=length/2;
		if(position<=mid){
			Node* target=list->head;		//target intiially at zero
			int counter=1;
			while(counter!=position){	//running loop until reach the targeted node
				counter++;
				target=target->next;
			}
			
			target->prev->next=target->next;	//reference manipulation
			target->next->prev=target->prev;
			free(target);
			list->length--;				//decreasing length
			return 1;
		}
		else{			//mean position >mid 
			Node* target=list->head->prev;
			int counter=length;
			while(counter!=position){
				
				counter--;
				target=target->prev;
			}
			
			target->prev->next=target->next;
			target->next->prev=target->prev;
			free(target);
			list->length--;			
			return 1;
		}
	}
}


/* Search By Value
Return Cases:
	1. can return the position
	2. can return the address of node
Possible Cases:
*/
Node* searchByValue(Property* list,int value,int occurance){
	if(list->head==NULL || occurance==0) return NULL;
	Node* temp=list->head;
	int occurCounter=0;
	do{
		if(temp->data==value){
			occurCounter++;
			if(occurCounter==occurance) return temp;
		}
		temp=temp->next;
	}
	while(temp!=list->head);
	return NULL;	//in case if not found
}


/* Rotating List:
1. empty list then don't 
3.One node so no need
2. Nodes present
Time Complexity: Constant
*/
void rotateList(Property* list){
	if(list->head==NULL || list->head->next==list->head) return;
	else{
		list->head=list->head->next;
	}
}


int updateValue(Property* list, int value,int position){
	if(list->head==NULL || position<=0 || position>list->length ) return 0; //not founded the value
	Node* temp=list->head;
	int counter=1;
	while(counter!=position){
		counter++;
		temp=temp->next;
	}
	temp->data=value;
	return 1;
	//can also compare the position after finding mid and transverse reversely to reach to avoid n operations
}

/* Clear List:
Time complexity: O(n)
*/
void clearList(Property* list){
	Node* temp=list->head;
	Node* nextNode;
	int i;
	for(i=0;i<list->length;i++){
		nextNode=temp->next;
		free(temp);
		temp=nextNode;
	}
	list->head=NULL;
	list->length=0;
}


//O(n)
void printList(Property* list){
	if(list->head==NULL){
	printf("List is empty\n");
	return;
	}
	Node* temp=list->head;
	do{
		printf("%d -> ",temp->data);
		temp=temp->next;
	}while(temp!=list->head);
	printf("Head\n");
}


/* Splitting the List: list is made non-circular and divide into two halves
using slow and fast pointer approach
O(n)
*/
Node* splitList(Node* head){
	if(head==NULL || head->next==head) return NULL;
	Node* slow=head;
	Node* fast=head;
	while(fast->next!=head && fast->next->next!=head){
		slow=slow->next;
		fast=fast->next->next;
	}
	Node* secondHalf=slow->next;
	if (head->prev !=NULL) head->prev->next= NULL;
	
	slow->next=NULL;
	secondHalf->prev=NULL;
	head->prev=NULL;
	
	return secondHalf;
}


/*
Merging Two Sorted List:
2 -> 4 -> 9
1 -> 2 -> 5
1 -> 2 -> 2 -> 4 -> 5 -> 9
Time Complexity: O( n)
Space complexity is also linear O(n) due to call stack
*/
Node* mergeList(Node*head,Node* head2){
	if(!head) return head2;
	if(!head2) return head;
	
	if(head->data <= head2->data){
		head->next=mergeList(head->next,head2);
		
		if(head->next) head->next->prev=head; 	//if next node exists, next node's prev reference to back head
		head->prev= NULL;
		return head;
	}
	else{
		head2->next=mergeList(head,head2->next);
		if(head2->next) head2->next->prev=head2;
		
		
		head2->prev=NULL;
		return head2;
	}
}

/*
Merge Sort:
1. Spliting the list into two parts
2. merge two list after again nd again spliting and merging
3. return the list
Time Complexity : O(n log n): work doing in each level + number of level
*/
Node* mergeSort(Node* head){
	if(head==NULL || head->next==NULL ) return head;
	Node* secondHalf=splitList(head);	//spliting the list 
	
	head=mergeSort(head);		
	secondHalf=mergeSort(secondHalf);
	
	return mergeList(head,secondHalf);		//connect the parts
}


//Time Complexity: O(n)
void sortCircularList(Property* list){
	if(list==NULL || list->head==NULL || list->length<2) return;
	Node* sortedHead=mergeSort(list->head);
	
	Node* temp=sortedHead;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=sortedHead;
	sortedHead->prev=temp;
	list->head=sortedHead;	
}

int main(){
	Property* list=malloc(sizeof(Property));
	list->head=NULL;
	list->length=0;
	
	insertAtHead(list,10);
	insertAtLast(list,20);
	insertAtLast(list,30);
	insertAtLast(list,50);
	insertAtPosition(list,40,4);
	
	printList(list);
	rotateList(list);
	printf("Rotated List:\n");
	printList(list);
	
	return 0;
}







