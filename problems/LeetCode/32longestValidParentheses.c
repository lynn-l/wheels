/*
 *32. 最长有效括号
 *
 *描述 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
 *
 *示例 1:
 *		输入: "(()"
 *		输出: 2
 *		解释: 最长有效括号子串为 "()"
 *示例 2:
 *		输入: ")()())"
 *		输出: 4
 *		解释: 最长有效括号子串为 "()()"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxLenValidParentheses(char* s)
{
	int len = 0;
	int slen = strlen(s);
	int tmplen = 0;
	int i = 0;
	int maxlen = 0;
	for(i=0; i<slen; i++) {
		if(s[i] == '(') {
			len++;
			tmplen++;
		} else if(s[i] == ')') {
			if(tmplen > 0) {
				tmplen--;
				len++;
			
				if(tmplen == 0)
					maxlen = len;
			} else {
				return maxlen;
			}
		}
	}

	return maxlen;
}

int longestValidParentheses(char* s) {
	int slen = 0;
	if(NULL == s || (slen = strlen(s)) <= 1)
		return 0;

	int maxlen = 0;
	int tmplen = 0;
	int i = 0;
	for(i=0; i<slen-maxlen; i++) {
		tmplen = maxLenValidParentheses(&s[i]);
		//printf("s[%d] = %s, maxlen = %d\n", i, &s[i], tmplen);
		if(tmplen > maxlen)
			maxlen = tmplen;
	}
	
	return maxlen;
}

int main()
{
	printf("maxlen = %d\n", longestValidParentheses("(()"));
	printf("maxlen = %d\n", longestValidParentheses(")()())"));
	printf("maxlen = %d\n", longestValidParentheses(")(((((()())()()))()(()))("));
}
