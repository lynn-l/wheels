/*
 *4. Ugly Number II
 *
 *Description	:Ugly number is a number that only have factors 2, 3 and 5.
 *				 Design an algorithm to find the nth ugly number. 
 *				 The first 10 ugly numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12...
 *Note 			:1 is typically treated as an ugly number.
 *Challenge		:O(n log n) or O(n) time.
 *
 */
 
#include <stdio.h>
#include <math.h>

int IsAUglyNumber(int n)
{
	while(n > 0)
	{
		if((n % 2) == 0)
			n /= 2;
		else if((n % 3) == 0)
			n /= 3;
		else if((n % 5) == 0)
			n /= 5;
		else 
			break;
	}

	if(n == 1)
		return 1;
	else
		return 0;
}
//basic
int nthUglyNumber(int n)
{
	if(n <= 6)
		return n;
	
	int i = 6;
	int seq = 6;

	do{
		i++;
		if(IsAUglyNumber(i) == 1)
			seq++;
	}while(seq < n);

	return i;
}

//advanced
int nthUglyNumber2(int n)
{
	if(n <= 6)
		return n;

	int *result = (int *)malloc(n * sizeof(int));
	int i = 1;	
	int last2 = 0;
	int last3 = 0;
	int last5 = 0;
	result[0] = 1;

	int temp2 = 0;
	int temp3 = 0;
	int temp5 = 0;
	
	while(++i <= n) {
		temp2 = result[last2] * 2;	
		while (i >= 2 && temp2 <= result[i-2]) {
			last2++;
			temp2 = result[last2] * 2;
		}
		
		temp3 = result[last3] * 3;
		while (i >= 2 && temp3 <= result[i-2]) {
			last3++;
			temp3 = result[last3] * 3;
		}

		temp5 = result[last5] * 5;
		while (i >= 2 && temp5 <= result[i-2]) {
			last5++;
			temp5 = result[last5] * 5;
		}

		if (temp2 <= temp3 && temp2 <= temp5) {
			result[i-1] = temp2;
			last2++;
		} else if (temp3 <= temp2 && temp3 <= temp5) {
			result[i-1] = temp3;
			last3++;
		} else {
			result[i-1] = temp5;
			last5++;
		}
	}

	i = result[n-1];

//	for(i=0; i<n; i++)
//		printf("result[%d] = %d\n", i, result[i]);

	free(result);
	
	return i;
}

int main()
{
	nthUglyNumber(15152);
	
	return 0;
}
