#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2

#define STACK_SIZE 100 // ջ��ʼ������С 
#define STACKINCREMENT 10  //�洢�ռ��������
typedef int ElemType;  
typedef int Status;  

//-------------------------------------------------------------------------------------
//ջ��˳���ʾ 


//1.ջ�����Ͷ��� 
typedef struct sqstack{
	ElemType *bottom;
	ElemType * top;
	int stacksize;
}SqStack; 
 
 //2.ջ�ĳ�ʼ��
 Status Init_Stack(SqStack &S){
 	S.bottom = (ElemType *)malloc(STACK_SIZE * sizeof(ElemType));
 	if(!S.bottom) exit (OVERFLOW);
 	S.top = S.bottom;
 	S.stacksize = STACK_SIZE;
 	return OK;
 }
 
 //3.GetTop
 Status GetTop(SqStack S,ElemType &e){
 	//��ջ���գ�����e����S��ջ��Ԫ�أ�������ok������error
	 if(S.top == S.bottom) return ERROR;
	 e = *(S.top - 1);
	 return OK; 
 }
 
 //4.ѹջPush
 Status Push(SqStack &S,ElemType e){
 	if(S.top - S.bottom >= S.stacksize){
 		S.bottom = (ElemType *)realloc(S.bottom,(S.stacksize + STACKINCREMENT) * sizeof(ElemType));
 		if(!S.bottom) exit (OVERFLOW);
 		S.top = S.bottom + S.stacksize;
	 }
	 *S.top++ = e;
	 return OK;
 } 
 
 //5.��ջPop
 Status Pop(SqStack &S,ElemType &e){
 	//��ջ���գ�ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	 if(S.top == S.bottom) return ERROR;
	 e = * --S.top;
	 return OK; 
 } 
 
 //6.DestoryStack
 Status DestoryStack(SqStack &S){
 	free(S.bottom);
 	S.bottom = NULL;
 	S.top = NULL;
 	S.stacksize = 0;
 	
 	return OK;
 } 
 
 //7.ClearStack
 Status ClearStack(SqStack &S){
 	//���ջ 
	S.top = S.bottom;
 	
 	return OK;
 }
 
 //8.StackEmpty
 Status StackEmpty(SqStack S){
 	//�ж�ջ�Ƿ�Ϊ��
	if(S.bottom == S.top) 
		return TRUE;
	else 
		return FALSE;
 }
 
 //9.StackLength
 Status StackLength(SqStack S){
 	return S.top - S.bottom;
 }
 
 
 
 
int PrintElem(ElemType e){
 	printf("  %d  |\n",e);
 	printf("-----\n");
 }
 
 Status StackTraverse(SqStack S, Status(visit)(ElemType)){
 	//����ջ��ÿ��Ԫ��,�����ƻ�ջ�Ľṹ
	 ElemType *p = S.top;
	 while(p > S.bottom) visit(*--p);
	 return OK;
 }
 
 main(){
 	int e,len;
 	printf("------------��ʼ��ջ-------------\n");
 	SqStack S;
 	Init_Stack(S);
 	
 	printf("------------�ж��Ƿ�Ϊ��-------------\n"); 
 	if(StackEmpty(S))
	 	printf("��\n");
	else
		printf("��Ϊ��\n"); 
		
 	printf("------------ѹջ-------------\n");
 	Push(S,1);
 	Push(S,2);
 	Push(S,3);
 	Push(S,4);
 	Push(S,5);
 	
 	printf("------------��ջ-------------\n");
 	Pop(S,e);
 	printf("%d\n",e);
 	
	printf("------------����ջ + ��ȡ����-------------\n");
 	StackTraverse(S,PrintElem);
 	len = StackLength(S);
 	printf("ջ�ĳ���Ϊ: %d\n",len);
 	
 	printf("------------�ж��Ƿ�Ϊ��-------------\n"); 
 	if(StackEmpty(S))
	 	printf("��\n");
	else
		printf("��Ϊ��\n"); 
 	
 	printf("------------���ջ-------------\n"); 
 	ClearStack(S);
	len = StackLength(S);
 	printf("ջ�ĳ���Ϊ: %d\n",len);
 	
 }
