#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
typedef int Status;  

#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10 //线性表存储空间的分配增量 

typedef struct{
	int *elem;
	int length;
	int listsize;
}SqList; 

Status InitList_Sq(SqList &L) { 
  // 构造一个空的线性表L。
  L.elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
  if (!L.elem) 
  	return OK;        // 存储分配失败
  	
  L.length = 0;                  // 空表长度为0
  L.listsize = LIST_INIT_SIZE;   // 初始存储容量
  return OK;
} // InitList_Sq

Status ListInsert_Sq(SqList &L, int i, int e) {  // 算法2.4
  // 在顺序线性表L的第i个元素之前插入新的元素e，
  // i的合法值为1≤i≤ListLength_Sq(L)+1
  int *p;
  if (i < 1 || i > L.length+1) 
  	return ERROR;  // i值不合法
  	
  if (L.length >= L.listsize) 
  {   // 当前存储空间已满，增加容量
    int *newbase = (int *)realloc(L.elem,
                  (L.listsize+LISTINCREMENT)*sizeof (int));
    if (!newbase) 
		return ERROR;   		  // 存储分配失败
    L.elem = newbase;             // 新基址
    L.listsize += LISTINCREMENT;  // 增加存储容量
  }
  int *q = &(L.elem[i-1]);   // q为插入位置
  for (p = &(L.elem[L.length-1]); p>=q; --p) 
  	*(p+1) = *p; // 插入位置及之后的元素右移
  	
  *q = e;       // 插入e
  ++L.length;   // 表长增1
  return OK;
} // ListInsert_Sq

Status Delete_SqList(SqList &L,int i,int &e)
{
	//删除线性表L的第i个元素并用e返回 
	int *p,*q;
	if(i<1||i>L.length)
		return ERROR;
	p = &(L.elem[i-1]);
	e = *p;
	q = &(L.elem[L.length-1]);  //表尾元素的位置 
	for(++p;p<=q;++p)
		*(p-1) = *p;  //被删除元素之后的元素左移 
	--L.length;  //表长减1 
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
{ // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序。
  // 若找到，则返回其在L中的位序，否则返回0。
  int i;
  int *p;
  i = 1;        // i的初值为第1个元素的位序
  p = L.elem;   // p的初值为第1个元素的存储位置
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
			printf("L初始化成功，长度为：%d\n",L.length);
	}
	
	printf("==========插入元素=========\n");
	//插入元素 
	for(i = 1;i < 5;i++)
	{
		j = ListInsert_Sq(L,i,i);
	}
	
	for(i = 0;i<L.length;i++)
	{
			printf("插入后元素为：%d\n",L.elem[i]);
	}
	
	printf("插入完成，长度为：%d\n",L.length);
	
	printf("==========删除元素=========\n");
	
	j = Delete_SqList(L,2,e);
	if(j == 1)
		printf("删除成功，删除值为：%d\n",e);
	
	for(i = 0;i<L.length;i++)
	{
			printf("删除元素后表为：%d\n",L.elem[i]);
	}
	
	printf("==========查找元素位置=========\n");
	
	int locate_test;
	locate_test = LocateElem_Sq(L,4,Compare_Sq);
	if(locate_test != 0)
		printf("找到元素了，位置在：%d\n",locate_test);
	else
		printf("找不到元素！\n");
}





