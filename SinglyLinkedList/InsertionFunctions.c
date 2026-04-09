//Singly Linked List
#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;				//the element to store
	 struct Node* next;		//pointer of structure type for storing reference of next Node
} Node;

/*
Insert At Head's Possible Cases:
1. Memory allocation failed -> return response 
2. List is empty -> creating new node and making it the head
3. List is not empty -> creating new node and assigning as head

Return type :
can be int: 1 for done and 0 for fail
can be *head type if wanna return head
can be void without response
*/

//Time Complexity: Constant O(1)
int insertAtHead(Node** head,Node**tail,int value){
	Node* newNode=malloc(sizeof(Node));		//allocating memory for Node
	if(newNode==NULL){return 0;} 		 //case 1
	
	newNode->data=value;
	newNode->next=NULL;
	
	if(*head==NULL){		//case 2
		*head=newNode;
		*tail=newNode;
		return 1;
	}
	else{					//case 3
		newNode->next=*head;
		*head=newNode;
		return 1;
	}
}


/*
Insert At Tail's Possible Cases:
1. Memory allocation failed -> return response 
2. List is empty -> creating new node and making it the head and tail
3. List is not empty -> creating new node and adding to end and making it tail
*/

//Time Complexity: Constant O(1)
int insertAtTail(Node**head,Node**tail,int value){
	Node* newNode=malloc(sizeof(Node));
	if(newNode==NULL){return 0; }       //case 1
	
	newNode->data=value;
	newNode->next=NULL;
	
	if(*head==NULL){		//case 2
		*head=newNode;
		*tail=newNode;
		return 1;
	}
	else{
		(*tail)->next=newNode;   	//braces because -> has more percedence than * 
		*tail=newNode;
		return 1;
	}
	/* if not maintaining tail pointer, then time complexity will be O(n) due to transversal till end */
}


/*
Insertion in Middle's Possible Cases: 
Position mean index here. Numbering is starting from zero like array for resemblence
1. List is empty:
	a.Position is 0 -> calling function insertAtHead
	b.Position is not 0	->returning 0 bcz invalid position
2. List is not empty:
	a.Postion is 0  -> Inserting at haed 
	b.Position is length -> Inserting at tail ->bcz its 0 based indexing(length+1 in case of 1 based indexing)
	c.Position in middle -> Transverse through loop and find the corect position
*/

//Time Complexity: Worst Case: o(n) due to two time transvrese and Best case O(1)
int insertInMiddle(Node**head, Node**tail, int position, int value){
	Node* temp=*head;
	int length=0;
	while(temp!=NULL){
		length++;
		temp=temp->next;
	}
	
	if(position<0 || position>length){ 	// invalid case
		return 0;
		//or return msg in case of void
	}
	else if(*head==NULL && position ==0){	//case 1a
		int result=insertAtHead(head,tail,value);
		return result;
	}
	else if(*head==NULL){    //case 1b
		return 0;
	}
	else if( position==0){	//case 2a
		int result=insertAtHead(head,tail,value);
		return result;
	}
	else if(position==length){	//case 2b 
		int result=insertAtTail(head,tail,value);
		return result;
	}
	temp=*head;	
	int i=0;
	while(temp!=NULL && i<position-1){	//Dry run is in picture 
		i++;
		temp=temp->next;
	}
	if(temp!=NULL){
		Node* newNode=malloc(sizeof(Node));
		if(newNode==NULL){return 0;}
		newNode->data=value;
		
		newNode->next=temp->next;	//pre-saving next node's reference
		temp->next=newNode;
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	Node* head=NULL;
	Node* tail=NULL;
	int i=insertAtHead(&head,&tail,10);		
	int j=insertAtTail(&head,&tail,20);		
	i=insertAtTail(&head,&tail,30);
	i=insertAtTail(&head,&tail,40);
	
	i=insertInMiddle(&head,&tail,1,15);	
	i=insertInMiddle(&head,&tail,5,50); 
	
	Node* temp=head;
	while(temp!=NULL){
		printf("%d -> ",temp->data);
		temp=temp->next;
	}
	
	temp=head;
	while(head!=NULL){
		temp=head;
		head=head->next;
		free(temp);
	}
	free(tail);
}

//Indexing is starting from 0 so that it matches the array(don't know why but doing)
//Using too many if else to handle everything 















