/*
 *Description	:Write an algorithm which computes the number of trailing zeros in n factorial.
 *Challenge		:O(log N) time
 *
 */
 
#include <stdio.h>
#include <math.h>

long long trailingZeros2(long long n)
{
	long long result = 0;
	
	while(n > 0) {
		n /= 5;
		result += n;
	}
	
	return result;
}

int main()
{
	printf("trailingZeros2 = %lld, trailingZeros3 = %lld\n", trailingZeros2(11111234));
	return 0;
}
