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
	ElemType data;  //������ 
	struct LNode *next;
}LNode, *LinkList;


/* 
�����������ַ�ʽ��һ��Ϊͷ�巨������һ��Ϊβ�巨����
1. ͷ�巨��������һ���ձ�ʼ���ظ��������ݣ������½�㣬
  ���������ݴ�����½����������� 
  
2. ͷ�巨����������Ȼ�㷨�򵥣������ɵ������н��Ĵ���������˳���෴��
  ��ϣ�����ߵĴ���һ�£��ɲ���β�巨�����÷����ǽ��½����뵽��ǰ����ı�β��
  ʹ���Ϊ��ǰ�����β��㡣 
*/

//ͷ�巨����
LNode *create_LinkList_L(){
	int data;
	LNode *head, *p; 
	head = (LNode *)malloc(sizeof(LNode));
	head -> next = NULL;
	printf("������Ԫ�أ����ո�ȷ�ϣ�����32767���˳�����:\n");
	while(TRUE){
		scanf("%d",&data);
		if (data == 32767) break;  //������ֵΪ32767ʱ���˳� 
		p = (LNode *)malloc(sizeof(LNode));  //�����½�� 
		p->data = data;  //���½��������ֵ 
		p->next = head->next;
		head->next = p;
	} 
	return (head);
 } 
 
//β�巨����
LNode *create_LinkList_R(){
	int data;
	LNode *head, *p ,*r;
	head = (LNode *)malloc(sizeof(LNode));
	head -> next = NULL;
	r = head;
	printf("������Ԫ�أ����ո�ȷ�ϣ�����32767���˳�����:\n");
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
  // LΪ��ͷ���ĵ������ͷָ�롣
  // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
  LinkList p;
  p = L->next;   
  int j = 1;           // ��ʼ����pָ���һ����㣬jΪ������
  while (p && j<i) {   // ˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
    p = p->next;  ++j;
  }
  if ( !p || j>i ) return ERROR;  // ��i��Ԫ�ز�����
  e = p->data;   // ȡ��i��Ԫ��
  return OK;
} // GetElem_L


Status ListTravel(LinkList L){
	LinkList p=L->next; //����ͷ���

	printf("��ǰ����������Ԫ��:");
	while(p != NULL)
	{
		printf("%d ,",p->data);
		p=p->next;
	}
	printf("\n");
}

Status ListInsert(LinkList &L,int index,ElemType e){
	// �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
	int i = 0;
	LinkList in, p = L;  //pָ��ͷ���
	while(p && i < index - 1){  // Ѱ�� i ��ǰһ��Ԫ�� 
		p = p -> next;
		i++;
	}
	if (!p)
		return ERROR; 
	in = (LNode *)malloc(sizeof(LNode)); //�����½�� 
	in -> data = e;
	in -> next = p -> next;
	p -> next = in;
	return OK; 
}

Status ListDelete_by_index(LinkList &L,int index,ElemType &e){
	// ɾ�����Ա�L�ĵ�i��Ԫ�ز���e���� 
	int i = 0;
	LinkList p = L, q; // pָ��L��ͷ���
	
	while(p && i < index - 1){ // Ѱ�ҵ�i��Ԫ�ص�ǰһ��Ԫ��
		p = p -> next;
		i++;
	} 
	if (!p)
		return ERROR;
	// ɾ��Ԫ��
	q = p -> next;
	e = q ->data;
	p -> next = q -> next;
	free(q);  // �ͷŽ��ռ� 
	return OK;
}

Status ListDelete_by_item(LinkList &L,ElemType item){
	// ��ָ��ֵɾ����ɾ����һ��Ϊitem��ֵ
	
	LinkList p = L, q = L -> next; //pָ��ͷ��㣬qָ����һ�����
	while (q != NULL && q -> data != item){  //��ȡ��item��ͬ�Ľ�����һ�����,����pָ��ý�� 
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
	// ɾ���������У�����ֵΪitem�Ľ��
	LinkList p = L, q = L -> next;
	while (q != NULL){
		if (q -> data == item){  // ɾ����� 
			p -> next = q -> next;
			free(q);
			q =  p -> next;
		}
		else{ // �����ȣ�ָ����һ��� 
			p = q;
			q = q -> next;
		}
	} 
}

int main(){
	int e;
	LinkList L = create_LinkList_L(); //��ͷ��㣬��ͷ�巨���� 
	ListTravel(L);
	
	printf("==========��ȡ��i��Ԫ��=========\n");
	GetElem(L,2,e);
	printf("%d\n",e);
	
	printf("==========ListInsert=========\n");
	int flag;
	flag = ListInsert(L,6,10);
	if (flag) ListTravel(L); else printf("û�и�λ��\n"); 

	printf("==========ListDelete_by_index=========\n");
	flag = ListDelete_by_index(L,6,e);
	if (flag){
		printf("ɾ��Ԫ��Ϊ��%d\n",e);
		ListTravel(L);		
	}
	else printf("û�и�λ��\n");

	printf("==========ListDelete_by_item=========\n");
	int del = 4;
	flag = ListDelete_by_item(L,del);
	if (flag){
		printf("ɾ��Ԫ��Ϊ%d\n",del);
		ListTravel(L);
	}
	else printf("�����ڸ�ֵ���ڵĽ��\n");
		
	printf("==========ListDeleteAll_by_item=========\n");
	ListDeleteAll_by_item(L,3);
	ListTravel(L);
	
}
