#include<stdio.h>
#include"arrays.h"

int main(){
	int array[]={1,2,3};
	int size=sizeof(array)/sizeof(int);
	
	printSubArray( array, size);
	int maxSum=maxSubArraySum(array,size);
	printf("Maxsum using brute force: %d\n",maxSum);
	
	int maxSum2=kadaneAlgorithm(array,size);
	printf("MaxSum using Kadane algo: %d\n",maxSum2);
	
	int array2[]={1,5,7,11,20};
	int size2=sizeof(array2)/sizeof(array[0]);
	int target=27;
	
	int index1=0;
	int index2=0;
	int result=pairSumOptimized(array2,size2,target,&index1,&index2);
	
	if(result==1){
		printf("First Index:  %d Second Index:  %d\n",index1,index2);
	}else{
		printf("Target sum not found\n");
	}
	return 0;
	
}
