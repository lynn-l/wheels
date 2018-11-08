/*
 *38. 报数
 *
 *描述 报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：
 *		1.     1
 *		2.     11
 *		3.     21
 *		4.     1211
 *		5.     111221
 *		1 被读作  "one 1"  ("一个一") , 即 11。
 *		11 被读作 "two 1s" ("两个一"）, 即 21。
 *		21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。
 *
 *		给定一个正整数 n（1 ≤ n ≤ 30），输出报数序列的第 n 项。

 *		注意：整数顺序将表示为一个字符串。
 *
 *示例 1:
 *		输入: 1
 *		输出: "1"
 *示例 2:
 *		输入: 4
 *		输出: "1211"
 */
#include <stdio.h>
#include <string.h>

int countAndSayByStr(char *in, char *out)
{
	int inLen = strlen(in);
	char c;
	int outLen = 0;
	int inIndex = 0;
	int cnt = 0;
	while(inIndex < inLen) {
		cnt = 1;
		c = in[inIndex++];
		for(; inIndex<inLen; inIndex++) {
			if(in[inIndex] == c)
				cnt++;
			else
				break;
		}
		out[outLen++] = '0' + cnt;
		out[outLen++] = c;
	}

	return 0;
}

char *countAndSay(int n) {
	if(n < 1 || n > 30)
		return NULL;

	char s[5][8] = {"1", "11", "21", "1211", "111221"};

	static char ret[8096] = {0};
	if(n >= 1 && n <= 5) {
		strcpy(ret, s[n-1]);
		return ret;
	}

	char in[8096] = {0};
	char out[8096] = {0};
	int i = 0;
	char c;
	int count = 0;
	int len = 0;
	int lenTmp = 0;
	printf("n = %d\n", n);
	strcpy(in, s[4]);
	for(i=6; i<=n; i++) {
		countAndSayByStr(in, out);
		strcpy(in, out);
		printf("%d = %d:%s\n", i-1, strlen(out), out);
	}

	strcpy(ret, out);
	
	return ret;
}

int main()
{
	printf("countAndSay 30 = %s\n", countAndSay(30));
}
