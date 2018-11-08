/*
 *39. 组合总和
 *
 *描述 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 *		candidates 中的数字可以无限制重复被选取。
 *说明：
 *		所有数字（包括 target）都是正整数。
 *		解集不能包含重复的组合。
 *
 *示例 1:
 *		输入: candidates = [2,3,6,7], target = 7,
 *		所求解集为:
 *		[
 *		  [7],
 *		  [2,2,3]
 *		]
 *示例 2:
 *		输入: candidates = [2,3,5], target = 8,
 *		所求解集为:
 *		[
 *		  [2,2,2,2],
 *		  [2,3,3],
 *		  [3,5]
 *		]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		array[size] = candidates[i];
		sum = arraySum(array, size+1);
	
		printf("size %d: ", size+1);
		for(j=0; j<size+1; j++)
			printf("%d ", array[j]);
		
		if(sum == target) {
			printf("==\n");
			addArrayToResult(array, size+1, ret, columnSizes, returnSize);
		} else if(sum < target) {
			printf("<\n");
			testSum(candidates, candidatesSize, target, array, size+1, ret, columnSizes, returnSize, i);
		} else {
			printf(">\n");
			continue;
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
	
	int testArray[1024] = {0};
	int sizeArray = 0;
	int i = 0, j = 0;
	int sum;
	
	int **ret = (int **)malloc(1024 * sizeof(int *));
	*columnSizes = (int *)malloc(1024 * sizeof(int));
	for(i=0; i<candidatesSize; i++) {
		testArray[sizeArray] = candidates[i];
		sum = arraySum(testArray, sizeArray+1);

		printf("size %d: ", sizeArray+1);
		for(j=0; j<sizeArray+1; j++)
			printf("%d ", testArray[j]);
		
		if(sum == target) {
			printf("==\n");
			addArrayToResult(testArray, sizeArray+1, ret, *columnSizes, returnSize);
		} else if(sum < target) {
			printf("<\n");
			testSum(candidates, candidatesSize, target, testArray, sizeArray+1, ret, *columnSizes, returnSize, i);
		} else {
			printf(">\n");
			continue;
		}
	}

	return ret;
}


int main()
{
	int candidates[] = {7,3,2};
	int candidatesSize = sizeof(candidates)/sizeof(int);
	int target = 18;
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
