/*
 *18. 四数之和
 *
 *描述 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
 *
 *注意 答案中不可以包含重复的四元组。
 *
 *示例 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。满足要求的四元组集合为：
 *		[
 *		  [-1,  0, 0, 1],
 *		  [-2, -1, 1, 2],
 *		  [-2,  0, 0, 2]
 *		]
 */

 /**
  * Return an array of arrays of size *returnSize.
  * Note: The returned array must be malloced, assume caller calls free().
  */
  
#include <stdio.h>
#include <stdlib.h>

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

 int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
	if(NULL == nums || numsSize < 4)
		return NULL;

	quikSort(nums, 0, numsSize - 1);

	int **ret = (int **)malloc(8192 * sizeof(int*));
	int retSize = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int tempSum = 0;
	for(i=0; i<numsSize; i++)
		printf("%d, ", nums[i]);	
	printf("\n");
	
	for(i=0; i<numsSize-3; i++) {
		while(i > 0 && i < numsSize - 3 && nums[i] == nums[i - 1])
				i++;
		for(j=i+1; j<numsSize-2; j++) {			
			while(j > i + 1 && j < numsSize - 2 && nums[j] == nums[j - 1])
				j++;
				
			k = j + 1;
			l = numsSize - 1;
			while(k < l) {
				tempSum = nums[i] + nums[j] + nums[k] + nums[l];
				if(tempSum <target) {
					k++;
				} else if(tempSum > target) {
					l--;
				} else {
					ret[retSize] = (int *)malloc(4 * sizeof(int));
					ret[retSize][0] = nums[i];
					ret[retSize][1] = nums[j];
					ret[retSize][2] = nums[k];
					ret[retSize][3] = nums[l];
					retSize++;
					k++;
					l--;
					while(k < l && nums[k] == nums[k-1]) 
						k++;
					while(k < l && nums[l] == nums[l+1])
						l--;
				}
			}

		}
	}

	*returnSize = retSize;

	return ret;
}

int main()
{
	int nums[] = {-3,-2,-1,0,0,1,2,3};
	int size = sizeof(nums)/sizeof(int);
	int retsize = 0;
	int **result = fourSum(nums, size, 0, &retsize);
	printf("retsize = %d\n", retsize);
	int i = 0;
	for(i=0; i<retsize; i++) {
		printf("[%d, %d, %d, %d]\n", result[i][0], result[i][1], result[i][2], result[i][3]);
		free(result[i]);
	}
	free(result);
}

