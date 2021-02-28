#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
typedef char ElemType;  
typedef int Status;  

typedef struct BiTNode{
	ElemType data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

Status InitBiTree(BiTree &T){
	T = (BiTree)malloc(sizeof(BiTree));
	T -> lchild = NULL;
	T -> rchild = NULL;
	T -> data = NULL;
	return OK;
}

Status Travel(BiTree b){
	BiTree St[100],p;
	int flag,top = -1;
	if(b!= NULL){
		do{
			while(b!=NULL){
				St[++top] = b;
				b = b->lchild;
			}
			p = NULL;
			flag = 1;
			while(top != -1 && flag){
				printf("------%d\n",top); 
				b = St[top];
				if(b -> rchild == p){
					printf("-------------------%c\n",b->data);
					top--;
					p = b;
				}
				else{
					b = b -> rchild;
					flag = 0;
				}
				if(p!=NULL) printf("----%c\n",p->data);
			}
		}while(top!=-1);
	}
}

main(){
	int flag;
	BiTree T,T2,T3,T4,T5,T6,T7,T8,T9;
	flag = InitBiTree(T);
	InitBiTree(T2);
	InitBiTree(T3);
	InitBiTree(T4);
	InitBiTree(T5);
	InitBiTree(T6);
	InitBiTree(T7);
	InitBiTree(T8);
	InitBiTree(T9);
	if (flag) printf("初始化成功\n");
	else printf("初始化失败\n"); 
	
	//构造二叉树
	T -> data = 'A';
	T2 -> data = 'B';
	T3 -> data = 'C';
	T4 -> data = 'D';
	T5 -> data = 'E';
	T6 -> data = 'F';
	T7 -> data = 'G';
	T8 -> data = 'H';
	
	T->lchild = T2;
	T->rchild = T3;
	T2->lchild = T4;
	T2->rchild = T5;
	T3->rchild = T6;
	T4->lchild = T7;
	T6->lchild = T8;
	
	
	Travel(T);	
//	printf("%c\n",T -> data);
//	printf("%c\n",T -> lchild -> data);
}

