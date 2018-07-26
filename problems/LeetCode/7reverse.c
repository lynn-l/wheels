/*
 *7. 反转整数
 *
 *描述 给定一个 32 位有符号整数，将整数中的数字进行反转。
 *
 *示例	输入: 123
 *		输出: 321
 *
 *		输入: -123
 *		输出: -321
 *		
 *		输入: 120
 *		输出: 21
 *注意 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//basic
int reverse(int x) {
	int negtiveFlg = 0;
	if(x < 0) {
		x = -x;
		negtiveFlg = 1;
	}

	char tmp[11] = {0};
	sprintf(tmp, "%d", x);
	int len = strlen(tmp);
	int i = 0;
	char c;
	for(i=0; i<len/2; i++) {
		c = tmp[i];
		tmp[i] = tmp[len-1-i];
		tmp[len-1-i] = c;
	}
	
	if(negtiveFlg) {
		int maxnum = pow(2, 31);
		char tmp2[11] = {0};
		sprintf(tmp2, "%d", maxnum);
		if(strlen(tmp) >= strlen(tmp2) && strcmp(tmp, tmp2) > 0)
			return 0;
		else
			return 0 - (atoi(tmp));
	} else {
		int maxnum = pow(2, 31) - 1;
		char tmp2[11] = {0};
		sprintf(tmp2, "%d", maxnum);
		if(strlen(tmp) >= strlen(tmp2) && strcmp(tmp, tmp2) > 0)
			return 0;
		else
			return atoi(tmp);
	}
}

//advanced
int reverse2(int x) {
	int negtiveFlg = 0;
	if(x < 0) {
		x = -x;
		negtiveFlg = 1;
	}

	char tmp[11] = {0};
	sprintf(tmp, "%d", x);
	int len = strlen(tmp);
	int i = 0;
	char c;
	for(i=0; i<len/2; i++) {
		c = tmp[i];
		tmp[i] = tmp[len-1-i];
		tmp[len-1-i] = c;
	}
	
	if(negtiveFlg) {
		char *tmp2 = "2147483648";
		if(len > 10 || (len == 10 && strcmp(tmp, tmp2) > 0))
			return 0;
		else
			return 0 - (atoi(tmp));
	} else {
		char *tmp2 = "2147483647";
		if(len > 10 ||  (len == 10 && strcmp(tmp, tmp2) > 0))
			return 0;
		else
			return atoi(tmp);
	}
}
int main()
{
	printf("%d\n", reverse2(-1234));
}

