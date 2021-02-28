#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
typedef int ElemType;  
typedef int Status;  

typedef struct Stack_Node{
	ElemType data;
	struct Stack_Node *next;
}StackNode, *LinkStackNode;

//1.ջ�ĳ�ʼ��
Status StackInit( LinkStackNode &S){
  S = (StackNode *)malloc(sizeof(StackNode));
  S -> next = NULL;
  return OK;
}

//2.ѹջ
Status Push(LinkStackNode &top,ElemType e){
  StackNode *p;
  p = (StackNode *)malloc(sizeof(StackNode));
  if(!p) return ERROR;
  p -> data = e;
  p -> next = top -> next;
  top -> next = p;
  return OK;
}

//3.��ջ
Status Pop(LinkStackNode &top,ElemType &e){
	StackNode *p;
	if(top -> next == NULL) return ERROR;  //��ջ
	p = top -> next;
	e = p -> data;
	top -> next = p -> next;
	free(p);
	return OK; 
}

//4.DestoryStack
Status DestoryStack(LinkStackNode &top){
	LinkStackNode pre,p;
	if(top -> next == NULL) return ERROR;  //��ջ
	pre = top -> next;
	while(pre){
		p = pre -> next;
		free(pre);
		pre = p;
	}
	top -> next = NULL;
	return OK;
}

//5.StackLength
Status StackLength(LinkStackNode top){
	LinkStackNode p;
	int len = 0;
	if(top -> next == NULL) return len;  //��ջ 
	p = top;
	while(p -> next != NULL){
		p = p -> next;
		len++;
	}
	return len;
} 

//6.StackTraverse
Status StackTraverse(LinkStackNode top,Status(visit)(ElemType)){
	
	if(top -> next == NULL) return ERROR;
	
	LinkStackNode p = top;
	while(p -> next != NULL){
		p = p -> next;
		visit(p -> data);
	}
}

int PrintElem(ElemType e){
 	printf("  %d  |\n",e);
 	printf("-----\n");
}


main(){
	int i,len,flag;
	StackNode *S;
	printf("------------��ʼ��ջ-------------\n");
	flag = StackInit(S);
	if(flag) printf("��ʼ���ɹ�\n");
	else printf("��ʼ��ʧ��\n");

	printf("------------ѹջ + ��ȡ����-------------\n");
	Push(S,2);
	Push(S,3);
	Push(S,4);
	len = StackLength(S);
	printf("��ǰ����Ϊ: %d\n",len);
	
	printf("------------����ջ-------------\n");
	
	StackTraverse(S,PrintElem);
	
	printf("------------��ջ-------------\n");
	Pop(S,i);
	printf("%d\n",i);
	
	printf("------------����ջ-------------\n");
	flag = DestoryStack(S);
	if(flag) printf("yes\n");
	else printf("No\n");
	flag = Pop(S,i);
	if(flag) printf("��ջ�ɹ���ֵ��%d\n",i);
	else printf("��ջ\n");
	
	
}

