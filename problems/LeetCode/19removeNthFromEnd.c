/*
 *19. 删除链表的倒数第N个节点
 *
 *描述 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 *
 *说明 给定的 n 保证是有效的。
 *
 *示例 给定一个链表: 1->2->3->4->5, 和 n = 2. 当删除了倒数第二个节点后，链表变为 1->2->3->5.
 *
 *进阶 你能尝试使用一趟扫描实现吗？
 *
 */
struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	if(NULL == head || n <= 0)
		return NULL;
	if(NULL == head->next && n > 0)
		return NULL;
	
	int count = 0;
	struct ListNode* tmp = head;
	struct ListNode* nodeDel = NULL;
	while(tmp->next != NULL) {
		tmp = tmp->next;
		if(count < n - 1) {
			count++;
		}
		else {
			if(NULL == nodeDel)
				nodeDel = head;
			else
				nodeDel = nodeDel->next;
		}
	}

	if(nodeDel == NULL)
		return head->next;
	//free(nodeDel->next)	;
	nodeDel->next = nodeDel->next->next;

	return head;
}

