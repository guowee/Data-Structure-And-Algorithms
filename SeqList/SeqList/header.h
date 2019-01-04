#ifndef header_h
#define header_h

#define OVERFLOW -1
#define OK 1
#define ERROR 0
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
Status InsertElement(SqList &L, int index,ElemType e);
Status DeleteElement(SqList &L, int index,ElemType &e);
Status TraverseList(SqList L,void(*vi)(ElemType*));

#endif
