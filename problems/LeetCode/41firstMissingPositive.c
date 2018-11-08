/*
 *41. 缺失的第一个正数
 *
 *描述 给定一个未排序的整数数组，找出其中没有出现的最小的正整数。
 *示例 1:
 *		输入: [1,2,0]
 *		输出: 3
 *示例 2:
 *		输入: [3,4,-1,1]
 *		输出: 2
 *示例 3:
 *		输入: [7,8,9,11,12]
 *		输出: 1
 *说明: 你的算法的时间复杂度应为O(n)，并且只能使用常数级别的空间。
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int firstMissingPositive(int* nums, int numsSize) {
	int i = 0;
	int tmp;

	int j = 0;

	for(i=0; i<numsSize; i++) {
		if(nums[i] > 0 && nums[i] < numsSize && nums[i] != i+1) {
			tmp = nums[i];
			nums[i] = nums[tmp-1];
			nums[tmp-1] = tmp;
			i--;
		}
		/*printf("nums %d : ", numsSize);
		for(j=0; j<numsSize; j++) {
			printf("%d ", nums[j]);
		}
		printf("\n");*/
	}

	for(i=0; i<numsSize; i++)
		if(nums[i] != i+1)
			return i+1;
		
	return i+1;
}

int main()
{
	int nums[] = {-1,4,2,1,9,10};
	int numsSize = sizeof(nums)/sizeof(int);

	printf("%d\n", firstMissingPositive(nums, numsSize));

	return 0;
}
