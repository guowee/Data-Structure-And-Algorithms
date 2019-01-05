#ifndef header_h
#define header_h

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int ElemType;
typedef int Status;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;


Status InitList(LinkList &L);
Status ListEmpty(LinkList L);
Status ClearList(LinkList &L);
Status ListTraverse(LinkList L, void(*vi)(ElemType));
int ListLength(LinkList L);
Status GetElem(LinkList L, int index, ElemType &e);
Status CreateListHead(LinkList &L, int n);
Status CreateListTail(LinkList &L, int n);
int LocateElem(LinkList L,ElemType e);
Status ListInsert(LinkList &L,int index,ElemType e);
Status ListDelete(LinkList &L, int index,ElemType &e);
Status ListReverse(LinkList &L);
void MergeList(LinkList &La,LinkList &Lb,LinkList &Lc);
#endif
