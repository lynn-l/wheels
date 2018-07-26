/*
 *12. Min Stack
 *
 *Description	:Implement a stack with min() function, which will return the smallest number in the stack.
 *				 It should support push, pop and min operation all in O(1) cost.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minNum = 0;
int sizeStack = 0;
int sizeNum = 0;
int *stack = NULL;

void push(int number) {
	if(sizeNum == sizeStack || sizeStack == 0) {
		int *tmp = stack;
		
		stack = (int *)malloc((sizeStack + 100) * sizeof(int));
		if(sizeStack > 0) {
			memcpy(stack, tmp, sizeStack * sizeof(int));
			free(tmp);
		}
		sizeStack += 100;
	}
   
	stack[sizeNum] = number;
	
	if(number < minNum || 0 == sizeNum)
		minNum = number;
	
	sizeNum++;
}

int pop() {
	if(sizeNum <= 0)
		return -1;
	
	int tmp = stack[sizeNum - 1];
	
	sizeNum--;

	if(0 != sizeNum && minNum == tmp)
	{
		int i = 0;
		minNum = stack[0];
		for(i=0; i<sizeNum; i++)
			if(stack[i] < minNum)
				minNum = stack[i];
	}
	
	return tmp;
}


int min() {
	return minNum;
}

int main()
{
	push(1);
	printf("pop %d\n", pop());
	push(2);
	push(3);
	printf("min %d\n", min());
	push(1);
	printf("min %d\n", min());
}

