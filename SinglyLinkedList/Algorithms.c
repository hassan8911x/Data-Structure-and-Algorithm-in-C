#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;	
} Node;

int insertAtTail(Node**head,Node**tail,int value){
	Node* newNode=(Node*) malloc(sizeof(Node));
	if(newNode==NULL){return 0; } 
	
	newNode->data=value;
	newNode->next=NULL;
	
	if(*head==NULL){	
		*head=newNode;
		*tail=newNode;
		return 1;
	}
	else{
		(*tail)->next=newNode;   
		*tail=newNode;
		return 1;
	}
}

void printList(Node* head){
	while(head!=NULL){
		printf("%d -> ", head->data);
		head=head->next;
	}
	printf("NULL\n");
}
//Reversing List
//Time Complexity:O(n) bcz in worst case , it will run n time
//No auxiliary space increasing so space complexity is constant O(1)
Node* reverseList(Node**head,Node**tail){
	if(*head==NULL){	//empty case 
		return NULL;
	}
	Node* prev=NULL;	
	Node* curr=*head;	
	Node* next=NULL;	//for storing remaining list to avoid loss
	
	*tail=*head;		
	//while current is not null, next is storing remaining list 
	//prev is storing previous node's reference to transform the connection
	//then prev moves one step and then current also
	while(curr!=NULL){
		next=curr->next;	
		curr->next=prev;
		prev=curr;
		curr=next;
	}
	*head=prev;	
	return *head;	//when head will NULL and loop ends, previous pointer will be at last node so its new head
}


//Recursive Reverse List Function
//Time Complexity: Linear O(n)
//Space Complexity: O(n) bcz of call stack of recursion
Node* reverseListRec(Node**head,Node**tail){
	if(*head==NULL || (*head)->next==NULL){
	*tail=*head;	
	return *head;	//returning when head is last node
	}
	Node* newHead=reverseListRec(&(*head)->next,tail);	//passing addresss of the deferenced next
	(*head)->next->next=*head;	//changing connection
	(*head)->next=NULL;
	return newHead;			//returning first(after reverse) as new head
}

/*
Merging two sorted Lists:
2 -> 9 -> 11 
1 -> 3 -> 9
1 -> 2 -> 3 -> 9 -> 9 -> 11
Idea: Taking two heads and including them on basis of smaller value
Modifying real lists
*/
Node* mergeList(Node* head1, Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    if (head1->data <= head2->data) {
        head1->next = mergeList(head1->next, head2);
        return head1;
    } else
	{head2->next = mergeList (head1, head2->next);
    	return head2;
    }
}

int main(){
	Node* head=NULL;
	Node* tail=NULL;
	int first=insertAtTail(&head,&tail,10);
	int second=insertAtTail(&head,&tail,20);
	int third=insertAtTail(&head,&tail,30);
	
	Node* head2=NULL;
	Node* tail2=NULL;
	int x=insertAtTail(&head2,&tail2,15);
	int xssecond=insertAtTail(&head2,&tail2,25);
	int tfdhird=insertAtTail(&head2,&tail2,36);
	
	Node* result= mergeList(head,head2);
	printList(result);
//
//	printList(head);
//	reverseList(&head , &tail);
//	printList(head);
	return 0;
}







