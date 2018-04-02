#include<stdio.h>

typedef struct _node
{
	int h;
	int data;
	struct _node *left;
	struct _node *right;
}node,*pnode;

int get_hight(pnode s_node);

int max_hight(pnode left,pnode right)
{
	h_left = get_hight(left);
	h_right  = get_hight(right);
	if(h_left - h_right > 0)
		return h_left;
	else
		return h_right;
}

int get_hight(pnode s_node)
{
	if(s_node == NULL) return -1;
	return max_hight(s_node->left,s_node->right)+1;
}
//
pnode
constuct_avltree_node(int data)
{
	pnode temp = (pnode)malloc(sizeof(node));
	memset(temp,0,sizeof(node));
	temp->data = data;
	temp->left = temp->right = NULL;
	temp->h = get_hight(temp);//高度
}

pnode 
add_node(pnode root,pnode newnode)
{
	if(root == NULL) return newnode;
	pnode = temp = root;
}