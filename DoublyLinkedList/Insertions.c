//Doubly Linked List
//Every Algorithm's return type is 0 or 1 mean yes or no
//Can use the struct type and return pointer or can use void 
#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
} Node;


//Insert At Head 
//Time Complexity:O(1) 
//Space Complexity also constant O(1)
int insertAtHead(Node** head,Node**tail,int value){
	Node* newNode=(Node*) malloc(sizeof(Node));
	if(newNode==NULL){
		return 0; //can also return error msg or address of head depending on function return type
	}
	newNode->data=value;
	newNode->next=NULL;
	newNode->prev=NULL;
	
	if(*head==NULL){		//case 1: if list is empty
		*head=newNode;
		*tail=newNode;
		return 1;
	}
	else{				//case 2: when list has nodes
		newNode->next=*head;	/* new node's next is pointing to head */
		(*head)->prev=newNode;
		*head=newNode;			//head is now new node
		return 1;
	}
}


//Insert At Tail
//Time and Space Complexity are constant bcz no transverse
int insertAtTail(Node**head,Node**tail,int value){
	Node* newNode=(Node*) malloc(sizeof(Node));
	if(newNode==NULL){
		return 0;
	}
	newNode->data=value;
	newNode->next=NULL;
	newNode->prev=NULL;
	
	if(*head==NULL){
		*head=newNode;
		*tail=newNode;
	}
	else{
		(*tail)->next=newNode;	//enclosing *tail in braces due to percedence issue
		newNode->prev=*tail;
		*tail=newNode;
	}
	return 1;
}


//Utility function for Length
int findLength(Node* head){
	int length=0;
	while(head!=NULL){
		length++;
		head=head->next;
	}
	return length;
}


//Insert Node At Position : using 1 based indexing in contrast to array
/* Possible Cases:
0. Position <= 0 || position >length +1 then invalid
1.List Empty
	a.position is 1 then insert At Head
	b.position is any other then invalid
2.List Not empty
	a.position is length+1 then insert at tail(constant Oepration)
	b.Position is between then transverse
	
*/
//Time Complexity: O(2n): One for length and one for insertion
//Final is O(n) ignoring constant
//Space Complexity is constant O(1)
int insertAtPosition(Node**head,Node**tail,int value,int position){
	int length=findLength(*head);
	if(position<=0 || position>length+1){
		return 0;	
	}
	if(*head==NULL){
		if(position==1){
			int result=insertAtHead(head,tail,value);
			return result;
		}
		else{
			return 0;
		}
	}
	else{
		if(position==1){
			int result=insertAtHead(head,tail,value);
			return result;
		}
		else if(position==length+1){
			int result=insertAtTail(head,tail,value);
			return result;
		}
		else{
			Node* temp=*head;
			int counter=0;
			while(temp!=NULL && counter<position-2){
				counter++;
				temp=temp->next;
			}
			Node* newNode=(Node*) malloc(sizeof(Node));
			if(newNode==NULL){return 0;}
			newNode->data=value;
			newNode->next=NULL;
			newNode->prev=NULL;
			
			newNode->next=temp->next;
			newNode->next->prev=newNode;
			temp->next=newNode;
			newNode->prev=temp;
			return 1;
		}
	}
//Don't know why I consider too many extra conditions(overthinking problem!!)
}


//Redundant Inserting at position
int insertAtPositionMin(Node**head, Node**tail,int value,int position){
    int length = findLength(*head);
    if (position <= 0 || position > length + 1){
        return 0;
    }

    if (position == 1){
        return insertAtHead(head, tail, value);
    }
    if (position == length + 1) {
        return insertAtTail(head, tail, value);
    }

    Node* temp = *head;
    int i;
    for ( i = 1; i < position - 1; i++){
        temp = temp->next;
    }
    
    Node* newNode=(Node*)malloc(sizeof(Node));
    if (newNode ==NULL) {return 0;} 
    
    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL){
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    return 1;
}


//Deleting Head
/*
1.List is empty or have 1 Node then returning 0
2. List has nodes then deleting head and making next node the head
//Want to keep at least one node so therefore not deleting if there is one node
*/
//Time Conplexity: O(1) bcz its constant operation
//Space complexity is also Constant
int deleteHead(Node**head){
	if(*head==NULL || (*head)->next==NULL){
		return 0;	//or printing msg in case of void or return head on basis of return type
	}
	Node* temp=*head;
	*head=temp->next;
	(*head)->prev=NULL;
	free(temp);		//deleting the ex head to avoid memory leak
	return 1;
}


/*
Delete tail:
No need to transverse and reach the node before the tail to delete it like in 
Singly linked list . simply using tail's prev here
1. List is Empty or 1 node then don't delete
2. List has two or more Nodes then apply deletion
*/
//Time Complexity : O(1) bcz of previous pointer
int deleteTail(Node** tail){
	if(*tail==NULL || (*tail)->prev==NULL){
		return 0;
	}
	Node* temp=*tail;
	*tail=temp->prev;
	(*tail)->next=NULL;
	free(temp);
	return 1;
}


//Delete Node ByPosition:
/* 
1. To delete at specific node, i will calculate length and find mid. if positon is greater than
mid then i will transverse from tail to that node in reverse manner .
Then total operations: n for length and appromaximately n/2 for deletion

2. Second is starting from head and reach destination to delete
So total operations: n in worst case then using this approach

3. One way is to make the length variable in structure of node and increment at every insertion
but i will use 4 byte extra memory so not doing that
*/
//time complexity : O(n)
//Space complexity is constant
int deleteAtPosition(Node**head,Node**tail,int position){
	if(position<=0 || (*head)->next==NULL || *head==NULL ){
		return 0; 
	}
	if(position==1){
		int result=deleteHead(head);
		return result;
	}
	Node* temp=*head;
	int counter=1;
	while(temp!=NULL && counter<position){
		counter++;
		temp=temp->next;
	}
	if(temp!=NULL){
		if(temp->next!=NULL){		//to avoid segmentation fault of accessing temp->next if temp is at last node
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			free(temp);
			return 1;
		}
		else{
			*tail=(*tail)->prev;
			temp->prev->next=NULL;
			
			free(temp);
			return 1;
		}
	}
	return 0;
}


/*
Delete Node by value + Occurance
1. List is empty
	simply return
2. List is not empty
	transverse and delete according to occurance value
*/
int deleteByValueAndOccurance(Node**head,Node**tail,int value,int occurance){
	if(*head==NULL || occurance <=0){
		return 0;		//mean value not fouund or either occurance
	}
	
	Node* temp=*head;
	int occurCounter=0;
	while(temp!=NULL){
		if(temp->data==value){
			occurCounter++;
		}
		if(occurCounter==occurance){	//it braek the loop if condition met of occurance
			break;
		}
		temp=temp->next;
	}
	if(temp==NULL) return 0;	//checking if temp reached the null
	
	if(temp==*head){
		int result=deleteHead(head);
		return result;
	}
	if(temp==*tail){		/*if temp is tail, simply calling deleteTail */
		int result=deleteTail(tail);
		return result;
	}
	
		temp->next->prev=temp->prev;	//setting pointers if between head and tail
		temp->prev->next=temp->next;
		free(temp);		
		return 1;
//time complexity is linear in worst case and constant in best case  
//Space Complexity is constant
}


//Return the value by position( not index as in my singly linked list code)
//Time Complexity in worst case : Linear =O(n)
//Space Complexity is common
int findValueByPosition(Node* head,int position,int* result){
	//will not change head, no need to pass pointer to pointer
	int counter=0;
	while(head!=NULL && counter!=position){
		counter++;
		if(counter==position){	//if not break, even after increment , head will move by one 
			break;
		}
		head=head->next;
	}
	if(head!=NULL){
		*result=head->data;
		return 1;
	}else{
		/* if here return 0 , 0 maybe value at that position. o my god */
		/* using pointer to store the value and return type int for operation result*/
		*result=0;
		return 0;
	}
}

//Free List
void freeList(Node** head,Node**tail){
	Node* temp=*head;
	while(temp!=NULL){
		Node* target=temp;
		temp=temp->next;
		free(target);
	}
	
	*head=NULL;
	*tail=NULL;
}



//Time Complexity:Linear O(n) 
//Space Complexity constant compare to recursive which need call stack
void printList(Node* head){
	while(head!=NULL){
		printf("%d -> ",head->data);
		head=head->next;
	}
	printf("NULL");
}


void printListReverse(Node* tail){
	while(tail!=NULL){
		printf("%d -> ",tail->data);
		tail=tail->prev;
	}
	printf("NULL");
}


int main(){
	Node* head=NULL;
	Node* tail=NULL;
	int result=insertAtTail(&head,&tail,10);
	int result1=insertAtTail(&head,&tail,20);
	int result2=insertAtTail(&head,&tail,30);
	int result3=insertAtTail(&head,&tail,40);
	
	
	printList(head);
	return 0;
}

