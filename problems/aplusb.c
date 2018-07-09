/*
 *Description	:Write a function that add two numbers A and B.
 *Challenge		:You should not use + or any arithmetic operators.
 *
 */
 
#include <stdio.h>

//basic
int aplusb(int a, int b)
{
	int result = 0;
	int i = 0;
	int atmp = 0;
	int btmp = 0;
	int carry = 0;
	
	while(i < 32)
	{
		atmp = a & 0x01;
		btmp = b & 0x01;

		if(atmp & btmp){
			if(carry)
				result |= (0x01 << i);
			carry = 1;
		} else if(atmp | btmp) {
			if(carry) {
				carry = 1;
			} else {
				result |= (0x01 << i);
			}
		} else {
			if(carry)
				result |= (0x01 << i);
			carry = 0;
		}
		//printf("result = %d, i = %d, a = %d, a >> 1 = %d, b = %d, b >> 1 = %d\n", result, i, a, a >> 1, b, b >> 1);
		a = a >> 1;
		b = b >> 1;
		
		i++;
	}

	return result;
}

//advanced
int aplusb2(int a, int b)
{
	int c = 0;
	int d = 0;

	do{
		c = (a & b) << 1;
		d = a ^ b;
		a = c;
		b = d;
	}while(c);

	return d;
}

int main()
{
	int sum = aplusb2(2255, 2333);
	printf("sum = %d\n", sum);

	return 0;
}
