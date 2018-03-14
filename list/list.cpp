/***************************
*关于单链表的学习 by luoms 20180314
***************************/


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

typedef struct List
{
	int data;
	struct List *next;
}ListNode,*ListNodePtr;

void
List_Print(ListNodePtr head)
{	
	ListNodePtr temp = head;
	while(head)
	{
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}

//从头部添加新节点
ListNodePtr 
insert_head(ListNodePtr head,ListNodePtr NewNode)
{
	//assert(head);
	assert(NewNode);
	
	NewNode->next = head;
	head = NewNode;
	
	return head;
}

//添加新节点到尾部
ListNodePtr
insert_tail(ListNodePtr head,ListNodePtr NewNode)
{
	assert(NewNode);
	if (head == NULL)
	{
		head = NewNode;
	}
	else
	{
		ListNodePtr temp = head;
		while(temp->next)
		{
			temp = temp->next;
		}
		NewNode->next = NULL;
		temp->next = NewNode;
	}
	return head;
}


//添加新节点到中间  节点不合法失败返回NULL
ListNodePtr
insert_node(ListNodePtr head,ListNodePtr location,ListNodePtr NewNode)
{
	assert(head);
	assert(NewNode);
	assert(location);
	//遍历链表 判断节点是否存在
	ListNodePtr temp = head;
	while(temp)
	{
		if (temp == location) 
		{
			ListNodePtr s_next = location->next;
			NewNode->next = s_next;
			temp->next = NewNode;
			return head;
		}
		temp = temp->next;
	}
	if (temp == NULL) return NULL;
}

ListNodePtr
delete_node(ListNodePtr head,int data)
{
	if (head ==NULL) return NULL;
	
	ListNodePtr temp = head;
	if(temp->data == data)
	{
		head = head->next;
		//free(temp);
		return head;
	}

	ListNodePtr prev = head;
	temp = head->next;
	
	while(temp != NULL && temp->data != data)
	{
		prev = temp;
		temp = temp->next;
	}
	
	if (temp == NULL) return NULL;
	
	prev->next = temp->next;
	//free(temp);
	
	return head;
}	

//for test
int main()
{
	ListNodePtr head = NULL;
	ListNode f={6,NULL},e={5,&f},d={4,&e},c={3,&d},b={2,&c},a={1,&b};
	ListNode z={100,NULL};
	srand(time(NULL));//随机数种子
	int i=0;
	for(;i<1;i++)
	{
		ListNodePtr newnode = (ListNodePtr)malloc(sizeof(ListNode));
		newnode->data = rand()%100;
		newnode->next = NULL;

		//head = insert_head(head,newnode);
		
		//head = insert_tail(head,newnode);
		
		//if (!insert_node(&a,&z,newnode))
		//{
			//printf("location is illegal!\n");
			//return -1;
		//}
		//head = &a;
		
		if((head = delete_node(&a,1)) == NULL)
		{
			printf("delete node failed!\n");
		}
				
		List_Print(head);
		getchar();
	}
	return 0;
}
	