/*
 *10. 正则表达式匹配
 *
 *描述 给定一个字符串 (s) 和一个字符模式 (p)。实现支持 '.' 和 '*' 的正则表达式匹配。
 *		'.' 匹配任意单个字符。
 *		'*' 匹配零个或多个前面的元素。
 *		匹配应该覆盖整个字符串 (s) ，而不是部分字符串。
 *
 *说明 s 可能为空，且只包含从 a-z 的小写字母。
 *		p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
 *
 *示例	输入:
 *		s = "aa"
 *		p = "a"
 *		输出: false
 *		解释: "a" 无法匹配 "aa" 整个字符串。
 *
 *		输入:
 *		s = "aa"
 *		p = "a*"
 *		输出: true
 *		解释: '*' 代表可匹配零个或多个前面的元素, 即可以匹配 'a' 。因此, 重复 'a' 一次, 字符串可变为 "aa"。
 *		
 *		输入:
 *		s = "ab"
 *		p = ".*"
 *		输出: true
 *		解释: ".*" 表示可匹配零个或多个('*')任意字符('.')。
 *
 *		输入:
 *		s = "aab"
 *		p = "c*a*b"
 *		输出: true
 *		解释: 'c' 可以不被重复, 'a' 可以被重复一次。因此可以匹配字符串 "aab"。
 *
 *		输入:
 *		s = "mississippi"
 *		p = "mis*is*p*."
 *		输出: false
 */
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char* s, char* p) {
	if(NULL == s || NULL == p)
		return false;

	int slen = strlen(s);
	int plen = strlen(p);
	printf("%s:%d, slen = %d, plen = %d\n", __FUNCTION__, __LINE__, slen, plen);
	int i = 0;
	int j = 0;
	while(j<plen && i<=slen) {
		if(p[j] == '.') {
			printf("%s:%d, s[%d] = %c, p[%d] = %c\n", __FUNCTION__, __LINE__, i, s[i], j, p[j]);
			if(j+1<plen && p[j+1] == '*') {
				while(i<=slen){
					if(true == isMatch(s+i, p+j+2))
						return true;
					i++;
				}
				return false;
			}	
			j++;
			i++;
		} else if(j+1< plen && p[j] >= 'a' && p[j] <= 'z' && p[j+1] == '*') {
			printf("%s:%d, s[%d] = %c, p[%d] = %c\n", __FUNCTION__, __LINE__, i, s[i], j, p[j]);
			//* = 0
			printf("%s:%d, isMatch s+%d, p+%d\n", __FUNCTION__, __LINE__, i, j+2);
			if(true == isMatch(s+i, p+j+2))
				return true;
			else {
			//* = 1- ...
				char c = p[j];
				int k = 1;
				while(i+k <= slen && s[i+k-1] == c) {
					printf("%s:%d, isMatch s+%d, p+%d\n", __FUNCTION__, __LINE__, i+k, j+2);
					if(true == isMatch(s+i+k, p+j+2))
						return true;
					k++;
				}
				return false;
			}
		} else if(p[j] >= 'a' && p[j] <= 'z') {
			printf("%s:%d, s[%d] = %c, p[%d] = %c\n", __FUNCTION__, __LINE__, i, s[i], j, p[j]);
			if(p[j] != s[i])
				return false;
			j++;
			i++;
		} else {
			printf("%s:%d, s[%d] = %c, p[%d] = %c\n", __FUNCTION__, __LINE__, i, s[i], j, p[j]);
			return false;
		}
	}

	if(i != slen || s[i] != '\0')
		return false;
	
	return true;
}

int main()
{
	printf("%d\n", isMatch("aa", "a"));
	printf("%d\n", isMatch("aa", "a*"));
	printf("%d\n", isMatch("ab", ".*"));
	printf("%d\n", isMatch("aab", "c*a*b"));
	printf("%d\n", isMatch("mississippi", "mis*is*p*."));
	printf("%d\n", isMatch("a", ".*..a*"));
}
