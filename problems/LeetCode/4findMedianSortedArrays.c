/*
 *4. 两个排序数组的中位数
 *
 *描述 给定两个大小为 m 和 n 的有序数组 nums1 和 nums2 。
 *		请找出这两个有序数组的中位数。要求算法的时间复杂度为 O(log (m+n)) 。
 *示例	nums1 = [1, 3]
 *		nums2 = [2]
		中位数是 2.0
 *
 *		nums1 = [1, 2]
 *		nums2 = [3, 4]
 *		中位数是 (2 + 3)/2 = 2.5
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int size = nums1Size + nums2Size;
	if(size <= 0)
		return 0;

	int tmp[size/2 + 2];
	int i = 0;
	int j = 0;
	int k = 0;
	while(k<=size/2) {
		if(i >= nums1Size) {
			tmp[k] = nums2[j];
			k++;
			j++;
		} else if (j >= nums2Size) {
			tmp[k] = nums1[i];
			k++;
			i++;
		} else if (nums1[i] < nums2[j]) {
			tmp[k] = nums1[i];
			k++;
			i++;
		} else if (nums1[i] > nums2[j]) {
			tmp[k] = nums2[j];
			k++;
			j++;
		} else {
			tmp[k] = nums1[i];
			k++;
			i++;
			tmp[k] = nums2[j];
			k++;
			j++;
		}
	}
	
	double result;
	if(size % 2 != 0)
		result = (double)tmp[size/2];
	else 
		result = (double)(tmp[size/2] + tmp[size/2 - 1]) / 2;

	return result;
}

int main()
{
	int a[2] = {1,3};
	int b[1] = {2};
	printf("%f\n", findMedianSortedArrays(a, 2, b, 1));

}
