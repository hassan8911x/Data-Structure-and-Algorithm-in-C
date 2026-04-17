#ifndef ARRAY_H
#define ARRAY_H

void printSubArray(int* array,int size);
int maxSubArraySum(int* array,int size);
int kadaneAlgorithm(int* array,int size);
int pairSum(int* array,int size,int target,int* index1,int* index2);
int pairSumOptimized(int* array,int size,int target,int* index1,int* index2);

int majorityElemnet(int* array,int size);
int majorityElementOptimized(int* array,int size);
int mooreVotingAlgorihtm(int* array,int size);

int maxWater(int* array,int size);
int maxWaterOptimized(int*  array,int size);

int* productArray(int* array,int n);
int* productArrayOptimized(int* array,int n);

#endif
