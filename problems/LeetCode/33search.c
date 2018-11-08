/*
 *33. 搜索旋转排序数组
 *
 *描述 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
 *		( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
 *		搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
 *		你可以假设数组中不存在重复的元素。
 *		你的算法时间复杂度必须是 O(log n) 级别。
 *
 *示例 1:
 *		输入: nums = [4,5,6,7,0,1,2], target = 0
 *		输出: 4
 *示例 2:
 *		输入: nums = [4,5,6,7,0,1,2], target = 3
 *		输出: -1
 *
 */
 
#include <stdio.h>

int search(int *nums, int numsSize, int target) {
	if(NULL == nums || numsSize <= 0)
		return -1;
	if(target == nums[0])
		return 0;
	if(target == nums[numsSize - 1])
		return numsSize - 1;

	int start = 0;
	int end = numsSize - 1;
	int index = 0;

	int upper = 0;
	if(target > nums[0])
		upper = 1;
	else
		upper = 0;
	
	while(1) {
		index = (start + end) >> 1;//  ">> 1" == "/ 2"
		printf("index = %d, start = %d, end = %d\n", index, start, end);
		if(index == start)
			return -1;
		
		if(nums[index] == target)
			return index;
		else if (target > nums[index]) {
			if (nums[index] > nums[0]) {
				start = index;
			} else {
				if(upper == 1) {
					end = index;
				} else {
					start = index;
				}
			}
		} else if (target < nums[index]) {			
			if (nums[index] > nums[0]) {
				if(upper == 1) {
					end = index;
				} else {
					start = index;
				}
			} else {
				end = index;
			}
		}
	}
}

int main()
{
	int nums[] = {4,5,6,7,8,0,1,2};
	int numsSize = sizeof(nums)/sizeof(int);
	printf("search result %d\n", search(nums, numsSize, 8));
/*	int i = 0;
	for(i=0; i<=8; i++)
		printf("search result %d\n", search(nums, numsSize, i));*/
}
