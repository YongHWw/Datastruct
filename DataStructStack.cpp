#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2

#define STACK_SIZE 100 // 栈初始向量大小 
#define STACKINCREMENT 10  //存储空间分配增量
typedef int ElemType;  
typedef int Status;  

//-------------------------------------------------------------------------------------
//栈的顺序表示 


//1.栈的类型定义 
typedef struct sqstack{
	ElemType *bottom;
	ElemType * top;
	int stacksize;
}SqStack; 
 
 //2.栈的初始化
 Status Init_Stack(SqStack &S){
 	S.bottom = (ElemType *)malloc(STACK_SIZE * sizeof(ElemType));
 	if(!S.bottom) exit (OVERFLOW);
 	S.top = S.bottom;
 	S.stacksize = STACK_SIZE;
 	return OK;
 }
 
 //3.GetTop
 Status GetTop(SqStack S,ElemType &e){
 	//若栈不空，则用e返回S的栈顶元素，并返回ok，否则error
	 if(S.top == S.bottom) return ERROR;
	 e = *(S.top - 1);
	 return OK; 
 }
 
 //4.压栈Push
 Status Push(SqStack &S,ElemType e){
 	if(S.top - S.bottom >= S.stacksize){
 		S.bottom = (ElemType *)realloc(S.bottom,(S.stacksize + STACKINCREMENT) * sizeof(ElemType));
 		if(!S.bottom) exit (OVERFLOW);
 		S.top = S.bottom + S.stacksize;
	 }
	 *S.top++ = e;
	 return OK;
 } 
 
 //5.出栈Pop
 Status Pop(SqStack &S,ElemType &e){
 	//若栈不空，删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
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
 	//清空栈 
	S.top = S.bottom;
 	
 	return OK;
 }
 
 //8.StackEmpty
 Status StackEmpty(SqStack S){
 	//判断栈是否为空
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
 	//遍历栈的每个元素,并不破坏栈的结构
	 ElemType *p = S.top;
	 while(p > S.bottom) visit(*--p);
	 return OK;
 }
 
 main(){
 	int e,len;
 	printf("------------初始化栈-------------\n");
 	SqStack S;
 	Init_Stack(S);
 	
 	printf("------------判断是否为空-------------\n"); 
 	if(StackEmpty(S))
	 	printf("空\n");
	else
		printf("不为空\n"); 
		
 	printf("------------压栈-------------\n");
 	Push(S,1);
 	Push(S,2);
 	Push(S,3);
 	Push(S,4);
 	Push(S,5);
 	
 	printf("------------出栈-------------\n");
 	Pop(S,e);
 	printf("%d\n",e);
 	
	printf("------------遍历栈 + 获取长度-------------\n");
 	StackTraverse(S,PrintElem);
 	len = StackLength(S);
 	printf("栈的长度为: %d\n",len);
 	
 	printf("------------判断是否为空-------------\n"); 
 	if(StackEmpty(S))
	 	printf("空\n");
	else
		printf("不为空\n"); 
 	
 	printf("------------清空栈-------------\n"); 
 	ClearStack(S);
	len = StackLength(S);
 	printf("栈的长度为: %d\n",len);
 	
 }
