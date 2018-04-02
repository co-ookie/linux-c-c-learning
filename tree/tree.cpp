#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
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

//查找方法
nodeptr
search_tree(nodeptr root,int data)
{
	
	nodeptr temp = root;
	while(temp != NULL)
	{
		if(temp->data == data) return temp;
		if(temp->data > data)
		{
			temp = temp->l_child;
		}
		else
		{
			temp = temp->r_child;
		}
	}
	return NULL;
}

nodeptr
search_max_l_tree(nodeptr root)
{
	assert(root);
	nodeptr temp = root;
	while(temp != NULL && temp->r_child != 	NULL)
	{
		temp=temp->r_child;
	}
	return temp;
}

nodeptr
search_min_r_tree(nodeptr root)
{
	assert(root);
	nodeptr temp =root;
	while(temp != NULL && temp->l_child != 	NULL)
	{
		temp=temp->l_child;
	}
	return temp;
}
nodeptr delete_node(nodeptr root,int data);

void
cut_link_from_tree(nodeptr node)
{
	if(node->l_child == NULL && node->r_child == NULL)
	{
		if(node->parent->l_child == node)
			node->parent->l_child = NULL;
		else if(node->parent->r_child == node)
			node->parent->r_child = NULL;
	}
	else
	{
		if(node->l_child != NULL)
		{
			if(node->parent->l_child == node)
				node->parent->l_child = node->l_child;
			else if(node->parent->r_child == node)
				node->parent->r_child = node->l_child;
		}
		else if(node->r_child != NULL)
		{
			if(node->parent->l_child == node)
				node->parent->l_child = node->r_child;
			else if(node->parent->r_child == node)
				node->parent->r_child = node->r_child;
		}
	}
}
nodeptr
delete_node(nodeptr root,int data)
{
	nodeptr ret = search_tree(root,data);
	nodeptr replace = NULL;
	if(ret == NULL)
	{
		printf("no such data\n");
		return root;
	}
	
	if(ret->l_child != NULL )
	{
		replace = search_max_l_tree(ret);
	}
	else if(ret->r_child != NULL)
	{
		replace = search_min_r_tree(ret);
	}
	else
	{
		cut_link_from_tree(ret);
		free(ret);
		//删除的是根节点，相当于为空树
		if(ret == root) return NULL;
		else return root;
	}
	cut_link_from_tree(replace);
	ret->data = replace->data;
	free(replace);		
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
	
#if 0	
	printf("pls input search data:");
	int data;
	scanf("%d",&data);
	nodeptr ret = search_tree(root,data);
	if(ret == NULL)
	{
		printf("not found.\n");
	}
	else
	{
		printf("found data[%d] local:%p",ret->data,ret);
	}
#endif
	while(1)
	{
		printf("pls input delete data:");
		int data;
		scanf("%d",&data);
		getchar();
		nodeptr ret = delete_node(root,data);
		inorder_traversal(ret);
		printf("\n");
	}
	
	return 0;
}