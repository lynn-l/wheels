/*
 *29. 两数相除
 *
 *描述 给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
 *		返回被除数 dividend 除以除数 divisor 得到的商。
 *
 *示例 输入: dividend = 10, divisor = 3
 *		输出: 3
 *
 *		输入: dividend = 7, divisor = -3
 *		输出: -2
 *
 *说明 被除数和除数均为 32 位有符号整数。
 *		除数不为 0。
 *		假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。本题中，如果除法结果溢出，则返回 231 − 1。 *
 *
 */

#include <stdio.h>

int divide(int dividend, int divisor) {
	if(divisor == 0)
		return -1;
	if(dividend == 0)
		return 0;

	int negFlag = 0;
	long long n1 = dividend;
	long long n2 = divisor;

	if(n1 < 0) {
		n1 = -n1;
		negFlag = 1 - negFlag;
	}
	if(n2 < 0) {
		n2 = -n2;
		negFlag = 1 - negFlag;
	}
	printf("n1 = %lld, n2 = %lld, negFlag = %d\n", n1, n2, negFlag);

	if(n1 < n2)
		return 0;
	long long tmp = n2;
	long long count  = 1;
	long long result = 0;
	while(n1 >= n2) {
		tmp = n2;
		count  = 1;
		int cnt = 0;
		while((tmp << 1) <= n1) {
			tmp = tmp << 1;
			count = count << 1;
			cnt++; 
		}
		result += count;
		n1 -= tmp;
		printf("result = %lld, n1 = %lld, cnt = %d\n", result, n1, cnt);
	}

	if(negFlag)
		result = -result;
	if(result > 2147483647)
		return 2147483647;

	return (int)result;	
}

int main()
{
	printf("%d\n", divide(10, 3));
	printf("%d\n", divide(7, -3));
	printf("%d\n", divide(-2147483648, 2));
	printf("%d\n", divide(-2147483648, -1));
	//printf("%d\n", divide(-2147483648, -1));
	return 0;
}
