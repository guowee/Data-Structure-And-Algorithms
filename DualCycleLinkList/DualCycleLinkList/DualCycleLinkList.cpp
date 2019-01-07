#include "Header.h"

Status InitList_DuL(DuLinkList * L)
{
	*L = (DuLinkList)malloc(sizeof(DuLinkList));
	if (!(*L))
	{
		exit(OVERFLOW);
	}

	(*L)->next = (*L)->prior = *L;

	return OK;
}

Status ClearList_DuL(DuLinkList L)
{
	DuLinkList p, q;
	p = L->next;
	while (p != L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = L->prior = L;
	return OK;
}

Status DestroyList_DuL(DuLinkList * L)
{
	DuLinkList q, p = (*L)->next;
	while (p != *L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(*L);
	*L = NULL;
	return OK;
}

Status ListEmpty_DuL(DuLinkList L)
{
	if (L && L->next == L && L->prior == L) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int ListLength_DuL(DuLinkList L)
{
	DuLinkList p;
	int count;
	if (L) {
		count = 0;
		p = L;
		while (p->next != L)
		{
			count++;
			p = p->next;
		}
	}
	return count;
}

Status GetElem_DuL(DuLinkList L, int index, LElemType_DC * e)
{
	DuLinkList p;
	int count;
	if (L) {
		count = 1;
		p = L->next;
		while (p != L && count < index)
		{
			count++;
			p = p->next;
		}

		if (p != L) {
			*e = p->data;
			return OK;
		}
	}
	return ERROR;
}

int LocateElem_DuL(DuLinkList L, LElemType_DC e, Status(Compare)(LElemType_DC, LElemType_DC))
{
	DuLinkList p;
	int count;
	if (L) {
		count = 1;
		p = L->next;
		while (p != L && !Compare(e, p->data))
		{
			count++;
			p = p->next;
		}
		if (p != L) {
			return count;
		}
	}
	return 0;
}

Status PriorElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC * pre_e)
{
	DuLinkList p;
	if (L) {
		p = L->next;

		while (p != L && p->data != cur_e)
		{
			p = p->next;
		}
		if (p != L && p->prior != L) {
			*pre_e = p->prior->data;
			return OK;
		}
	}
	return ERROR;
}

Status NextElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC * next_e)
{
	DuLinkList p;
	if (L) {
		p = L->next;
		while (p != L && p->data != cur_e)
		{
			p = p->next;
		}
		if (p != L && p->next != L) {
			*next_e = p->next->data;
			return OK;
		}
	}

	return ERROR;
}

DuLinkList GetElemPtr_DuL(DuLinkList L, int index)
{
	int count;
	DuLinkList p;
	if (L && index > 0) {
		count = 1;
		p = L->next;

		while (p != L && count < index)
		{
			count++;
			p = p->next;
		}
		if (p != L) {
			return p;
		}

	}
	return NULL;
}

Status ListInsert_DuL(DuLinkList L, int index, LElemType_DC e)
{
	DuLinkList p, s;

	if (index<1 || index>ListLength_DuL(L) + 1) {
		return ERROR;
	}

	p = GetElemPtr_DuL(L, index);
	if (!p) {
		p = L;
	}

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (!s) {
		exit(OVERFLOW);
	}

	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

Status ListDelete_DuL(DuLinkList L, int index, LElemType_DC * e)
{
	DuLinkList p;
	if (!(p = GetElemPtr_DuL(L, index))) {
		return ERROR;
	}

	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;

	free(p);
	p = NULL;

	return OK;
}

void ListTraverse_DuL(DuLinkList L, void(Visit)(LElemType_DC))
{
	DuLinkList p;
	p = L->next;
	while (p != L) {
		Visit(p->data);
		p = p->next;
	}
}
