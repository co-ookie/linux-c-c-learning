#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

typedef struct _member
{
	char ch;
	int line;
	int colnum;
}node,*nodeptr;

typedef struct _stack_ds
{
	int size;
	int member;
	node ptr[0];
}stack_ds,*stack_dsptr;

stack_dsptr
init_stack(int size);
{
	stack_dsptr head =  (stack_dsptr)malloc(sizeof(stack_ds)+sizeof(node)*size);
	head->size = size;
	head->member = 0;
	memset(head->ptr,0,sizeof(node)*size);
	return head;
}

void
destroy_stack(stack_dsptr head)
{
	free(head);
}

void
push_stack(stack_dsptr head,char ch,int line,int colnum)
{
	if(head->member == head->size)
	{
		//realloc statck memory...
	}
	head->ptr[head->member].ch = ch;
	head->ptr[head->member].line = line;
	head->ptr[head->member].colnum = colnum;
	
	head->member++;
}

nodeptr
pop_stack(stack_dsptr head);
{
	if(head->member == 0) return NULL;
	head->member--;
	return head->ptr + head->member;
}

char fetch_top_mem(stack_dsptr head)
{
	if(head->member == 0) return -1;
	return head->ptr[head->member-1].ch;
}

int is_empty_stack(stack_dsptr head)
{
	if(head->member <= 0) return 0;
	return -1;
}

int main(int argc ,char *argv[])
{
	if(argc != 2)
	{
		printf("usage:%s filename \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	int line = 1;
	int colnum = 0;
	char ch = -1;
	
	while(feof(fp) == 0 )
	{
		ch = fgetc(fp);
		if(map[ch] == 0) continue;
		int ret = process();
	}
}