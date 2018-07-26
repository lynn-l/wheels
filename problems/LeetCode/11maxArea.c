/*
 *11. 盛最多水的容器
 *
 *描述 给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 *
 *说明 你不能倾斜容器，且 n 的值至少为 2。
 *
 *示例	输入: [1,8,6,2,5,4,8,3,7]
 *		输出: 49
 */
#include <stdio.h> 

int maxArea(int* height, int heightSize) {
	int max = 0;
	int i = 0;
	int j = 0;
	int tmp;
	for(i=0; i<heightSize-1; i++) {
		for(j=i+1; j<heightSize; j++) {
			if(height[i] <= height[j])
				tmp = height[i] * (j - i);
			else
				tmp = height[j] * (j - i);
			if(tmp > max)
				max = tmp;
		}
	}

	return max;
}

int main()
{
	int height[9] = {1,8,6,2,5,4,8,3,7};
	printf("%d\n", maxArea(height, 9));
}

