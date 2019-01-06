#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include "Status.h"
#include "Scanf.h"
#define MAXSIZE 1000

typedef int LElemType_S;
typedef int SLinkList;

typedef struct 
{
	LElemType_S data;
	int cur;
}Component[MAXSIZE];

Component SPACE;

void InitSpace_SL();

int Malloc_SL();

void Free_SL(int k);

int InitList_SL(SLinkList *H);

Status ClearList_SL(SLinkList H);

void DestroyList_SL(SLinkList *H);

Status ListEmpty_SL(SLinkList H);

int ListLength_SL(SLinkList H);

Status GetElem_SL(SLinkList H,int i, LElemType_S *e);

int LocateElem_SL(SLinkList H,LElemType_S e);

Status PriorElem_SL(SLinkList H,LElemType_S cur_e,LElemType_S *pre_e);

Status NextElem_SL(SLinkList H, LElemType_S cur_e,LElemType_S *next_e);

Status ListInsert_SL(SLinkList H, int i, LElemType_S e);

Status ListDelete_SL(SLinkList H, int i, LElemType_S *e);

Status ListTraverse_SL(SLinkList H,void(Visit)(LElemType_S));

void difference(SLinkList *S,LElemType_S A[],int len_A,LElemType_S B[],int len_B);

#endif