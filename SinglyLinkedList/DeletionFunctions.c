//Deletion Functions for Singly Linked List
#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;

/*
Delete Head's Possible Cases:
1. List is empty -> then simply return 1
2. Single Node -> then either deleting it or warning about that
3. More than one node -> then deleting head and making next as head
*/

//Time Complexity: Constant O(1) in worst case
int removeHead(Node**head,Node**tail){
	if(*head==NULL){
		return 0;		//mean list is already empty
	}
	else if((*head)->next==NULL){	//enclosing head  bcz of percedence than ->
		free(*head);	//deleting single existing node (or can warn in case of void)
		*head=NULL;
		*tail=NULL;
		return 1;
	}
	else{
		Node* temp=*head;	//storing head
		*head=(*head)->next;	//marking next the head
		free(temp);			//freeing the memory 
		return 1;
	}
	
}

/*
Delete Tail's Possible Cases:
1. List is empty -> then  returning 0
2. Single Node -> then either deleting it or warning about that
3. More than one node -> then transversing to node before tail and deleting the tail
*/

int removeTail(Node**head,Node**tail){
	if(*head==NULL){
		return 0;
	}
	else if((*head)->next==NULL){	//either delete or leave at least one node
		free(*head);
		*head=NULL;
		*tail=NULL;
		return 1;
	}
	//Now transversing to end to node one node before tail
	Node* temp=*head;
	while(temp->next->next !=NULL){
		temp=temp->next;
	}
	free(temp->next);
	temp->next=NULL;
	*tail=temp;
	return 1;			
	//temp will be freed automatically because exists in stack.
}

//Helper Function to calculate length
int calcLength(Node*head){	
	int length=0;
	while(head!=NULL){
		length++;
		head=head->next;
	}
	return length;
}

/* 
Remove At Index's Possible cases:
1. List is empty -> simply return either 0 or 1 depending on scenario
2. List has one node
	a. position is 0 -> removing that node
	b. position is any other -> invalid position error mean returning 0
3. List has many nodes -> transverse to node before target and removing that
Can also use removeTail function if index is equal to length -1.
*/

//Time Complexity: Linear O(n) bcz of transversal
int removeAtIndex(Node** head, Node** tail, int index) {
    if (*head == NULL) {
        return 0;  
    }
    int length = calcLength(*head);
    if (index < 0 || index >= length) {
        return 0;   
    }
    
    if (index == 0) {
        return removeHead(head, tail);
    }
    if (index == length - 1) {
        return removeTail(head, tail);
    }
    
    Node* temp = *head;
    int i;
    for (i = 0; i < index - 1; i++) {
        temp = temp->next;
    }
    Node* target = temp->next;
    temp->next = target->next;
    free(target);
    return 1;
}

/*
Remove By Value's Possible Cases:
1. List is empty
2. Value exists -> then remove and can return index
3. Value does not exist -> then returning 0
*/
int removeByValue(Node**head,Node**tail,int value){
	if(*head==NULL){
		return 0;	//list is empty
	}
	else if((*head)->data==value){
		int result=removeHead(head,tail);
		return result;
	}
	
	Node* temp=*head;
	while(temp!=NULL && temp->next!=NULL){		//checking both cases to avoid segmentation faultt
		if(temp->next->data==value){
			Node* target=temp->next;
			temp->next=target->next;
			if(target==*tail){
				*tail=temp;
			}
			free(target);
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}

//Adding some helper Algorithms
void printList(Node* head){		//pass by value is enough for transversal only
	while(head!=NULL){
		printf("%d -> ",head->data);
		head=head->next;
	}
	printf("NULL");
}


/*Recursive Printing List
Time Complexity: Linear O(n)
Space Complexity: Linear O(n) bcz recursion uses call stack 
*/
void printListRec(Node* head){
	if(head==NULL){
		printf("NULL");
		return;
	}
	printf("%d -> ",head->data);
	printListRec(head->next);
}


/*Search By value + occurance
Worst Case Complexity: O(n) when need to transverse all nodes
Space complexity is constant O(1)
*/
int searchByValue(Node* head,int value, int occurance){
	int index=0;
	int occurCounter=0;
	while(head!=NULL){
		if(head->data==value){
			occurCounter++;
			if(occurCounter==occurance){
				return index;
			}
		}
		head=head->next;
		index++;
	}
	return -1;
}


/*
returning simple 0 for invalid index is not well bcz list may contain 0 value 
therefore, if operation return 1, then check result and if 0, mean index is invalid
Time Complexity : O(n) and space complexity is constant
*/
int searchByIndex(Node* head, int index,int* result){
	int counter=0;
	while(head!=NULL && counter!=index){
		counter++;
		head=head->next;
	}
	if(head!=NULL){
		*result=head->data;		//deferencing and writing value into address 
		return 1;
	}
	else{
		return 0;		
	}
}


/*
Updating Node Value By Index:
1. Empty list or invalid index
2. Index's node exists then simply returning
O(n) : Worst Case Complexity
*/
int UpdateValue(Node*head,int index, int newValue){
	int counter=0;
	while(head!=NULL){
		if(index==counter){
			head->data=newValue;
			return 1;
		}
		head=head->next;
		counter++;
	}
	return 0;
}

int isEmpty(Node* head){
	return(head==NULL)?  1:0;
}


int main(){
	Node* head=malloc(sizeof(Node));
	Node* tail=NULL;
	head->data=10;

	Node* secondNode=malloc(sizeof(Node));
	secondNode->data=20;

	Node* thirdNode =malloc(sizeof(Node));
	thirdNode->data=30;

	head->next=secondNode;
	secondNode->next=thirdNode;
	thirdNode->next= NULL;
	tail=thirdNode;
	
	printList(head);
	return 0;
}














