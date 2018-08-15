/*
 *24. 两两交换链表中的节点
 *
 *描述 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 *
 *示例 给定 1->2->3->4, 你应该返回 2->1->4->3.
 *
 *说明 你的算法只能使用常数的额外空间。
 *		你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 *
 */

struct ListNode {
   int val;
   struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
	if(NULL == head || NULL == head->next)
		return head;
	
	struct ListNode *ret = head->next;
	struct ListNode *tmp = head;
	struct ListNode *tmp2 = head->next;
	struct ListNode *tmp3 = NULL;
	while(tmp && tmp->next) {
		tmp2 = tmp->next;
		
		if(tmp3 != NULL)
			tmp3->next = tmp2;
	
		tmp->next = tmp2->next;
		tmp2->next = tmp;

		tmp3 = tmp;
		tmp = tmp->next;
	}

	return ret;
}

