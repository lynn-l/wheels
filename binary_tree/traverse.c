/*binaryTraverse.c*/
/*
 *This file implement the non-recursive traverse of binary tree
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//struct BTree;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
typedef struct _BTree
{
	struct _BTree *parent;
	struct _BTree *leftChild;
	struct _BTree *rightChild;
	char name;
}BTree;

typedef struct
{
	int maxNum;
	int itemSize;
	int usedNum;
	void *stack;
}MyStack;

int DeleteStack(MyStack *stack)
{
	if(NULL == stack)
		return -1;

	free(stack->stack);
	free(stack);

	return 0;
}

BOOL StackIsEmpty(MyStack *stack)
{
	if(NULL == stack)
		return TRUE;
	return (stack->usedNum > 0) ? FALSE : TRUE;
}

MyStack *CreatStack(int num, int itemSize)
{
	if(num < 0 || itemSize < 0 || (num * itemSize) > 4096)
		return NULL;

	MyStack *stack = malloc(sizeof(MyStack));
	if(NULL == stack)
	{
		printf("%s:%d malloc error\n", __FUNCTION__, __LINE__);
		return NULL;
	}
	stack->maxNum = num;
	stack->itemSize = itemSize;
	stack->usedNum = 0;
	stack->stack = malloc(num * itemSize);
	if(NULL == stack->stack)
	{
		printf("%s:%d malloc error\n", __FUNCTION__, __LINE__);
		return NULL;
	}

	return stack;
}

void **GetStackTop(MyStack *stack)
{
	if(stack->usedNum <= 0)
		return NULL;

	return stack->stack + ((stack->usedNum - 1) * stack->itemSize);
}
int PrintStack(MyStack *stack)
{
	if(NULL == stack)
		return -1;
	
	int i = 0;
	BTree **temp = NULL;
	//printf("%s:%d stack has node ", __FUNCTION__, __LINE__);
	for(i=0; i<stack->usedNum; i++)
	{
		temp = (BTree **)(stack->stack + (i * stack->itemSize));
		printf("%d.%c ", i, (*temp)->name);
	}
	printf("\n");

	return 0;
}

int PushStack(MyStack *stack, void *data)
{
	if(NULL == stack || NULL == data)
		return -1;

	if(stack->usedNum < 0 || stack->usedNum >= stack->maxNum)
	{
		printf("%s:%d num %d < 0 or num > maxNum %d\n", __FUNCTION__, __LINE__, stack->usedNum, stack->maxNum);
		return -1;
	}
	BTree *temp = (BTree *)data;
	//printf("%s:%d Push node %c\n", __FUNCTION__, __LINE__, temp->name);
	
	BTree **temp2 = (BTree **)(stack->stack + (stack->usedNum * stack->itemSize));
	*temp2 = data;
	stack->usedNum++;

	PrintStack(stack);

	/*int i = 0;
	printf("%s:%d stack has node ", __FUNCTION__, __LINE__);
	for(i=0; i<stack->usedNum; i++)
	{
		temp2 = (BTree **)(stack->stack + (i * stack->itemSize));
		printf("%d.%c ", i, (*temp2)->name);
	}
	printf("\n");*/
	
	return 0;
}

int PopStack(MyStack *stack, void **data)
{
	if(NULL == stack || NULL == data)
		return -1;

	if(stack->usedNum <= 0 || stack->usedNum > stack->maxNum)
	{
		printf("%s:%d num %d < 0 or num > maxNum %d\n", __FUNCTION__, __LINE__, stack->usedNum, stack->maxNum);
		return -1;
	}

	BTree **temp = (BTree **)data;
	BTree **temp2 = stack->stack + ((stack->usedNum - 1) * stack->itemSize);
	*temp = *temp2;
	//printf("%s:%d Pop node %c\n", __FUNCTION__, __LINE__, (*temp)->name);
	stack->usedNum--;
	
	PrintStack(stack);
	
/*	int i = 0;
	printf("%s:%d stack has node ", __FUNCTION__, __LINE__);
	for(i=0; i<stack->usedNum; i++)
	{
		temp2 = (BTree **)(stack->stack + (i * stack->itemSize));
		printf("%d.%c ", i, (*temp2)->name);
	}
	printf("\n");*/

	return 0;
}

int PreTraverse(BTree *btree)
{
	if(NULL == btree)
		return -1;

	char nodeName[100];
	int size = 0;
	MyStack *stack = CreatStack(100, sizeof(BTree *));

	BTree *curNode = btree;
	while(NULL != curNode)
	{
//		printf("--------------------------------------------curNode->name = %c\n", curNode->name);
		nodeName[size++] = curNode->name;
		PushStack(stack, curNode);
		curNode = curNode->leftChild;

		while(NULL == curNode && StackIsEmpty(stack) == FALSE)
		{
			PopStack(stack, (void **)&curNode);
			curNode = curNode->rightChild;
		}		
	}

	int i = 0;
	printf("\n%s:%d results is ", __FUNCTION__, __LINE__);
	for(i=0; i<size; i++)
		printf("%c ", nodeName[i]);
	printf("\n\n\n");
	DeleteStack(stack);
	
	return 0;
}

int MiddleTraverse(BTree *btree)
{
	if(NULL == btree)
		return -1;

	char nodeName[100];
	int size = 0;
	MyStack *stack = CreatStack(100, sizeof(BTree *));

	BTree *curNode = btree;
	while(NULL != curNode)
	{		
		PushStack(stack, curNode);
		curNode = curNode->leftChild;

		while(NULL == curNode && StackIsEmpty(stack) == FALSE)
		{
			PopStack(stack, (void **)&curNode);
			nodeName[size++] = curNode->name;
			curNode = curNode->rightChild;
		}		
	}

	int i = 0;
	printf("\n%s:%d results is ", __FUNCTION__, __LINE__);
	for(i=0; i<size; i++)
		printf("%c ", nodeName[i]);
	printf("\n\n\n");
	DeleteStack(stack);
	
	return 0;
}

int PostTraverse(BTree *btree)
{
	if(NULL == btree)
		return -1;

	char nodeName[100];
	int size = 0;
	MyStack *stack = CreatStack(100, sizeof(BTree *));

	BTree *curNode = btree;
	BTree *lastPopNode = NULL;
	
	PushStack(stack, curNode);
	while(StackIsEmpty(stack) == FALSE)
	{
		curNode = *((BTree **)GetStackTop(stack));
		if((NULL == curNode->leftChild && NULL == curNode->rightChild)
			|| (NULL != lastPopNode && (curNode->rightChild == lastPopNode || curNode->leftChild == lastPopNode)))
		{
			nodeName[size++] = curNode->name;
			if(StackIsEmpty(stack) == TRUE)
				break;
			lastPopNode = curNode;
			PopStack(stack, (void **)&curNode);
			continue;
		}
		else
		{
			if(NULL != curNode->rightChild)
				PushStack(stack, curNode->rightChild);
			if(NULL != curNode->leftChild)
				PushStack(stack, curNode->leftChild);
		}
	}

	int i = 0;
	printf("\n%s:%d results is ", __FUNCTION__, __LINE__);
	for(i=0; i<size; i++)
		printf("%c ", nodeName[i]);
	printf("\n\n\n");
	DeleteStack(stack);
	
	return 0;
}

typedef enum
{
	left, 
	right
}ChildType;
BTree *AddBTreeNode(BTree *parent, ChildType type, char name)
{
	BTree *node = malloc(sizeof(BTree));
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->parent = parent;
	node->name = name;

	if(left == type)
	{
		parent->leftChild = node;
	}
	else if(right == type)
	{
		parent->rightChild = node;
	}
	
	return node;
}
BTree *InitBTree()
{
	BTree *MyBTree = malloc(sizeof(BTree));
	MyBTree->leftChild = NULL;
	MyBTree->rightChild = NULL;
	MyBTree->parent = NULL;
	MyBTree->name = 'A';

	BTree *B = AddBTreeNode(MyBTree, left, 'B');
	BTree *D = AddBTreeNode(B, left, 'D');
	BTree *E = AddBTreeNode(B, right, 'E');
	BTree *N = AddBTreeNode(E, right, 'N');
	BTree *O = AddBTreeNode(N, left, 'O');
	BTree *P = AddBTreeNode(N, right, 'P');
	
	BTree *C = AddBTreeNode(MyBTree, right, 'C');
	BTree *F = AddBTreeNode(C, left, 'F');
	BTree *G = AddBTreeNode(F, left, 'G');
	BTree *H = AddBTreeNode(F, right, 'H');
	BTree *I = AddBTreeNode(H, right, 'I');
	BTree *J = AddBTreeNode(I, right, 'J');
	BTree *K = AddBTreeNode(J, left, 'K');
	BTree *M = AddBTreeNode(J, right, 'M');

	return MyBTree;
}
int FreeBTree(BTree *btree)
{
	if(NULL == btree)
		return -1;
	
	if(NULL != btree->parent)
	{
		if(btree->parent->leftChild == btree)
			btree->parent->leftChild = NULL;
		else if(btree->parent->rightChild == btree)
			btree->parent->rightChild = NULL;
	}

	if(NULL != btree->leftChild)
		FreeBTree(btree->leftChild);
	if(NULL != btree->rightChild)
		FreeBTree(btree->rightChild);
	free(btree);

	return 0;
}

int main()
{
	BTree *MyBTree = InitBTree();
	PreTraverse(MyBTree);
	MiddleTraverse(MyBTree);
	PostTraverse(MyBTree);
	FreeBTree(MyBTree);
	return 0;
}
