/*
 *描述 给定一个字符串，找出不含有重复字符的最长子串的长度。
 *示例	给定 "abcabcbb"，没有重复字符的最长子串是 "abc"，那么长度就是3。
 *		给定 "bbbbb"，最长的子串就是 "b"，长度是1。
 *		给定 "pwwkew"，最长子串是 "wke"，长度是3。请注意答案必须是一个子串，"pwke" 是子序列而不是子串。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
	if(NULL == s || strlen(s) <= 0)
		return 0;
	
	int mostlen = 1;
	int i = 0;
	int j = 0;
	int len = strlen(s);
	char * tmp;
	
	for(i=0; i<len-mostlen; i++) {
		for(j=i+1; j<len; j++) {
			tmp = strchr(s+i, s[j]);
			if(tmp < s+j){
				break;
			}
		}
		if(j-i > mostlen)
			mostlen = j-i;
	}

	return mostlen;
}

int main()
{
	printf("%d\n", lengthOfLongestSubstring("pwwkew"));
}
