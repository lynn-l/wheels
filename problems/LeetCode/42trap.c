/*
 *42. 接雨水
 *
 *描述 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *示例 1:
 *		输入: [0,1,0,2,1,0,1,3,2,1,2,1]
 *		输出: 6
 */ 
#include <stdio.h>

int MaxHigh(int* height, int heightSize)
{
	int max = 0;
	int i = 0;
	for(i=0; i<heightSize; i++)
		if(height[i] > max)
			max = height[i];

	return max;
}

int trap(int* height, int heightSize) {
	int left = 0;
	int i = 0;
	int sum = 0;
	int rightMax = 0;
	printf("%d:heightSize = %d\n", __LINE__, heightSize);
	for(i=0; i<heightSize; i++) {
		if(left <= 0) {
			while(height[i] <= 0 && i < heightSize)
				i++;
			if(i >= heightSize-1)
				continue;
			left = height[i];
			printf("%d:left = height[%d] = %d\n", __LINE__, i, left);

			rightMax = MaxHigh(&height[i+1], heightSize-i-1);
			if(rightMax < left) {
				left = rightMax;
				printf("%d:left = rightMax = %d\n", __LINE__, rightMax);
			}
			continue;
		}

		if(height[i] >= left) {
			if(i+1 >= heightSize)
				continue;
			left = height[i];
			printf("%d:left = height[%d] = %d\n", __LINE__, i, left);
			rightMax = MaxHigh(&height[i+1], heightSize-i-1);
			if(rightMax < left) {
				left = rightMax;
				printf("%d:left = rightMax = %d\n", __LINE__, rightMax);
			}

			continue;
		}

		sum += left - height[i];
		printf("%d:sum + %d = %d\n", __LINE__, left - height[i], sum);
	}

	return sum;
}

int main()
{
	int nums[] = {0,2,0};
	int numsSize = sizeof(nums)/sizeof(int);
	
	printf("%d\n", trap(nums, numsSize));
}
