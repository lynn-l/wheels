/*
 *25. k个一组翻转链表
 *
 *描述 给出一个链表，每 k 个节点一组进行翻转，并返回翻转后的链表。
 *		k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么将最后剩余节点保持原有顺序。
 *
 *示例 给定这个链表：1->2->3->4->5
 *		当 k = 2 时，应当返回: 2->1->4->3->5
 *		当 k = 3 时，应当返回: 3->2->1->4->5
 *
 *说明 你的算法只能使用常数的额外空间。
 *		你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
   int val;
   struct ListNode *next;
};

int printList(struct ListNode *head, int n)
{
	int i = 0;
	for(i=0; i<n; i++) {
		printf("%d ", head->val);
		head = head->next;
	}
	printf("\n");
	
	return 0;
}

int reverseKNode(struct ListNode *head, struct ListNode *tail, int k)
{
	int i = 0;
	struct ListNode *next = tail->next;
	struct ListNode *tmpp = head;
	printf("before reverse:");
	printList(head, k);
	
	struct ListNode *tmp = head->next;
	struct ListNode *tmp1 = tmp->next;
	while(tmp != tail)	{
		tmp->next = head;
		head = tmp;

		tmp = tmp1;
		tmp1 = tmp1->next;
	}
	tail->next = head;

	tmpp->next = next;
	printf("after reverse:");
	printList(tail, k);

	return 0;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
	if(NULL == head || NULL == head->next || k <= 1)
		return head;

	struct ListNode *tmp = head;
	int count = 0;
	struct ListNode *tmpHead = NULL;
	struct ListNode *tmpTail = NULL;
	struct ListNode *tmp1 = NULL;
	struct ListNode *ret = NULL;
    struct ListNode *next = NULL;
	while(tmp) {
		count++;
        printf("count = %d, tmp = %d\n", count, tmp->val);
		if(count == 1) {
			tmpHead = tmp;
            printf("tmpHead = %d\n", tmpHead->val);
            tmp = tmp->next;
		} else if(count == k) {
            next = tmp->next;
			tmpTail = tmp;
            printf("tmpTail = %d\n", tmpTail->val);
			reverseKNode(tmpHead, tmpTail, k);
			if(tmp1 != NULL)
				tmp1->next = tmpTail;
			tmp1 = tmpHead;

			if(ret == NULL)
				ret = tmpTail;
			
            tmp = next;
			
			count = 0;
		} else
		    tmp = tmp->next;
	}
	
	return ret == NULL ? head : ret;
}

int main()
{
	struct ListNode list[5];
	int i = 0;
	for(i=0; i<5; i++) {
		list[i].val = i + 1;
		if(i == 4)
			list[i].next = NULL;
		else
			list[i].next = &list[i+1];
	}

	struct ListNode *ret = reverseKGroup(list, 2);

	printf("ret = ");
	printList(ret, 5);

	return 0;
}
