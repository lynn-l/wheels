/*
 *14. 最长公共前缀
 *
 *描述 编写一个函数来查找字符串数组中的最长公共前缀。
 *		如果不存在公共前缀，返回空字符串 ""。
 *
 *示例	输入: ["flower","flow","flight"]
 *		输出: "fl"
 *
 *		输入: ["dog","racecar","car"]
 *		输出: ""
 *		解释: 输入不存在公共前缀。
 *
 *说明 所有输入只包含小写字母 a-z 。
 */
 
char* longestCommonPrefix(char** strs, int strsSize) {
	if(NULL == strs || strsSize <= 0)
		return "";
	if(strsSize == 1)
		return strs[0];

	static char result[128] = {0};
	memset(result, 0, 128);
	int len = 0;
	int i = 0;
	while(1){
		for(i=1; i<strsSize; i++) {
			if(strs[i][len] == '\0' || strs[i-1][len] == '\0' || strs[i][len] != strs[i-1][len])
				return result;
		}
		result[len] = strs[0][len];
		len++;
	}

	return result;
}

