/*
 *31. 下一个排列
 *
 *描述 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
 *		如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
 *		必须原地修改，只允许使用额外常数空间。
 *		以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
 * 		1,2,3 → 1,3,2
 *		3,2,1 → 1,2,3
 *		1,1,5 → 1,5,1
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void nextPermutation(int* nums, int numsSize) {
	if(NULL == nums || numsSize <= 1)
		return;
	
	int tmp = numsSize - 1;

	for(; tmp>=1; tmp--) {
		if(nums[tmp-1] < nums[tmp])
			break;
	}
	if(tmp == 0)
		tmp = 1;
	//printf("nums[%d] = %d, nums[%d] = %d\n", tmp-1, nums[tmp-1], tmp, nums[tmp]);
	
	int tmpp = 0;
	int i = 0;
	//Ascending order
	if(nums[tmp-1] >= nums[tmp]) {
		//printf("Ascending order\n");
		for(i=0; i<numsSize/2; i++) {
			tmpp = nums[i];
			nums[i] = nums[numsSize-1-i];
			nums[numsSize-1-i] = tmpp;
		}
		return;
	}

	tmpp = tmp;
	for(i=tmp+1; i<numsSize; i++) {
		if(nums[i] > nums[tmp-1] && nums[i] < nums[tmpp]) {
			tmpp = i;
		}
	}
	//printf("tmpp = %d\n", tmpp);
	int tmppp;
	tmppp = nums[tmp - 1];
	nums[tmp - 1] = nums[tmpp];
	nums[tmpp] = tmppp;

	quikSort(nums, tmp, numsSize-1);
	
	return;
}

int main()
{
//	int nums[] = {1,2,3};
//	int nums[] = {3,2,1};
	int nums[] = {1,1};
	int size = sizeof(nums)/sizeof(nums[0]);

	nextPermutation(nums, size);

	int i = 0;
	printf("results : ");
	for(i=0; i<size; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	return 0;
}
