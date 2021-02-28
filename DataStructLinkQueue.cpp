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

//队列的链式表示

typedef struct QNode{
	ElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QNode *front;   //   头指针  
	QNode *rear;    //   尾指针 
}LinkQueue;


//1.队列初始化 
Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front -> next = NULL;
	return OK;
}

//2.入队
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

//3.出队 
Status DeQueue(LinkQueue &Q,ElemType &e){
	QueuePtr p;
	
	if(Q.front == Q.rear) return ERROR; //空队
	
	p = Q.front -> next;
	e = p -> data;
	
	Q.front -> next = p -> next;
	
	if(Q.rear == p) Q.rear = Q.front;
	
	free(p);
	
	return OK;	 
}


//4.获取长度
Status QueueLength(LinkQueue Q){
	int count = 0;
	QueuePtr p = Q.front;
	
	while(p != Q.rear){
		count++;
		p = p -> next; 
	}
	
	return count;
}
 

//5.遍历 
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


//6.判断是否为空
Status QueueEmpty(LinkQueue Q){
	if(Q.front == Q.rear) return OK;
	else return ERROR;
} 


//7.获取队头元素
Status GetHead(LinkQueue Q,ElemType &e){
	QueuePtr p;
	if(Q.front == Q.rear) return ERROR;
	
	p = Q.front -> next;
	e = p -> data;
	
	return OK;
} 


//8.清空队列
Status ClearQueue(LinkQueue &Q){
	Q.rear = Q.front -> next;
	
	while(Q.rear){
		Q.front -> next = Q.rear -> next;
		free(Q.rear);
		Q.rear = Q.front -> next;
	}
	
	Q.rear = Q.front; 
} 


//9.销毁队列 (队尾指针指向头指针的下一个，销毁头指针，头指针指向队尾指针下一个，一次循环，直到头指针为NULL)
Status DestoryQueue(LinkQueue *Q){
	while((*Q).front){
		(*Q).rear = (*Q).front -> next;
		free((*Q).front);   
		(*Q).front = (*Q).rear;		
	}
} 

/*
这里销毁队列用的参数形式和前面的不一样，前面的函数的参数形式是引用参数(&Q)，而这里用的是一个指针参数(*Q)。
它们的使用效果是一样的，都是可以改变调用这个函数的时候传入的那个参数，但是如果用的指针参数的话，
后面所有调用这个参数都需要是指针参数，即(*Q).front 等等 .如若函数内的操作，不改变Q这个参数本身的内容，
那么可以仅仅传入Q这个参数本身，而不需要引用参数或者指针参数。 
*/ 

main(){
	int e,flag;
	LinkQueue Q;
	printf("------------------队列初始化------------------------\n"); 
	flag = InitQueue(Q);    //LinkQueue 不是指针变量，而InitQueue的参数是指针，因此要用&获取Q的地址 
	if(flag) printf("Init successed\n");
	else printf("Init Error\n");
	
	printf("------------------队列入队------------------------\n"); 
	EnQueue(Q,1);
	EnQueue(Q,2);
	EnQueue(Q,3);
	QueueTraverse(Q,PrintElem); 
	
	printf("------------------队列出队------------------------\n"); 
	DeQueue(Q,e);
	printf("%d\n",e);
	QueueTraverse(Q,PrintElem); 
	
	printf("------------------获取对头元素 + 判断是否为空------------------------\n"); 
	GetHead(Q,e);
	printf("%d\n",e);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
	
	printf("------------------清空队列------------------------\n"); 
	ClearQueue(Q);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
	
	printf("------------------销毁队列------------------------\n"); 
	DestoryQueue(&Q);
	if(!QueueEmpty(Q)) printf("not Empty\n");
	else printf("Empty\n");
}
