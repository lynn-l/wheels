/*
 *17. 电话号码的字母组合 	
 *
 *描述 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 *
 *示例 输入："23"
 *		输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 *说明 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
 *
 */

 /**
  * Return an array of size *returnSize.
  * Note: The returned array must be malloced, assume caller calls free().
  */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int size;
	char c[5];
}letterMap;

char** letterCombinations(char* digits, int* returnSize) {
	if(NULL == digits || NULL == returnSize || strlen(digits) <= 0)
		return NULL;

	letterMap map[10] = {{0, ""},{0, ""},{3, "abc"},{3, "def"},{3, "ghi"},{3, "jkl"},{3, "mno"},{4, "pqrs"},{3, "tuv"},{4, "wxyz"}};

	int len = strlen(digits);
	int i = 0;
	int retSize = 1;
	int index = 0;
	for(i=0; i<len; i++) {
		index = digits[i] - '0';
		//printf("digits[%d] = %c, index = %d, map[index].size = %d\n", i, digits[i], index, map[index].size);
		if(map[index].size > 0) {
			retSize *= map[index].size;
		}
	}
	if(retSize == 1)
		retSize = 0;
	//printf("retSize = %d\n", retSize);
	char **results = (char **)malloc(retSize * sizeof(char *));
	for(i=0; i<retSize; i++) {
		results[i] = (char *)malloc(len + 1);
		memset(results[i], 0, len + 1);
	}
	//printf("1\n");
	int tmpLen = 0;
	int j = 0;
	int k = 1;
	int step = 0;
	int l = 0;
	for(i=0; i<len; i++) {
		index = digits[i] - '0';
		//printf("index = %d\n", 0);
		if(map[index].size > 0) {
			k *= map[index].size;
			step = retSize / k;
			//printf("k = %d, step = %d\n", k, step);
			for(j=0; j<retSize; j++) {
				l = j/step%map[index].size;
				results[j][tmpLen] = map[index].c[l];
				//printf("j = %d, tmplen = %d, l = %d, c = %c\n", j, tmpLen, l, map[index].c[l]);
			}
			tmpLen++;
		}
	}

	*returnSize = retSize;
	
	return results;
}


int main()
{
	int size = 0;
	char **ret = letterCombinations("23", &size);
	printf("size = %d\n", size);
	int i = 0;
	for(i=0; i<size; i++) {
		printf("%s\n", ret[i]);
	}
	
	return 0;
}

