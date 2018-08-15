/*
 *21. 合并两个有序链表
 *
 *描述 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
 *
 *示例 输入：1->2->4, 1->3->4
 *		输出：1->1->2->3->4->4
 *
 */

struct ListNode {
   int val;
   struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	if(NULL == l1)
		return l2;
	if(NULL == l2)
		return l1;
	
	struct ListNode* tmp1 = l1;
	struct ListNode* tmp2 = l2;
	struct ListNode* tmp = NULL;
	struct ListNode* ret = NULL;

	while(tmp1 && tmp2) {
		if(tmp2->val <= tmp1->val) {
			if(ret == NULL) {
				ret = tmp2;
				tmp = tmp2;
			} else {
				tmp->next = tmp2;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		} else {
			if(ret == NULL) {
				ret = tmp1;
				tmp = tmp1;
			} else {
				tmp->next = tmp1;
				tmp = tmp->next;
			}
			tmp1 = tmp1->next;
		}
	}

	if(tmp1 != NULL)
		tmp->next = tmp1;
	else if(tmp2 != NULL)
		tmp->next = tmp2;
	
	return ret;
}

