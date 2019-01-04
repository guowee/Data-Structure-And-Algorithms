#ifndef header_h
#define header_h

#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define INFEASIBLE -2
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
/*
 *线性表的顺序表示指的是用一组地址连续的存储单元依次存储线性表的数据元素
*/
typedef struct 
{
	ElemType *elem; //存储空间基地址
	int length;//当前长度
	int listsize;//当前分配存储空间
}SqList;

Status InitList(SqList &L);
Status DestoryList(SqList &L);
Status ClearList(SqList &L);
Status ListEmpty(SqList L);
int ListLength(SqList L);
Status GetElem(SqList L, int index, ElemType &e);
int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e);
Status NextElem(SqList L, ElemType cur_e, ElemType &next_e);
Status ListInsert(SqList &L, int index,ElemType e);
Status ListDelete(SqList &L, int index,ElemType &e);
Status ListTraverse(SqList L,void(*vi)(ElemType*));
#endif
