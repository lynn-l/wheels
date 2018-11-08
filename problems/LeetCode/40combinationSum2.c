/*
 *40. 组合总和2
 *
 *描述 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 *		candidates 中的每个数字在每个组合中只能使用一次。
 *说明：
 *		所有数字（包括 target）都是正整数。
 *		解集不能包含重复的组合。
 *
 *示例 1:
 *		输入: candidates = [10,1,2,7,6,1,5], target = 8,
 *		所求解集为:
 *		[
 * 			[1, 7],
 * 			[1, 2, 5],
 * 			[2, 6],
 * 			[1, 1, 6]
 *		]
 *示例 2:
 *		输入: candidates = [2,5,2,1,2], target = 5,
 *		所求解集为:
 *		[
 * 			[1,2,2],
 *			[5]
 *		]
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

int arraySum(int *array, int size)
{
	int sum = 0;
	int i = 0;
	for(i=0; i<size; i++)
		sum += array[i];

	return sum;
}

int addArrayToResult(int *array, int size, int **ret, int *columnSizes, int *returnSize)
{
	columnSizes[*returnSize] = size;
	
	ret[*returnSize] = (int *)malloc(size * sizeof(int));
	memcpy(ret[*returnSize], array, size * sizeof(int));

	*returnSize += 1;
	
	return 0;
}

int testSum(int *candidates, int candidatesSize, int target, int *array, int size, int **ret, int *columnSizes, int *returnSize, int start)
{
	int i = 0, j = 0;
	int sum;
	for(i=start; i<candidatesSize; i++) {
		if(i>start && candidates[i] == candidates[i-1])
			continue;
		
		array[size] = candidates[i];
		sum = arraySum(array, size+1);
	
		printf("size %d: ", size+1);
		for(j=0; j<size+1; j++)
			printf("%d ", array[j]);
		
		if(sum == target) {
			printf("==\n");
			addArrayToResult(array, size+1, ret, columnSizes, returnSize);
			break;
		} else if(sum < target) {
			printf("<\n");
			testSum(candidates, candidatesSize, target, array, size+1, ret, columnSizes, returnSize, i+1);
		} else {
			printf(">\n");
			break;
		}
	}
	return 0;
}

int **combinationSum(int *candidates, int candidatesSize, int target, int **columnSizes, int *returnSize)
{
	if(NULL == candidates || candidatesSize <= 0 || NULL == columnSizes || NULL == returnSize) {
		printf("columnSizes = %p\n", columnSizes);
		return NULL;
	}

	quikSort(candidates, 0, candidatesSize-1);

	int testArray[1024] = {0};
	int sizeArray = 0;
	int i = 0, j = 0;
	int sum;
	
	int **ret = (int **)malloc(1024 * sizeof(int *));
	*columnSizes = (int *)malloc(1024 * sizeof(int));
	for(i=0; i<candidatesSize; i++) {
		if(i>0 && candidates[i] == candidates[i-1])
			continue;
		testArray[sizeArray] = candidates[i];
		sum = arraySum(testArray, sizeArray+1);

		printf("size %d: ", sizeArray+1);
		for(j=0; j<sizeArray+1; j++)
			printf("%d ", testArray[j]);
		
		if(sum == target) {
			printf("==\n");
			addArrayToResult(testArray, sizeArray+1, ret, *columnSizes, returnSize);
			break;
		} else if(sum < target) {
			printf("<\n");
			testSum(candidates, candidatesSize, target, testArray, sizeArray+1, ret, *columnSizes, returnSize, i+1);
		} else {
			printf(">\n");
			break;
		}
	}

	return ret;
}


int main()
{
	int candidates[] = {10,1,2,7,6,1,5};
	int candidatesSize = sizeof(candidates)/sizeof(int);
	int target = 8;
	int returnSize = 0;
	int *columnSizes = NULL;
	
	int **ret = combinationSum(candidates, candidatesSize, target, &columnSizes, &returnSize);
	printf("returnSize = %d\n", returnSize);
	int i = 0, j = 0;
	for(i=0; i<returnSize; i++) {
		printf("ret[%d]:[", i);
		for(j=0; j<columnSizes[i]; j++) {
			printf(" %d ", ret[i][j]);
		}
		printf("]\n");
		free(ret[i]);
	}
	free(columnSizes);
	free(ret);
}

