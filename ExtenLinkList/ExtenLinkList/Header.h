#ifndef HEADER_H
#define HEADER_H
#include <stdlib.h>
#include "Status.h"
#include "Scanf.h"

typedef int LElemType_E;

typedef struct ELNode {
	LElemType_E data;
	struct ELNode *next;
}ELNode;

typedef ELNode* Link;
typedef ELNode* Position;


typedef struct {
	Link head, tail;
	int len;
}ELinkList;

Status MakeNode_E(Link *p,LElemType_E e);

void FreeNode_E(Link *p);

Status InitList_E(ELinkList *L);

Status ListEmpty_E(ELinkList L);

void ClearList_E(ELinkList *L);

void DestroyList_E(ELinkList *L);

int ListLength_E(ELinkList L);

void InsFirst_E(ELinkList *L,Link h,Link s);

Status DelFirst_E(ELinkList *L,Link h,Link *q);

void Append_E(ELinkList *L, Link s);

Status Remove_E(ELinkList *L,Link *q);

void InsBefore(ELinkList *L,Link *p,Link s);

void InsAfter(ELinkList *L,Link *p,Link s);

void SetCurElem_E(Link p,LElemType_E e);

LElemType_E GetCurElem_E(Link p);

Position GetHead_E(ELinkList L);

Position GetLast_E(ELinkList L);

Position PriorPos_E(ELinkList L,Link p);

Position NextPos_E(Link p);

Status LocatePos_E(ELinkList L,int index,Link *p);

Position LocateElem_E(ELinkList L,LElemType_E e, Status(Compare)(LElemType_E, LElemType_E));

Status ListTraverse_E(ELinkList L,void(Visit)(LElemType_E));

Status ListInsert_L_E(ELinkList *L,int index,LElemType_E e);

Status ListDelete_L_E(ELinkList *L,int index,LElemType_E *e);

#endif // !HEADER_H
