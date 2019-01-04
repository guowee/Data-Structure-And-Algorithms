#ifndef header_h
#define header_h

#define OVERFLOW -1
#define OK 1
#define ERROR 0
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
Status InsertElement(SqList &L, int index,ElemType e);
Status DeleteElement(SqList &L, int index,ElemType &e);
Status TraverseList(SqList L,void(*vi)(ElemType*));

#endif
