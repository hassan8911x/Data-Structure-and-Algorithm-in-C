//Array problems
#include<stdio.h>
#include<limits.h>//for using INT_MIN

//Time Complexity: O(n^3)
//i runs n times
//j runs from i to n-1 and decreases with every increasing i mean n(n+1)/2 (ignoring constats O(n^2) )
//k runs on average n times
void printSubArray(int* array,int size){
	int i,j,k;
	for(i=0;i<size;i++){
		for(j=i;j<size;j++){
			for(k=i;k<=j;k++){
				printf("%d",array[k]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

//Time Complexity: O(n^3)
int maxSubArraySum(int* array,int size){
	int i,j,k;
	int maxSum=array[0];		//so negative arrray case can be handled
	for(i=0;i<size;i++){
		for(j=i;j<size;j++){
			int tempSum=0;
			for(k=i;k<=j;k++){
				tempSum+=array[k];
			}
			if(tempSum>maxSum){
				maxSum=tempSum;
			}
		}
	}
	return maxSum;
}


//Kadane's Algorithm
//Time Complexity: O(n)
int kadaneAlgorithm(int* array,int size){
	int maxSum=INT_MIN;
	int currentSum=0;
	int i;
	
	for(i=0;i<size;i++){
		currentSum+=array[i];
		if(currentSum>maxSum) maxSum=currentSum;
		if(currentSum<0){
			currentSum=0;
		}
	}
	return maxSum;
}


/* Pair Sum Brute Force Approach: Can used for sorted/unsorted
1.Taking one element one by one
2. Adding all element one by one to check if their sum is equal to target
	a. if equal to target 
		a. make array and setting elements and returning pointer
		b.funtion's 1/0 tells found or not and two parmaters of integer type for storing result.
		 if result is 1, then check variables for indices other wise no need and clear memory
	b.if not then return 0 for operation unsuccessful 
*/
int pairSum(int* array,int size,int target,int* index1,int* index2){
	int i,j;
	for(i=0;i<size-1;i++){
		for(j=i+1;j<size;j++){
			if(array[i]+array[j]==target){
				*index1=i;
				*index2=j;
				return 1;//mean found the target,now check variable's value 
			}
		}	
	}
	return 0;//mean not found	
	//Time Complexity:O(n^2)
}

/* Pair Sum: On sorted array using the two pointer approach
	1.the target is found then simply return pointer of array made/setting value of parameters
	2.the sum of pointers is greater than target
		then smaller(left) can be decreased so decreasing the greater(right)
	3.the sum of pointers is less than the target ->
		then greater(right) can be increased so increasing the smaller(left)
	4.if not found, then return 
*/
//Time Complexity: O(n) bcz array already sorted
//If sorted manually then for merge Sort(n log n) then O(n log n) total  
int pairSumOptimized(int* array,int size,int target,int* index1, int* index2){
	int left=0;
	int right=size-1;
	while(left<right){
		int sum=array[left]+array[right];
		if(sum==target){
			*index1=left;
			*index2=right;
			return 1;
		}
		else if(sum<target){
			left++;
		}
		else{
			right--;
		}
	}
	return 0; //not found ,0 as operation flag
}


