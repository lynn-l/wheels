/*
 *22. 括号生成
 *
 *描述 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 *
 *例如 给出 n = 3，生成结果为：
 *
 *		[
 *		  "((()))",
 *		  "(()())",
 *		  "(())()",
 *		  "()(())",
 *		  "()()()"
 *		]
 *
 */

/**
* Return an array of size *returnSize.
* Note: The returned array must be malloced, assume caller calls free().
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int addParenthesis(char *s, int current, int maxlen, int leftCount, char **result, int *count)
{
	if(current >= maxlen - 1) {
		result[*count] = (char *)malloc(maxlen + 1);
		//printf("count = %d, s = %s, %p\n", *count, s, result[*count]);
		strcpy(result[*count], s);
		(*count)++;
		return 0;
	} else {
		s[current + 1] = '\0';
		//printf("current = %d, leftcount = %d, s = %s\n", current, leftCount, s);
		if(current + leftCount < maxlen - 1) {
			s[current+1] = '(';
			addParenthesis(s, current+1, maxlen, leftCount + 1, result, count);
		}
		if(leftCount > 0) {
			s[current+1] = ')';
			addParenthesis(s, current+1, maxlen, leftCount - 1, result, count);
		}
	}

	return 0;
}

char** generateParenthesis(int n, int* returnSize) {
	if(n <= 0 || returnSize == NULL) {
		*returnSize = 0;
		return NULL;
	}
	int maxsize = pow(2, n + n);
	char **result = (char **)malloc(maxsize * sizeof(char *));
	memset(result, 0, maxsize * sizeof(char *));
	
	char buf[n+n+1];
	memset(buf, 0, n + n + 1);

	int current = 0;
	int maxlen = n + n;
	int leftCount = 0;
	int count = 0;
	
	buf[current] = '(';
	leftCount++;
	addParenthesis(buf, current, maxlen, leftCount, result, &count);

	*returnSize = count;

	return result;
}

int main()
{
	int size = 0;
	char **ret = generateParenthesis(5, &size);
	printf("retsize = %d\n", size);
	int i = 0;
	for(i=0; i<size; i++) {
		printf("ret[%d]:%s\n", i, ret[i]);
		free(ret[i]);
	}
	free(ret);
}
