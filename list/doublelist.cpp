//双向链表（非环装）的学习
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

//通过结构体成员找该结构体的首地址
#define addr_head(type,ptr,memb)  (type *)((unsigned char *)ptr - (unsigned long)&(((type *)0)->memb))

//链表与数据分离
typedef struct DoubleList
{
	struct DoubleList *prev;
	struct DoubleList *next;
}DOUBLELIST,*DoubleListPtr;


void init_DoubleList(DoubleListPtr head)
{
	head->next=head->prev=head;
}

struct stone
{	
	DoubleList node;
	char data[4+1];
	stone()
	{
		init_DoubleList(&node);
		memset(data,0,sizeof(data));
	}
};

DoubleListPtr
return_head(DoubleListPtr local)
{
	assert(local);
	DoubleListPtr temp = local;
	while(temp->prev != NULL)
	{
		temp = temp->prev;
	}
	
	return temp;
}

//在local之前的位置插入一个新节点
DoubleListPtr
add_node(DoubleListPtr newnode,DoubleListPtr local)
{
	assert(newnode);
	assert(local);
	if(local->prev == NULL)
	{
		newnode->next = local;
		local->prev = newnode;
		newnode->prev = NULL;	
	}
	else
	{
		DoubleListPtr s_prev = local->prev;
		s_prev->next = newnode;
		newnode->next = local;
		local->prev = newnode;
		newnode->prev = s_prev;
	}
	return return_head(newnode);
}

DoubleListPtr
delete_node(DoubleListPtr local)
{
	assert(local);
	if(local->prev = NULL)
	{
		DoubleListPtr temp = local->next;
		temp->prev = NULL;
		return return_head(temp);
	}
	else if(local->next = NULL)
	{
		DoubleListPtr temp = local->prev;
		temp->prev = NULL;
		return return_head(temp);
	}
	else
	{
		DoubleListPtr s_prev = local->prev;
		DoubleListPtr s_next = local->next;
		s_prev->next = s_next;
		s_next->prev = s_prev;
		//free(local);	
		return return_head(s_prev);		
	}
}
void
ptint_stone(DoubleListPtr head)
{
	stone *stone_ptr;
	DoubleListPtr temp = head;
	while(temp != NULL)
	{
		stone_ptr = addr_head(stone,temp,node);
		printf("%s ",stone_ptr->data);
		temp = temp->next;
	}
	printf("\n");
}


//for test
int main()
{
	stone *a = (stone *)malloc(sizeof(stone));
	stone *b = (stone *)malloc(sizeof(stone));
	stone *c = (stone *)malloc(sizeof(stone));
	memcpy(a->data,"000a",5);
	memcpy(b->data,"000b",5);
	memcpy(c->data,"000c",5);
	a->node.prev = NULL;
	c->node.next = NULL;
	add_node(&(b->node),&(c->node));
	DoubleListPtr head = add_node(&(a->node),&(b->node));
	ptint_stone(&(a->node));
	free(a);
	free(b);
	free(c);	
	return 0;
}