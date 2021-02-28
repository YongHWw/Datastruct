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

//���е���ʽ��ʾ

typedef struct QNode{
	ElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QNode *front;   //   ͷָ��  
	QNode *rear;    //   βָ�� 
}LinkQueue;


//1.���г�ʼ�� 
Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front -> next = NULL;
	return OK;
}

//2.���
Status EnQueue(LinkQueue &Q,ElemType e){
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) return ERROR;
	p -> data = e;
	p -> next = NULL;
	
	Q.rear -> next = p;
	Q.rear = p;
	return OK; 
} 

//3.���� 
Status DeQueue(LinkQueue &Q,ElemType &e){
	QueuePtr p;
	
	if(Q.front == Q.rear) return ERROR; //�ն�
	
	p = Q.front -> next;
	e = p -> data;
	
	Q.front -> next = p -> next;
	
	if(Q.rear == p) Q.rear = Q.front;
	
	free(p);
	
	return OK;	 
}


//4.��ȡ����
Status QueueLength(LinkQueue Q){
	int count = 0;
	QueuePtr p = Q.front;
	
	while(p != Q.rear){
		count++;
		p = p -> next; 
	}
	
	return count;
}
 

//5.���� 
Status QueueTraverse(LinkQueue &Q,Status(visit)(ElemType)){
	QueuePtr p;
	int count,i; 
	count = QueueLength(Q);
	
	for(i = 0;i < count;i++){
		printf("------");
	}
	printf("\n");
	
	p = Q.front -> next;
	
	while(p){
		visit(p -> data);
		p = p -> next;
	}
	printf("\n");
}

int PrintElem(ElemType e){
	printf("  %d  |",e);
}


//6.�ж��Ƿ�Ϊ��
Status QueueEmpty(LinkQueue Q){
	if(Q.front == Q.rear) return OK;
	else return ERROR;
} 


//7.��ȡ��ͷԪ��
Status GetHead(LinkQueue Q,ElemType &e){
	QueuePtr p;
	if(Q.front == Q.rear) return ERROR;
	
	p = Q.front -> next;
	e = p -> data;
	
	return OK;
} 


//8.��ն���
Status ClearQueue(LinkQueue &Q){
	Q.rear = Q.front -> next;
	
	while(Q.rear){
		Q.front -> next = Q.rear -> next;
		free(Q.rear);
		Q.rear = Q.front -> next;
	}
	
	Q.rear = Q.front; 
} 


//9.���ٶ��� (��βָ��ָ��ͷָ�����һ��������ͷָ�룬ͷָ��ָ���βָ����һ����һ��ѭ����ֱ��ͷָ��ΪNULL)
Status DestoryQueue(LinkQueue *Q){
	while((*Q).front){
		(*Q).rear = (*Q).front -> next;
		free((*Q).front);   
		(*Q).front = (*Q).rear;		
	}
} 

/*
�������ٶ����õĲ�����ʽ��ǰ��Ĳ�һ����ǰ��ĺ����Ĳ�����ʽ�����ò���(&Q)���������õ���һ��ָ�����(*Q)��
���ǵ�ʹ��Ч����һ���ģ����ǿ��Ըı�������������ʱ������Ǹ���������������õ�ָ������Ļ���
�������е��������������Ҫ��ָ���������(*Q).front �ȵ� .���������ڵĲ��������ı�Q���������������ݣ�
��ô���Խ�������Q�����������������Ҫ���ò�������ָ������� 
*/ 

main(){
	int e,flag;
	LinkQueue Q;
	printf("------------------���г�ʼ��------------------------\n"); 
	flag = InitQueue(Q);    //LinkQueue ����ָ���������InitQueue�Ĳ�����ָ�룬���Ҫ��&��ȡQ�ĵ�ַ 
	if(flag) printf("Init successed\n");
	else printf("Init Error\n");
	
	printf("------------------�������------------------------\n"); 
	EnQueue(Q,1);
	EnQueue(Q,2);
	EnQueue(Q,3);
	QueueTraverse(Q,PrintElem); 
	
	printf("------------------���г���------------------------\n"); 
	DeQueue(Q,e);
	printf("%d\n",e);
	QueueTraverse(Q,PrintElem); 
	
	printf("------------------��ȡ��ͷԪ�� + �ж��Ƿ�Ϊ��------------------------\n"); 
	GetHead(Q,e);
	printf("%d\n",e);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
	
	printf("------------------��ն���------------------------\n"); 
	ClearQueue(Q);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
	
	printf("------------------���ٶ���------------------------\n"); 
	DestoryQueue(&Q);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
}
