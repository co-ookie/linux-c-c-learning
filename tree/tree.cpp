#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

typedef struct _node 
{
	int data; //数据域，一般是结构体
	struct _node *l_child;
	struct _node *r_child;
	struct _node *parent;
}node,*nodeptr;

//树节点的创建
nodeptr
construct_tree_node(int data)
{
	nodeptr temp = (nodeptr)malloc(sizeof(node));
	memset(temp,0,sizeof(node));	
	temp->data = data;
	temp->l_child = temp->r_child = temp->parent = NULL;
	return temp;
}

//树节点的插入操作
//相等情况暂不考虑
nodeptr add_node(nodeptr root,nodeptr newnode)
{
	
	if(root == NULL)
	{
		root = newnode;
		return root;
	}
	nodeptr temp = root;
	while(temp != NULL)
	{
		if(temp->data > newnode->data)
		{
			if(temp->l_child == NULL)
			{
				temp->l_child = newnode;
				newnode->parent = temp;
				return root;
			}
			temp = temp->l_child;
		}
		else if(temp->data < newnode->data)
		{
			if(temp->r_child == NULL)
			{
				temp->r_child = newnode;
				newnode->parent = temp;
				return root;
			}
			temp = temp->r_child;
		}
		else
		return root;		
	}
}

//排序二叉树的递归式实现(中序遍历)
void
inorder_traversal(nodeptr root)
{
	if(root == NULL) return;
	nodeptr temp = root;
	if(temp != NULL)
	{
		if(temp->l_child != NULL)
			inorder_traversal(temp->l_child);
		
		printf("%d ",temp->data);
		
		if(temp->r_child != NULL)
			inorder_traversal(temp->r_child);
	}
}

//排序二叉树的非递归式实现(中序遍历)
void
inorder_traversal_2(nodeptr root)
{
	
}

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("usage:%s data_count\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	int num = atoi(argv[1]);
	srand(time(NULL));
	nodeptr root = NULL;
	for(int i =0;i<num;i++)
	{
		nodeptr temp = construct_tree_node(rand()%100);
		root = add_node(root,temp);
	}
	inorder_traversal(root);
	printf("\n");
	return 0;
}