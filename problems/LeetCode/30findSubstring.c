/*
 *30. 与所有单词相关联的字串
 *
 *描述 给定一个字符串 s 和一些长度相同的单词 words。在 s 中找出可以恰好串联 words 中所有单词的子串的起始位置。
 *		注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
 *
 *示例 输入:
 *		s = "barfoothefoobarman",
 *		words = ["foo","bar"]
 *		输出: [0,9]
 *		解释: 从索引 0 和 9 开始的子串分别是 "barfoor" 和 "foobar" 。
 *		输出的顺序不重要, [9,0] 也是有效答案。
 *
 *		输入:
  *		s = "wordgoodstudentgoodword",
 *		words = ["word","student"]
 *		输出: []
 * 
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMatch(char* s, char** words, int wordsSize, int *wordsLen, int strsLen)
{
	int tmp[wordsSize];
	memset(tmp, 1, wordsSize * sizeof(int));

	int i = 0;
	int tmplen = 0;
	int match = 0;
	while(tmplen < strsLen) {
		match = 0;
		for(i=0; i<wordsSize; i++) {
			if(strncmp(s+tmplen, words[i], wordsLen[i]) == 0 && tmp[i] != 0) {
				tmplen +=  wordsLen[i];
				tmp[i] = 0;
				match = 1;
				break;
			}
		}
		if(match == 0)
			return 0;
	}
	for(i=0; i<wordsSize; i++) {
		if(tmp[i] != 0)
			return 0;
	}

	return 1;
}
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	if(NULL == s || NULL == words || wordsSize <= 0 || NULL == returnSize)
		return NULL;

	int wordsLen[wordsSize];
	int i = 0;
	int strsLen = 0;
	int slen = strlen(s);
	for(i=0; i<wordsSize; i++) {
		wordsLen[i] = strlen(words[i]);
		strsLen += wordsLen[i];
	}
	if(strsLen > slen) {
		*returnSize = 0;
		return NULL;
	}
	
	int *results = malloc(slen * sizeof(int));
	memset(results, 0, slen * sizeof(int));
	for(i=0; i<=slen-strsLen; i++) {
		if(isMatch(s+i, words, wordsSize, wordsLen, strsLen) == 1) {
			results[*returnSize] = i;
			*returnSize = *returnSize + 1;
		}
	}
	
	return results;
}


int main()
{
	int returnSize = 0;
	int i = 0;

/*	char *words[2] = {"foo","bar"};
	int *results = findSubstring("barfoothefoobarman", words, 2, &returnSize);
*/
	char s[4096] = {0};
	memset(s, 'a', 4095);
	
	char *words[4096];
	for(i=0; i<4096; i++) {
		words[i] = "a";
	}
	int *results = findSubstring(s, words, 4096, &returnSize);

	
	printf("results = %d : ", returnSize);
	for(i=0; i<returnSize; i++) {
		printf("%d ", results[i]);
	}
	printf("\n");
	return 0;
}

