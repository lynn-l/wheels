/*
 *23. 合并K个排序链表
 *
 *描述 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 *
 *示例 输入:
 *		[
 * 			1->4->5,
 * 			1->3->4,
 * 			2->6
 *		]
 *		输出: 1->1->2->3->4->4->5->6
 *
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* minNode(struct ListNode** lists, int listsSize)
{
	if(NULL == lists || listsSize <= 0)
		return NULL;

	int i = 0;
	int tmpi = -1;
	struct ListNode *result = NULL;
	for(i=0; i<listsSize; i++) {
		if(lists[i] != NULL) {
			if(result == NULL || lists[i]->val < result->val) {
				result = lists[i];
				tmpi = i;
			}
		}	
	}

	if(tmpi >= 0)
		lists[tmpi] = lists[tmpi]->next;
	
	return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	if(NULL == lists || listsSize <= 0)
		return NULL;
	
	struct ListNode *result = NULL;
	struct ListNode **tmp = lists;
	int complete = 0;
	int i = 0;

	struct ListNode *iter = result = minNode(lists, listsSize);

	while(iter) {
		iter->next = minNode(lists, listsSize);
		iter = iter->next;
	}

	return result;
}

