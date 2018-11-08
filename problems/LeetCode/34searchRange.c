/*
 *34. 在排序数组中查找元素的第一个和最后一个位置
 *
 *描述 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
 *		你的算法时间复杂度必须是 O(log n) 级别。
 *		如果数组中不存在目标值，返回 [-1, -1]。
 *
 *示例 1:
 *		输入: nums = [5,7,7,8,8,10], target = 8
 *		输出: [3,4]
 *示例 2:
 *		输入: nums = [5,7,7,8,8,10], target = 6
 *		输出: [-1,-1]
 *
 */

#include <stdio.h>
#include <stdlib.h>

int serach(int* nums, int numsSize, int target){
	int start = 0;
	int end = numsSize - 1;
	int index = 0;

	if(nums[start] == target)
		return start;
	if(nums[end] == target)
		return end;

	while(1) {
		index = (start + end) >> 1;
		if(index == start)
			return -1;
	
		if(nums[index] == target)
			return index;	
		else if(nums[index] > target)
			end = index;
		else
			start =index;
	}
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	int *ret = (int *)malloc(2 * sizeof(int));
	if(ret == NULL)
		return NULL;

	ret[0] = ret[1] = -1;
	*returnSize = 2;

	if(NULL == nums || numsSize <= 0 || NULL == returnSize)
		return ret;

	int loc = serach(nums, numsSize, target);
	if(loc < 0)
		return ret;

	ret[0] = ret[1] = loc;
	while(ret[0]-1 >= 0 && nums[ret[0]-1] == target)
		ret[0]--;
	while(ret[1]+1 <= numsSize-1 && nums[ret[1]+1] == target)
		ret[1]++;

	return ret;
}

int print_ret(int *ret, int returnSize)
{
	int i = 0;
	if(NULL != ret) {
		printf("ret ");
		for(i=0; i<returnSize; i++) {
			printf("%d ", ret[i]);
		}
		printf("\n");
		free(ret);
	}
	return 0;
}

int main()
{
	int nums[] = {5,7,7,8,8,10};
	int numsSize = sizeof(nums) / sizeof(int);
	int returnSize = 0;

	int *ret = searchRange(nums, numsSize, 8, &returnSize);
	print_ret(ret, returnSize);
	
	ret = searchRange(nums, numsSize, 6, &returnSize);
	print_ret(ret, returnSize);

	return 0;
}
