/*
 *20. 有效的括号
 *
 *描述 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 *
 *		有效字符串需满足：
 *
 *		左括号必须用相同类型的右括号闭合。
 *		左括号必须以正确的顺序闭合。
 *		注意空字符串可被认为是有效字符串。
 *
 *示例 输入: "()"
 *		输出: true
 *
 *		输入: "()[]{}"
 *		输出: true
 *
 *		输入: "(]"
 *		输出: false
 *
 *		输入: "([)]"
 *		输出: false
 *
 *		输入: "{[]}"
 *输出: true
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
	if(NULL == s || strlen(s) <= 0)
		return true;

	int len = strlen(s);
	char tmp[len];
	memset(tmp, 0, len);


	int i = 0;
	int count = 0;

	for(i=0; i<len; i++) {	
		switch(s[i])
		{
			case '(':				
			case '{':
			case '[':
				tmp[count] = s[i];
				count++;
				break;
			case ')':
				if(count <= 0 || tmp[count - 1] != '(')
					return false;
				count--;
				break;
			case '}':
				if(count <= 0 || tmp[count - 1] != '{')
					return false;
				count--;
				break;			
			case ']':
				if(count <= 0 || tmp[count - 1] != '[')
					return false;
				count--;
				break;
			default:
				return false;
		}
	}

	if(count > 0)
		return false;
	
	return true;
}

int main()
{
	printf("%d\n", isValid("()"));
	printf("%d\n", isValid("()[]{}"));
	printf("%d\n", isValid("(]"));
	printf("%d\n", isValid("([)]"));
	printf("%d\n", isValid("{[]}"));
}
