/*
 *16. 最接近的三数之和 	
 *
 *描述 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
 *
 *例如，给定数组 nums = [-1，2，1，-4], 和 target = 1. 与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
 *
 */
#include <stdio.h>

int quikSort(int *nums, int first, int last)
{
	if(first >= last)
		return 0;

	int low = first;
	int high = last;
	int key = nums[low];
	while(low < high)
	{
		while(low < high && nums[high] >= key)
			high--;
		
		if(low < high) {
			nums[low] = nums[high];
		}
		while(low < high && nums[low] <= key)
			low++;

		if(low < high) {
			nums[high] = nums[low];
		}
	}
	nums[low] = key;

	quikSort(nums, first, low - 1);
	quikSort(nums, low + 1, last);

	return 0;
}

int threeSumClosest(int* nums, int numsSize, int target) {
	if(NULL == nums || numsSize < 3)
		return 0;

	quikSort(nums, 0, numsSize - 1);

	int retSum = 0x7fffffff;
	int closest = 0x7fffffff;
	int i = 0;
	int j = 0;
	int k = 0;
	int tempi = 0;
	int tmpClose = 0;
	int tmpSum = 0;
	for(i=0; i<numsSize; i++)
		printf("%d, ", nums[i]);	
	printf("\n");
	
	for(i=0; i<numsSize-2; i++) {
/*		if(nums[i] - target > 0) {
			tmpSum = nums[i] + nums[i+1] + nums[i+2];
			tmpClose = tmpSum - target;
			if(tmpClose < 0)
				tmpClose = -tmpClose;
			if(tmpClose < closest) {
				printf("i = %d, sum = %d, close = %d\n", i, tmpSum, tmpClose);
				closest = tmpClose;
				retSum = tmpSum;
			}
			break;
		}*/
		
		j = i + 1;
		k = numsSize - 1;
		while(j < k) {
			tmpSum = nums[i] + nums[j] + nums[k];
			tmpClose = tmpSum - target;
			if(tmpClose < 0) {
				j++;
			} else if(tmpClose > 0) {
				k--;
			} else {
				return target;
			}
			
			if(tmpClose < 0)
				tmpClose = -tmpClose;
			if(tmpClose < closest) {
				printf("i = %d, j = %d, k = %d, sum = %d, close = %d\n", i, j, k, tmpSum, tmpClose);
				closest = tmpClose;
				retSum = tmpSum;
			}
		}
	
		
	}

	return retSum;
}

int main()
{
	int nums[] = {6,-18,-20,-7,-15,9,18,10,1,-20,-17,-19,-3,-5,-19,10,6,-11,1,-17,-15,6,17,-18,-3,16,19,-20,-3,-17,-15,-3,12,1,-9,4,1,12,-2,14,4,-4,19,-20,6,0,-19,18,14,1,-15,-5,14,12,-4,0,-10,6,6,-6,20,-8,-6,5,0,3,10,7,-2,17,20,12,19,-13,-1,10,-1,14,0,7,-3,10,14,14,11,0,-4,-15,-8,3,2,-5,9,10,16,-4,-3,-9,-8,-14,10,6,2,-12,-7,-16,-6,10};
	int size = sizeof(nums)/sizeof(int);
	printf("%d\n", threeSumClosest(nums, size, -52));
}
