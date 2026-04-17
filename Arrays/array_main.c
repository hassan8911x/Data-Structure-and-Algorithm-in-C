#include<stdio.h>
#include"arrays.h"
#include<stdlib.h>

int main(){
	int array[]={1,2,3};
	int size=sizeof(array)/sizeof(int);
	
	printSubArray( array, size);
	int maxSum=maxSubArraySum(array,size);
	printf("Maxsum using brute force: %d\n",maxSum);
	
	int maxSum2=kadaneAlgorithm(array,size);
	printf("MaxSum using Kadane algo: %d\n",maxSum2);
	
	int array2[]={1,5,7,11,20};
	int size2=sizeof(array2)/sizeof(array2[0]);
	int target=27;
	
	int index1=0;
	int index2=0;
	int result=pairSumOptimized(array2,size2,target,&index1,&index2);
	
	if(result==1){
		printf("First Index:  %d Second Index:  %d\n",index1,index2);
	}else{
		printf("Target sum not found\n");
	}
	
	int array3[]={3,3,1,1,3,1,2,3,3,3,3,1};
	int size3=sizeof(array3)/sizeof(array3[0]);
	int maj=mooreVotingAlgorithm(array3,size3);
	if(maj!=-1)
		printf("Majority Element: %d\n",maj);
	else
		printf("Majority Element not found\n");
		
	int array4[]={1,8,6,2,5,4,8,3,7};
	int size4=sizeof(array4)/sizeof(int);
	int maxWater1=maxWater(array4,size4);
	int maxWater2=maxWaterOptimized(array4,size4);
	printf("Approach 1: %d\n Approach 2: %d\n",maxWater1,maxWater2);
	
	int array5[]={1,2,3,4};
	int size5=sizeof(array5)/sizeof(array5[0]);
	int* answerArray=productArrayOptimized(array5,size5);
	int i;
	for(i=0;i<size5;i++){
		printf("%d ",answerArray[i]);
	}

	free(answerArray);
	
	return 0;
}










