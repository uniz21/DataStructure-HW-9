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
				* Traversal �Լ����� head�� �ƴ� head->left�� ���ڷ� �ޱ� ������ �ʱ�ȭ ���� ���� ���,
				* NULL������ ȣ��� ������ �߻��� �� �־�, �Լ� ȣ�� ���� ��ó��
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

/* ��ó�� �Լ� */
int precheck(Node* head, int mode)
{
	/* ����� �ʱ�ȭ */
	if (head == NULL)
	{
		printf("Initialize First");
		return 0;
	}
	switch (mode)
	{
		/* ��ȸ�Լ� ��ó�� Ʈ���� ������ ��尡 ���� ��� */
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

/* ���� ��ȸ */
void inorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* ���ʳ�带 ���� Ž�� */
		inorderTraversal(ptr->left);
		/* ������ ��带 Ž���ϱ� ���� ���� ��带 ǥ�� */
		printf("[%d] ", ptr->key);
		/* ������ ��� Ž�� */
		inorderTraversal(ptr->right);
	}
}

/* ���� ��ȸ */
void preorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* ���� ��带 ǥ�� */
		printf("[%d] ", ptr->key);
		/* ���� ��� Ž�� */
		preorderTraversal(ptr->left);
		/* ������ ��� Ž�� */
		preorderTraversal(ptr->right);
	}
}

/* ���� ��ȸ */
void postorderTraversal(Node* ptr)
{
	if (ptr)
	{
		/* ���� ��� Ž�� */
		postorderTraversal(ptr->left);
		/* ������ ��� Ž�� */
		postorderTraversal(ptr->right);
		/* ���� ��带 ǥ�� */
		printf("[%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	/* ��ó�� */
	if (!precheck(head, 0)) return 0;

	Node *p;

	/* ���ο� ��� ���� */
	Node* node2insert = (Node*)malloc(sizeof(Node));
	node2insert->key = key;
	node2insert->left = NULL;
	node2insert->right = NULL;

	p = head;

	while (1)
	{
		/* �����尡 ������� ��� */
		if (p->key == -9999)
		{
			/* Ʈ���� ����带 ������ ��尡 ���� ��� ���ο� ��带 ����� ���ʿ� ���� */
			if (p->left == NULL) 
			{
				p->left = node2insert;
				return 0;
			}
			/* Ʈ���� ���� ��尡 �ִ� ��� ���� ��� Ž�� */
			p = p->left;
		}

		/* �Է¹��� Ű�� ���� ����� Ű ������ �۴ٸ� */
		if (p->key > key)
		{
			if (p->left == NULL)
			{
				/* ����ִٸ� ��� ���� */
				p->left = node2insert;
				return 0;
			}
			/* ������ ���� ��尡 �ִ� ��� ���� ��� Ž�� */
			p = p->left;
		}
		/* �Է¹��� Ű�� ���� ����� Ű ������ ũ�ٸ� */
		else if (p->key < key)
		{
			if (p->right == NULL)
			{
				/* ����ִٸ� ��� ���� */
				p->right = node2insert;
				return 0;
			}
			/* ������ ���� ��尡 �ִ� ��� ���� ��� Ž�� */
			p = p->right;
		}
		/* �Է¹��� Ű�� ���� ����� Ű ���� ���ٸ� */
		else if (p->key == key)
		{
			/* ���ʳ�带 �켱 Ȯ���ϰ� ��� ������ ���� */
			if (p->left == NULL)
			{
				p->left = node2insert;
				return 0;
			}
			/* ������ ��带 Ȯ���ϰ� ��� ������ ���ο� ��� ���� */
			else if (p->right == NULL)
			{
				p->right = node2insert;
				return 0;
			}
			/* ���ʿ� ���� ��尡 �ִٸ� Ž���� �̾� ������. */
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

/* ��������� Ʈ���� Ž���Ͽ� �޸� ����*/
int freeBST(Node* head)
{
	/* ��ó��, ��尡 �ʱ�ȭ ���� ������� ����	*/
	if (!precheck(head,0)) return 0;

	/* �����尡 ������ ���ʸ� Ž�� */
	if (head->right == head)
	{
		freeBST(head->left);
	}
	/* ���ʳ�尡 NULL���� �ƴϸ� �޸� ���� */
	else
	{
		if(head->left != NULL) freeBST(head->left);
		if(head->right != NULL) freeBST(head->right);
	}
	free(head);

	return 0;
}