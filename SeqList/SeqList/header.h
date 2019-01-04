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
 *���Ա��˳���ʾָ������һ���ַ�����Ĵ洢��Ԫ���δ洢���Ա������Ԫ��
*/
typedef struct 
{
	ElemType *elem; //�洢�ռ����ַ
	int length;//��ǰ����
	int listsize;//��ǰ����洢�ռ�
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
