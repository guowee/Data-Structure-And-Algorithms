#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Status InitList(LinkList &L) {
  L = (LinkList)malloc(sizeof(LNode));
  if (!L) {
	  return ERROR;
  }
  L->next = NULL;
  return OK;
}

Status ListEmpty(LinkList L)
{
	if (L->next) {
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

Status ClearList(LinkList & L)
{
	LinkList p, q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}

Status ListTraverse(LinkList L, void(*vi)(ElemType))
{
	LinkList s = L->next;
	while (s)
	{
		vi(s->data);
		s = s->next;
	}
	return OK;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetElem(LinkList L, int index, ElemType & e)
{
	if (!L || index < 1) 
	{
		return ERROR;
	}

	LinkList p = L->next;
	int j = 1;
	while (p && j<index) {
		p = p->next;
		++j;
	}
	if (!p || j > index) { return ERROR; }
	e = p->data;
	return OK;
}

Status CreateListHead(LinkList & L, int n)
{
	if (!L || n<1|| n>MAXSIZE) {
		return ERROR;
	}
	LinkList p;
	int i;
	srand(time(NULL));
	for ( i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p->data = rand() % 100 + 1;
		p->next =L->next;
		L->next = p;
	}
	
	return OK;
}

Status CreateListTail(LinkList &L, int n) {
	if (!L  || n <1 || n> MAXSIZE) {
		return ERROR;
	}
	LinkList p, q;
	int i;
	srand(time(0));

	q = L;
	for ( i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		p->data = rand() % 100 + 1;
		q->next = p;
		q = p;
	}
	q->next = NULL;
	return OK;
}

int LocateElem(LinkList L, ElemType e)
{
	if (ListEmpty(L))
	{
		return ERROR;
	}
	int loc = 1;
	LinkList p = L->next;
	while (p) {
	    if(e==p->data){
		   return loc;
	    }
		p = p->next;
		loc++;
	}
	return ERROR;
}

Status ListInsert(LinkList & L, int index, ElemType e)
{
	if (!L || index<1 || index>MAXSIZE) { return ERROR; }

	int j = 1;
	LinkList p, q;
	p = L;
	while (p && j < index)
	{
		p = p->next;
		j++;
	}
	if (!p || j > index) { return ERROR; }

	LinkList s;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete(LinkList & L, int index, ElemType & e)
{
	if(!L || index < 1 || index >MAXSIZE) {
		return ERROR;
	}

	int j = 1;
	LinkList p; 
	p = L;
	while (p && j<index) {
		p = p->next;
		j++;
	}
	if (!(p->next) || j > index) { return ERROR; }
	LinkList q = p->next;
	e = q->data;
	p->next = q->next;
	free(q);
	return OK;
}

Status ListReverse(LinkList & L)
{
	if (ListEmpty(L) || !L) {
		return ERROR;
	}
	LinkList p, q, r;
	p = L->next;
	q = p->next;
	p->next = NULL;
	while (q)
	{ 
		r = q->next;
		q -> next = p;
		p = q;
		q = r;
	}
	L->next = p;
	return OK;
}

void MergeList(LinkList & La, LinkList & Lb, LinkList & Lc)
{
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;
	while (pa && pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb);
}
