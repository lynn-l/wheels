/*
 *Description	:Count the number of k's between 0 and n. k can be 0 - 9.
 *Example		:if n = 12, k = 1 in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], we have FIVE 1's (1, 10, 11, 12)
 *
 */
 
#include <stdio.h>
#include <math.h>

int digitCounts(int k, int n)
{
    int len = 0;
    char buf[128] = {0};
    int result = 0;
    char tmp = '0' + k;
    
    while(n >= 0)
    {
        len += sprintf(buf+len, "%d", n);
        if(len >= 118 || n == 0)
        {
            int i = 0;
            for(i=0; i<len; i++)
            {
                if(buf[i] == tmp)
                    result++;
            }
            len = 0;   
        }
        n--;
    }
    
    return result;
}


