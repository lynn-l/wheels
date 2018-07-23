/*
 *描述 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。
 *示例	输入: "babad"
 *		输出: "bab"
 *		注意: "aba"也是一个有效答案。
 *
 *		输入: "cbbd"
 *		输出: "bb"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s) {
	int len;
	if(NULL == s || (len = strlen(s)) <= 1)
		return s;

	int mostlen = 1;
	static char longeststr[1024] = {0};
	longeststr[0] = s[0];

	int i = 0;
	int j = 0;
	int endflg = 0;

	for(i=1; i<len, (len-i)*2+1>mostlen; i++) {
		if(s[i] == s[i-1]){
			for(j=1; i-1-j>=0, j+i<len; j++) {
				if(s[i-1-j] != s[i+j]) {
					break;
				}
			}	  
			if(j*2 >= mostlen) {
				mostlen = j*2;
				strncpy(longeststr, s+i-j, mostlen);
				longeststr[mostlen] = '\0';
			}
		}
		if(i-2>=0 && s[i] == s[i-2]) {
			for(j=1; i-2-j>=0, j+i<len; j++) {
				if(s[i-2-j] != s[i+j]) {
					break;
				}
			}
			if(j*2+1 >= mostlen) {
				mostlen = j*2+1;
				strncpy(longeststr, s+i-j-1, mostlen);
				longeststr[mostlen] = '\0';
			}
		}
	}

	return longeststr;
}

int main()
{
	printf("%s\n", longestPalindrome("babad"));
	printf("%s\n", longestPalindrome("cbbd"));
}

