#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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


//problem: Os, 1s, 2s
//Given list containing 0, 1 and 2
//Sort the List
//Solution: Counting every 0, 1 , and 2 and then changing values
Node* threeProblem(Node* head){	
	Node* temp=head;
	int zeroCounter=0;
	int oneCounter=0;
	int twoCounter=0;
	
	while(temp!=NULL){
		if(temp->data==0){
			zeroCounter++;
		}
		else if(temp->data==1){
			oneCounter++;
		}
		else{
			twoCounter++;
		}
		temp=temp->next;	//moving temp to next
	}
	temp=head;
	while(temp!=NULL){		//while not reaching end, swaping values
		if(zeroCounter>0){	//first writing all zeros
			temp->data=0;
			zeroCounter--;
		}
		else if(oneCounter>0){	//if zero finished, then 1
			temp->data=1;	
			oneCounter--;
		}
		else{					//remaining all are 2 so insert them
			temp->data=2;
			twoCounter--; 		//reduant 
		}
		temp=temp->next;
	}
	return head;
	//Time Complexity: two loops mean O(n) + O(n) =O(2n) 
	//Constants are ignored so O(n)
	//Space complexity = O(1) bcz no memory 
}

//Helper function to find mid
Node* findMid(Node* head){
	Node* slow=head;
	Node* fast=head;
	//in case of even sized lsit, considering second as mid
	while(fast!=NULL && fast->next!=NULL){ //fast->next case for even list
		slow=slow->next;
		fast=fast->next->next;
	}
	return slow;
}

//Recursive Approach Using Merge Sort
//Time Complexity O(n log n)
//Space Complexity O(log n) bcz roughly half size with every call
Node* threeProblemRec(Node* head){
	if(head==NULL || head->next==NULL){
		return head;
	}
	//Using two helper function: 1 for finding mid and 2nd for merging two halves into one
	Node* mid=findMid(head);
	Node* secondHead=mid->next;		//holding remaining half of list
	mid->next=NULL;
	/* Before applying merge sort, need to sort the lists first */
	Node* firstHalve=threeProblemRec(head);
	Node* secondHalve=threeProblemRec(secondHead);
	
	return mergeList(firstHalve,secondHalve);
}


//Floyd's Cycle Detection Algorithm + Removal
//Time Complexity: O(n) bcz n operation in worst case (n mean size of input)
//Space Complexity is constant
/*
When both starting moving, distance between them increase by one ,
a point comes when the distance between them is equal to size of the 
loop and both meet at a point then its mean cycle exists 
*/
bool cycleExists(Node* head){
	Node* slow=head;
	Node* fast=head;
	while(fast!=NULL && fast->next!=NULL){
		slow=slow->next;
		fast=fast->next->next;
		if(slow==fast){
			return true;
		}
	}
	return false;
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







