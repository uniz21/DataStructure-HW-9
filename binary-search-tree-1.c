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

int precheck(Node *head);

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
			if (precheck(head))
			{
				inorderTraversal(head->left);
			}
			break;
		case 'p': case 'P':
			if (precheck(head))
			{
				preorderTraversal(head->left);
			}
			break;
		case 't': case 'T':
			if (precheck(head))
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

int precheck(Node* head)
{
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}

	if (head->left == NULL)
	{
		printf("There is no Tree");
		return 0;
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

void inorderTraversal(Node* ptr)
{
	/*
	* 전처리, 함수가 head->left를 매개변수로 받아 ptr이 NULL 포인터인 경우 함수 호출에서 에러가 나므로 커맨드 호출시 함수로 검사.
	if (ptr == NULL)
	{
		printf("There is no Tree");
		return -1;
	}
	*/

	if (ptr)
	{
		inorderTraversal(ptr->left);
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr)
	{
		printf("[%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{

	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}

	Node *p;
	Node* node2insert = (Node*)malloc(sizeof(Node));

	node2insert->key = key;
	node2insert->left = NULL;
	node2insert->right = NULL;

	p = head;

	while (1)
	{
		if (p->key == -9999)
		{
			if (p->left == NULL) 
			{
				p->left = node2insert;
				return 0;
			}
			p = p->left;
		}

		if (p->key > key)
		{
			if (p->left == NULL)
			{
				p->left = node2insert;
				return 0;
			}
			else
			{
				p = p->left;
			}
		}
		else if (p->key < key)
		{
			if (p->right == NULL)
			{
				p->right = node2insert;
				return 0;
			}
			else
			{
				p = p->right;
			}
		}
		else if (p->key == key)
		{
			if (p->left == NULL)
			{
				p->left = node2insert;
				return 0;
			}
			else if (p->right == NULL)
			{
				p->right = node2insert;
				return 0;
			}
			else
			{
				p = p->left;
			}
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