#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
typedef int Status;  

#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10 //���Ա�洢�ռ�ķ������� 

typedef struct{
	int *elem;
	int length;
	int listsize;
}SqList; 

Status InitList_Sq(SqList &L) { 
  // ����һ���յ����Ա�L��
  L.elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if (!L.elem) 
  	return OK;        // �洢����ʧ��
  	
  L.length = 0;                  // �ձ���Ϊ0
  L.listsize = LIST_INIT_SIZE;   // ��ʼ�洢����
  return OK;
} // InitList_Sq

Status ListInsert_Sq(SqList &L, int i, int e) {  // �㷨2.4
  // ��˳�����Ա�L�ĵ�i��Ԫ��֮ǰ�����µ�Ԫ��e��
  // i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)+1
  int *p;
  if (i < 1 || i > L.length+1) 
  	return ERROR;  // iֵ���Ϸ�
  	
  if (L.length >= L.listsize) 
  {   // ��ǰ�洢�ռ���������������
    int *newbase = (int *)realloc(L.elem,
                  (L.listsize+LISTINCREMENT)*sizeof (int));
    if (!newbase) 
		return ERROR;   		  // �洢����ʧ��
    L.elem = newbase;             // �»�ַ
    L.listsize += LISTINCREMENT;  // ���Ӵ洢����
  }
  int *q = &(L.elem[i-1]);   // qΪ����λ��
  for (p = &(L.elem[L.length-1]); p>=q; --p) 
  	*(p+1) = *p; // ����λ�ü�֮���Ԫ������
  	
  *q = e;       // ����e
  ++L.length;   // ����1
  return OK;
} // ListInsert_Sq

Status Delete_SqList(SqList &L,int i,int &e)
{
	//ɾ�����Ա�L�ĵ�i��Ԫ�ز���e���� 
	int *p,*q;
	if(i<1||i>L.length)
		return ERROR;
	p = &(L.elem[i-1]);
	e = *p;
	q = &(L.elem[L.length-1]);  //��βԪ�ص�λ�� 
	for(++p;p<=q;++p)
		*(p-1) = *p;  //��ɾ��Ԫ��֮���Ԫ������ 
	--L.length;  //����1 
	return OK;
} //Delete_SqList 

int Compare_Sq(int p,int e)
{
	if(p==e)
		return TRUE;
	else
		return FALSE;
} 

Status LocateElem_Sq(SqList L, int e,Status (*compare)(int, int)) 
{ // ��˳�����Ա�L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ��
  // ���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0��
  int i;
  int *p;
  i = 1;        // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
  p = L.elem;   // p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
  while (i <= L.length && !(*compare)(*p++, e)) 
    ++i;
  if (i <= L.length) 
  	return i;
  else 
  	return FALSE;
} // LocateElem_Sq


//Status GetElem(SqList L,int i,int *e)
//{
//    if(L.length==0 || i<1 || i>L.length)
//            return ERROR;
//    e=L.elem[i-1];
// 
//    return OK;


int main()
{
	int i,e;
	SqList L;
	Status j = InitList_Sq(L);
	if(j = 1)
	{
			printf("L��ʼ���ɹ�������Ϊ��%d\n",L.length);
	}
	
	printf("==========����Ԫ��=========\n");
	//����Ԫ�� 
	for(i = 1;i < 5;i++)
	{
		j = ListInsert_Sq(L,i,i);
	}
	
	for(i = 0;i<L.length;i++)
	{
			printf("�����Ԫ��Ϊ��%d\n",L.elem[i]);
	}
	
	printf("������ɣ�����Ϊ��%d\n",L.length);
	
	printf("==========ɾ��Ԫ��=========\n");
	
	j = Delete_SqList(L,2,e);
	if(j == 1)
		printf("ɾ���ɹ���ɾ��ֵΪ��%d\n",e);
	
	for(i = 0;i<L.length;i++)
	{
			printf("ɾ��Ԫ�غ��Ϊ��%d\n",L.elem[i]);
	}
	
	printf("==========����Ԫ��λ��=========\n");
	
	int locate_test;
	locate_test = LocateElem_Sq(L,4,Compare_Sq);
	if(locate_test != 0)
		printf("�ҵ�Ԫ���ˣ�λ���ڣ�%d\n",locate_test);
	else
		printf("�Ҳ���Ԫ�أ�\n");
}





