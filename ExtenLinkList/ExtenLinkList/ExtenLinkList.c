#include "Header.h"

Status MakeNode_E(Link * p, LElemType_E e)
{
	*p = (Link)malloc(sizeof(ELNode));
	if (!(*p)) {
		exit(OVERFLOW);
	}
	(*p)->data = e;
	(*p)->next = NULL;
	return OK;
}

void FreeNode_E(Link * p)
{
	free(*p);
	*p = NULL;
}

Status InitList_E(ELinkList * L)
{
	Link p;
	p = (Link)malloc(sizeof(ELNode));

	if (!p) {
		exit(OVERFLOW);
	}
	p->next = NULL;
	(*L).head = (*L).tail = p;
	(*L).len = 0;
	return OK;
}

Status ListEmpty_E(ELinkList L)
{
	if(L.len){
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void ClearList_E(ELinkList * L)
{
	Link p, q;

	p = (*L).head->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	(*L).head->next = NULL;
	(*L).tail = (*L).head;
	(*L).len = 0;
}

void DestroyList_E(ELinkList * L)
{
	ClearList_E(L);
	free((*L).head);
	(*L).head = (*L).tail = NULL;
}

int ListLength_E(ELinkList L)
{
	return L.len;
}

void InsFirst_E(ELinkList * L, Link h, Link s)
{
	s->next = h->next;
	h->next = s;
	if (h == (*L).tail) {
		(*L).tail=h->next;
	}
	(*L).len++;
}

Status DelFirst_E(ELinkList * L, Link h, Link * q)
{

	*q = h->next;
	if (*q) {
		h->next =(*q)->next;
		if (!h->next) {
			(*L).tail = h;
		}
		(*L).len--;
		return OK;
	}

	return ERROR;
}

void Append_E(ELinkList * L, Link s)
{
	int count = 0;
	(*L).tail->next = s;
	while (s) {
		(*L).tail = s;
		s = s->next;
		count++;
	}
	(*L).len += count;
}

Status Remove_E(ELinkList * L, Link * q)
{
	Link p;
	if (!(*L).len) {
		*q = NULL;
		return ERROR;
	}

	*q = (*L).tail;
	p = (*L).head;
	while (p->next != (*L).tail) {
		p = p->next;
	}
	p->next = NULL;
	(*L).tail = p;
	(*L).len--;
	return OK;
}

void InsBefore(ELinkList * L, Link * p, Link s)
{
	Link q;

	q = PriorPos_E(*L,*p);

	if (!q) {
		q = (*L).head;
	}

	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++;
}

void InsAfter(ELinkList * L, Link * p, Link s)
{
	if (*p ==(*L).tail) {
		(*L).tail = s;
	}

	s->next = (*p)->next;
	(*p)->next = s;
	*p = s;
	(*L).len++;
}

void SetCurElem_E(Link p, LElemType_E e)
{
	p->data = e;
}

LElemType_E GetCurElem_E(Link p)
{
	return p->data;
}

Position GetHead_E(ELinkList L)
{
	return L.head;
}

Position GetLast_E(ELinkList L)
{
	return L.tail;
}

Position PriorPos_E(ELinkList L, Link p)
{
	Link q;
	q = L.head->next;
	if (q == p ) {
		return NULL;
	}
	else
	{
		while (q->next != p)
		{
			q = q->next;
		}
		return q;
	}
}

Position NextPos_E(Link p)
{
	return p->next;
}

Status LocatePos_E(ELinkList L, int index, Link * p)
{
	int count = 0;
	*p = L.head;

	if (index <0 || index>L.len) {
		return ERROR;
	}

	while (count <index )
	{
		count++;
		*p = (*p)->next;
	}
	return OK;
}

Position LocateElem_E(ELinkList L, LElemType_E e, Status(Compare)(LElemType_E, LElemType_E))
{
	Link p = L.head->next;
	while (p && !(Compare(e,p->data)))
	{
		p = p->next;
	}
	return p;
}

Status ListTraverse_E(ELinkList L, void(Visit)(LElemType_E))
{
	Link p;
	int j;
	p = L.head->next;
	for ( j = 1; j <=L.len; j++)
	{
		Visit(p->data);
		p = p->next;
	}

	return OK;
}

Status ListInsert_L_E(ELinkList * L, int index, LElemType_E e)
{
	Link h, s;
	if (!LocatePos_E(*L,index-1,&h)) {
		return ERROR;
	}
	if (!MakeNode_E(&s,e)) {
		return ERROR;
	}

	InsFirst_E(L,h,s);

	return OK;
}

Status ListDelete_L_E(ELinkList * L, int index, LElemType_E * e)
{
	Link p, q;
	if (index < 1 || index >(*L).len) {
		return ERROR;
	}
	LocatePos_E(*L,index -1,&p);
	DelFirst_E(L,p,&q);
	*e = q->data;
	free(q);
	q = NULL;
	return OK;
}

Status MergeEList_L(ELinkList La, ELinkList Lb, ELinkList * Lc, int(Compare)(LElemType_E, LElemType_E))
{
	Link ha, hb, pa, pb, q;
	LElemType_E c1, c2;
	if (!InitList_E(Lc)) {
		return ERROR;
	}
	ha = GetHead_E(La); 				//ha指向La头结点
	hb = GetHead_E(Lb); 				//hb指向Lb头结点
	pa = NextPos_E(ha);					//pa指向La第一个结点 
	pb = NextPos_E(hb);					//pb指向Lb第一个结点
	while (!ListEmpty_E(La) && !ListEmpty_E(Lb))
	{									//La与Lb非空 
		c1 = GetCurElem_E(pa);			//c1、c2为当前比较的元素
		c2 = GetCurElem_E(pb);
		if (Compare(c1, c2) <= 0)
		{
			DelFirst_E(&La, ha, &q);
			InsFirst_E(Lc, (*Lc).tail, q);
			pa = NextPos_E(ha);
		}
		else
		{
			DelFirst_E(&Lb, hb, &q);
			InsFirst_E(Lc, (*Lc).tail, q);
			pb = NextPos_E(hb);
		}
	}

	if (!ListEmpty_E(La))
		Append_E(Lc, pa);
	else
		Append_E(Lc, pb);

	FreeNode_E(&ha);
	FreeNode_E(&hb);

	return OK;
}

int Cmp(LElemType_E c1, LElemType_E c2)
{
	return c1-c2;
}

Status CreateList_ascend(FILE * fp, ELinkList * L, int count)
{
	int i;
	LElemType_E e;

	InitList_E(L);
	if (!L)
		return ERROR;

	for (i = 1; i <= count; i++)
	{
		Scanf(fp, "%d", &e);
		ListInsert_L_E(L, i, e);
	}

	return OK;
}
