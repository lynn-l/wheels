/*
 *描述 给定两个非空链表来表示两个非负整数。位数按照逆序方式存储，它们的每个节点只存储单个数字。将两数相加返回一个新的链表。
 *示例	输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 *		输出：7 -> 0 -> 8
 *		原因：342 + 465 = 807
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
	int val;
    struct ListNode *next;
};

struct ListNode* num2List(int num)
{	
	struct ListNode *result = NULL;
	struct ListNode *tail = NULL;
	do{
		if(result == NULL) {
			result = (struct ListNode *)malloc(sizeof(struct ListNode));
			tail = result;
		} else {
			tail->next = (struct ListNode *)malloc(sizeof(struct ListNode));
			tail = tail->next;
		}

		tail->val = num%10;
		num /= 10;
		tail->next = NULL;
		
	}while(num > 0);
	
	return result;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

    int a = 0;
    int b = 0;
    struct ListNode* sum = NULL;
    struct ListNode* tail = NULL;
    int jinwei = 0;
        
    while(l1 || l2 || jinwei == 1){
        if(l1) {
            a = l1->val;
            l1 = l1->next;
        }
        else
            a = 0;
        
        if(l2) {
            b = l2->val;
            l2 = l2->next;
        }
        else
            b = 0;
        
        if(tail == NULL) {
            tail = (struct ListNode*)malloc(sizeof(struct ListNode));
            sum = tail;
        } else {
            tail->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            tail = tail->next;
        }
            

        tail->val = a + b + jinwei;
        if(tail->val >= 10) {
            tail->val -= 10;
            jinwei = 1;
        } else
            jinwei = 0;
            
        tail->next = NULL;
    }
    
    return sum;
}

void listFree(struct ListNode* list)
{
	struct ListNode* next;

	while(list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}
int main()
{
	struct ListNode* a = num2List(342);
	struct ListNode* b = num2List(465);
	struct ListNode* result = addTwoNumbers(a, b);

	struct ListNode* tmp = result;

	while(tmp){
		printf("%d", tmp->val);
		if(NULL != tmp->next)
			printf("->");
		tmp = tmp->next;
	}
	printf("\n");
	
	listFree(a);
	listFree(b);
	listFree(result);
}
