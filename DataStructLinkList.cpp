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

typedef struct LNode{ 
	ElemType data;  //数据域 
	struct LNode *next;
}LNode, *LinkList;


/* 
链表创建有两种方式，一种为头插法创建，一种为尾插法创建
1. 头插法创建：从一个空表开始，重复读入数据，生成新结点，
  将读入数据存放入新结点的数据域中 
  
2. 头插法建立链表虽然算法简单，但生成的链表中结点的次序和输入的顺序相反，
  若希望二者的次序一致，可采用尾插法建表。该方法是将新结点插入到当前链表的表尾，
  使其成为当前链表的尾结点。 
*/

//头插法建表
LNode *create_LinkList_L(){
	int data;
	LNode *head, *p; 
	head = (LNode *)malloc(sizeof(LNode));
	head -> next = NULL;
	printf("请输入元素，按空格确认，输入32767则退出输入:\n");
	while(TRUE){
		scanf("%d",&data);
		if (data == 32767) break;  //当输入值为32767时，退出 
		p = (LNode *)malloc(sizeof(LNode));  //创建新结点 
		p->data = data;  //给新结点数据域赋值 
		p->next = head->next;
		head->next = p;
	} 
	return (head);
 } 
 
//尾插法建表
LNode *create_LinkList_R(){
	int data;
	LNode *head, *p ,*r;
	head = (LNode *)malloc(sizeof(LNode));
	head -> next = NULL;
	r = head;
	printf("请输入元素，按空格确认，输入32767则退出输入:\n");
	while(TRUE){
		scanf("%d",&data);
		if (data == 32767) break;
		p = (LNode *)malloc(sizeof(LNode));
		p -> data = data;
		
		p -> next = r -> next;
		r -> next = p;
		r = p;
	}
	return (head);
}



Status GetElem(LinkList &L,int i, ElemType &e) {
  // L为带头结点的单链表的头指针。
  // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
  LinkList p;
  p = L->next;   
  int j = 1;           // 初始化，p指向第一个结点，j为计数器
  while (p && j<i) {   // 顺指针向后查找，直到p指向第i个元素或p为空
    p = p->next;  ++j;
  }
  if ( !p || j>i ) return ERROR;  // 第i个元素不存在
  e = p->data;   // 取第i个元素
  return OK;
} // GetElem_L


Status ListTravel(LinkList L){
	LinkList p=L->next; //跳过头结点

	printf("当前单链表所有元素:");
	while(p != NULL)
	{
		printf("%d ,",p->data);
		p=p->next;
	}
	printf("\n");
}

Status ListInsert(LinkList &L,int index,ElemType e){
	// 在带头结点的单链线性表L的第i个元素之前插入元素e
	int i = 0;
	LinkList in, p = L;  //p指向头结点
	while(p && i < index - 1){  // 寻找 i 的前一个元素 
		p = p -> next;
		i++;
	}
	if (!p)
		return ERROR; 
	in = (LNode *)malloc(sizeof(LNode)); //生成新结点 
	in -> data = e;
	in -> next = p -> next;
	p -> next = in;
	return OK; 
}

Status ListDelete_by_index(LinkList &L,int index,ElemType &e){
	// 删除线性表L的第i个元素并用e返回 
	int i = 0;
	LinkList p = L, q; // p指向L的头结点
	
	while(p && i < index - 1){ // 寻找第i个元素的前一个元素
		p = p -> next;
		i++;
	} 
	if (!p)
		return ERROR;
	// 删除元素
	q = p -> next;
	e = q ->data;
	p -> next = q -> next;
	free(q);  // 释放结点空间 
	return OK;
}

Status ListDelete_by_item(LinkList &L,ElemType item){
	// 按指定值删除，删除第一个为item的值
	
	LinkList p = L, q = L -> next; //p指向头结点，q指向下一个结点
	while (q != NULL && q -> data != item){  //获取与item相同的结点的上一个结点,并用p指向该结点 
		p = q;
		q = q -> next;
	} 
	if (!q)
		return ERROR;
	else if(q -> data == item){
		p -> next = q -> next;
		free(q);
		return OK;
	}
}

Status ListDeleteAll_by_item(LinkList &L,ElemType item){
	// 删除单链表中，所有值为item的结点
	LinkList p = L, q = L -> next;
	while (q != NULL){
		if (q -> data == item){  // 删除结点 
			p -> next = q -> next;
			free(q);
			q =  p -> next;
		}
		else{ // 若不等，指向下一结点 
			p = q;
			q = q -> next;
		}
	} 
}

int main(){
	int e;
	LinkList L = create_LinkList_L(); //以头结点，用头插法建表 
	ListTravel(L);
	
	printf("==========获取第i个元素=========\n");
	GetElem(L,2,e);
	printf("%d\n",e);
	
	printf("==========ListInsert=========\n");
	int flag;
	flag = ListInsert(L,6,10);
	if (flag) ListTravel(L); else printf("没有该位置\n"); 

	printf("==========ListDelete_by_index=========\n");
	flag = ListDelete_by_index(L,6,e);
	if (flag){
		printf("删除元素为：%d\n",e);
		ListTravel(L);		
	}
	else printf("没有该位置\n");

	printf("==========ListDelete_by_item=========\n");
	int del = 4;
	flag = ListDelete_by_item(L,del);
	if (flag){
		printf("删除元素为%d\n",del);
		ListTravel(L);
	}
	else printf("不存在该值所在的结点\n");
		
	printf("==========ListDeleteAll_by_item=========\n");
	ListDeleteAll_by_item(L,3);
	ListTravel(L);
	
}
