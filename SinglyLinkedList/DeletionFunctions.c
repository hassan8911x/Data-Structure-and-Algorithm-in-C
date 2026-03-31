//Deletion Functions for Singly Linked List
#include<stdio.h>

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
		*head=*head->next;	//marking next the head
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
int calcLength(Node*head){		//Not passing pointer to pointer because pass by value is enough for simple transversal
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
    for (int i = 0; i < index - 1; i++) {
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





