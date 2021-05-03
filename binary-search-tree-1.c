/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int precheck(Node *head,int);

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			if (precheck(head,1))
			{
				/*
				* Traversal 함수들은 head가 아닌 head->left를 인자로 받기 때문에 초기화 되지 않은 경우,
				* NULL포인터 호출로 에러가 발생할 수 있어, 함수 호출 전에 전처리
				*/
				inorderTraversal(head->left);
			}
			break;
		case 'p': case 'P':
			if (precheck(head,1))
			{
				preorderTraversal(head->left);
			}
			break;
		case 't': case 'T':
			if (precheck(head,1))
			{
				postorderTraversal(head->left);
			}
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* 전처리 함수 */
int precheck(Node* head, int mode)
{
	/* 헤드노드 초기화 */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}
	switch (mode)
	{
		/* 순회함수 전처리 트리에 생성된 노드가 없는 경우 */
		case 1:
			if (head->left == NULL)
			{
				printf("There is no Tree");
				return 0;
			}
		default:
			break;
	}
	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/* 중위 순회 */
void inorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* 왼쪽노드를 먼저 탐색 */
		inorderTraversal(ptr->left);
		/* 오른쪽 노드를 탐색하기 전에 현재 노드를 표기 */
		printf("[%d] ", ptr->key);
		/* 오른쪽 노드 탐색 */
		inorderTraversal(ptr->right);
	}
}

/* 전위 순회 */
void preorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* 현재 노드를 표기 */
		printf("[%d] ", ptr->key);
		/* 왼쪽 노드 탐색 */
		preorderTraversal(ptr->left);
		/* 오른쪽 노드 탐색 */
		preorderTraversal(ptr->right);
	}
}

/* 후위 순회 */
void postorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* 왼쪽 노드 탐색 */
		postorderTraversal(ptr->left);
		/* 오른쪽 노드 탐색 */
		postorderTraversal(ptr->right);
		/* 현재 노드를 표기 */
		printf("[%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	/* 전처리 */
	if (!precheck(head, 0)) return 0;

	Node *p;

	/* 새로운 노드 생성 */
	Node* node2insert = (Node*)malloc(sizeof(Node));
	node2insert->key = key;
	node2insert->left = NULL;
	node2insert->right = NULL;

	p = head;

	while (1)
	{
		/* 현재노드가 헤드노드인 경우 */
		if (p->key == -9999)
		{
			/* 트리에 헤드노드를 제외한 노드가 없는 경우 새로운 노드를 헤드노드 왼쪽에 삽입 */
			if (p->left == NULL) 
			{
				p->left = node2insert;
				return 0;
			}
			/* 트리에 기존 노드가 있는 경우 다음 노드 탐색 */
			p = p->left;
		}

		/* 입력받은 키가 현재 노드의 키 값보다 작다면 */
		if (p->key > key)
		{
			if (p->left == NULL)
			{
				/* 비어있다면 노드 삽입 */
				p->left = node2insert;
				return 0;
			}
			/* 좌측에 기존 노드가 있는 경우 다음 노드 탐색 */
			p = p->left;
		}
		/* 입력받은 키가 현재 노드의 키 값보다 크다면 */
		else if (p->key < key)
		{
			if (p->right == NULL)
			{
				/* 비어있다면 노드 삽입 */
				p->right = node2insert;
				return 0;
			}
			/* 우측에 기존 노드가 있는 경우 다음 노드 탐색 */
			p = p->right;
		}
		/* 입력받은 키가 현재 노드의 키 값과 같다면 */
		else if (p->key == key)
		{
			/* 왼쪽노드를 우선 확인하고 비어 있으면 삽입 */
			if (p->left == NULL)
			{
				p->left = node2insert;
				return 0;
			}
			/* 오른쪽 노드를 확인하고 비어 있으면 새로운 노드 삽입 */
			else if (p->right == NULL)
			{
				p->right = node2insert;
				return 0;
			}
			/* 양쪽에 기존 노드가 있다면 탐색을 이어 나간다. */
			p = p->left;
		}
	}

	return 0;
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}

/* 재귀적으로 트리를 탐색하여 메모리 해제*/
int freeBST(Node* head)
{
	/* 전처리, 헤드가 초기화 되지 않은경우 리턴	*/
	if (!precheck(head,0)) return 0;

	/* 현재노드가 헤드노드면 왼쪽만 탐색 */
	if (head->right == head)
	{
		freeBST(head->left);
	}
	/* 양쪽노드가 NULL값이 아니면 메모리 해제 */
	else
	{
		if(head->left != NULL) freeBST(head->left);
		if(head->right != NULL) freeBST(head->right);
	}
	free(head);

	return 0;
}