//Array problems
#include<stdio.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>

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

/*	majority element: existing more than size/2 times
1.pick up one element and running loop on  entire array
2.update the  frequency with every existence
3.if frequency is greater than n/2 then its majority element

O(n^2) : in effecient
*/
int majorityElement(int* array,int size){
	int i,j;
	for(i=0;i<size;i++){
		int frequency=0;
		for(j=0;j<size;j++){
			if(array[i]==array[j]){
				frequency++;
			}
		}
		if(frequency>(size/2)) return array[i];	
	}
	return -1;
}

/* Sorting and checking the frequency
Sort: O(nlogn)
Loop: O(n)
Better than the brute previous brute force 
*/
int majorityElementOptimized(int* array, int size){
	int majElement=array[0];
	int frequency=1;
	int  i;
	for(i=1;i<size;i++){
		if(array[i]==array[i-1]){
			frequency++;
		}else{
			majElement=array[i];
			frequency=1;
		}
		if(frequency>(size/2))
			return majElement;
	} 
	return -1; 
}



/* Moore Voting Algorithm: effecient way to find majElement in O(n) 
1.transverse from start to end 
2. if next same element -> increment the frequency
3. if not -> decrement
4. if majority element present, its frequency will

*/
int mooreVotingAlgorithm(int* array,int size){
	int frequency=0;
	int element=0;
	int i;
	for(i=0;i<size;i++){
		if(frequency==0) element=array[i];
		if(element==array[i]){
			frequency++;
		}else{
			frequency--;
		}
	}
	//verification bcz if not found, it will return last 
	frequency=0;
	for(i=0;i<size;i++){
		if(array[i]==element){
			frequency++;
		}
	}
	if(frequency>size/2) return element;
	return -1;
}

/* Container with most water problem:
1.find the area between two bars(bars are elemnet of array)
1.brute force approach(O^n2)
*/
int maxWater(int* array,int size){
	
	int i,j;
	int maxWater=0;
	for(i=0;i<size;i++){		//accessing element one by one
		for(j=i+1;j<size;j++){	//making posssible combinations
			int width=j-i;
			int height=0;
			if(array[i]<array[j])	//height is minimum of the two bars(otherwise water will leak)
				height=array[i];
			else 
				height=array[j];
				
			int currentWater=width*height;
			if(currentWater>maxWater){	//replacing the maxWater area if found larger area
				maxWater=currentWater;
			}
		}
	}
	return maxWater;
}


/* Container with most water problem:
1.find the area by making two combinations
Optimized Version O(n)
*/
int maxWaterOptimized(int* array,int size){
	int start=0;
	int end=size-1;
	int maxWater=0;
	while(start<end){
		int width=end-start;
		int height=0;
		if(array[start]<array[end])	//height is the greater or either bar
			height=array[start];
		else
			height=array[end];
		int currentWater=width*height;
		if(currentWater>maxWater)
			maxWater=currentWater;
			
		if(array[start]<array[end])	//moving that pointer with low bar to find maxWater
			start++;
		else
			end--;
	}
	return maxWater;
}


/* Product of array except itself:
1.Time Complexity : O(n) Linear
2.Space Complexity: O(n) 
Assuming no 0 (can write checks if exist)
Array is valid bi-elemental and memory is freed in main function
*/
int* productArray(int* array,int n){
	int* prefix=malloc(n*sizeof(int));
	if(prefix==NULL) return NULL;
	prefix[0]=1;
	int i;
	for(i=1;i<n;i++){
		prefix[i]=array[i-1]*prefix[i-1];
	}
	
	int* suffix=malloc(n* sizeof(array[0]));
	if(suffix==NULL) return NULL;
	suffix[n-1]=1;
	for(i=n-2;i>=0;i--){
		suffix[i]=suffix[i+1]*array[i+1];
	}
	
	int* ansArray=malloc(n*sizeof(array[0]));
	for(i=0;i<n;i++){
		ansArray[i]=prefix[i]*suffix[i];
	}
	free(prefix);
	free(suffix);
	return ansArray;
	
}

/* Product of array except itself
Time complexity: Linear O(n)
Space Complexity: O(n)
if assuming the mallocated array is standard for returning output, then
Space complexity: O(1)
*/
int* productArrayOptimized(int* array,int n){
	int* productArray=malloc(n*sizeof(array[0]));
	productArray[0]=1;
	
	int i;
	for(i=1;i<n;i++){
		productArray[i]=productArray[i-1]*array[i-1];	
	}
	
	int suffix=array[n-1];
	for(i=n-2;i>=0;i--){
		productArray[i]*=suffix;
		suffix*=array[i];
	}
	return productArray;
}










