#include "Polynomial.h"

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
	if (L.len) {
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
		(*L).tail = h->next;
	}
	(*L).len++;
}

Status DelFirst_E(ELinkList * L, Link h, Link * q)
{

	*q = h->next;
	if (*q) {
		h->next = (*q)->next;
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

	q = PriorPos_E(*L, *p);

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
	if (*p == (*L).tail) {
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
	if (q == p) {
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

	while (count < index)
	{
		count++;
		*p = (*p)->next;
	}
	return OK;
}

Position LocateElem_E(ELinkList L, LElemType_E e, Status(Compare)(LElemType_E, LElemType_E))
{
	Link p = L.head->next;
	while (p && !(Compare(e, p->data)))
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
	for (j = 1; j <= L.len; j++)
	{
		Visit(p->data);
		p = p->next;
	}

	return OK;
}

Status ListInsert_L_E(ELinkList * L, int index, LElemType_E e)
{
	Link h, s;
	if (!LocatePos_E(*L, index - 1, &h)) {
		return ERROR;
	}
	if (!MakeNode_E(&s, e)) {
		return ERROR;
	}

	InsFirst_E(L, h, s);

	return OK;
}

Status ListDelete_L_E(ELinkList * L, int index, LElemType_E * e)
{
	Link p, q;
	if (index < 1 || index >(*L).len) {
		return ERROR;
	}
	LocatePos_E(*L, index - 1, &p);
	DelFirst_E(L, p, &q);
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
	return c1.coef - c2.coef;
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



















void CreatPolyn_P(FILE * fp, Polynomial * P, int m)
{
	Position h;
	ElemType_P e;
	int i;
	Link p;
	InitList_E(P);
	h = GetHead_E(*P);

	e.coef = 0.0;
	e.expn = -1;
	SetCurElem_E(h,e);
	h->next = NULL;

	for ( i = 1; i < m; i++)
	{
		Scanf(fp, "%f%d", &(e.coef), &(e.expn));
		MakeNode_E(&p, e);
		p->next = NULL;
		InsFirst_E(P, h, p);
		h = h->next;
	}
}

void DestroyPolyn_P(Polynomial * P)
{
	DestroyList_E(P);
}

int PolynLength_P(Polynomial P)
{
	return ListLength_E(P);
}

void AddPolyn_P(Polynomial * Pa, Polynomial * Pb)
{
	Position ha, hb;
	Position qa, qb;
	ElemType_P a, b;
	float sum;

	ha = GetHead_E(*Pa);					//ha、hb分别指向Pa、Pb头结点 
	hb = GetHead_E(*Pb);
	qa = NextPos_E(ha);						//qa、qb分别指向Pa、Pb的当前结点
	qb = NextPos_E(hb);

	while (qa && qb)							//qa、qb均非空
	{
		a = GetCurElem_E(qa);				//a和b为两表中当前比较元素 
		b = GetCurElem_E(qb);

		switch (Cmp_exp(a, b))				//比较当前元素的指数大小 
		{
		case -1:						//多项式Pa中当前结点的指数值较小
			ha = qa;
			qa = NextPos_E(ha);
			break;
		case 0:							//两者数值相等 
			sum = a.coef + b.coef;
			if (sum != 0.0)				//相加不能抵消时更新Pa结点的系数值 
			{
				qa->data.coef = sum;
				SetCurElem_E(qa, qa->data);
				ha = qa;				//此时ha需后移 
			}
			else						//相加抵消时，删除Pa中当前结点
			{
				DelFirst_E(Pa, ha, &qa);
				FreeNode_E(&qa);
			}
			DelFirst_E(Pb, hb, &qb);	//删除Pb中扫描过的结点 
			FreeNode_E(&qb);
			qb = NextPos_E(hb);			//qa、qb均后移 
			qa = NextPos_E(ha);
			break;
		case 1:							//多项式Pb中当前结点的指数值较小
			DelFirst_E(Pb, hb, &qb);	//摘下Pb当前结点
			InsFirst_E(Pa, ha, qb); 	//将摘下结点链入Pa中
			qb = NextPos_E(hb);
			ha = NextPos_E(ha);
			break;
		}//switch
	}//while

	if (qb)									//若Pb还未扫描完，将剩余项链接到Pa后 
		Append_E(Pa, qb);

	FreeNode_E(&hb);						//释放Pb头结点
	(*Pb).head = (*Pb).tail = NULL;			//设置Pb为销毁状态 
	(*Pb).len = 0;
}

void SubtractPolyn_P(Polynomial * Pa, Polynomial * Pb)
{
	Position ha, hb;
	Position qa, qb;
	Position r;
	ElemType_P a, b;
	float sum;

	ha = GetHead_E(*Pa);					//ha、hb分别指向Pa、Pb头结点 
	hb = GetHead_E(*Pb);
	qa = NextPos_E(ha);						//qa、qb分别指向Pa、Pb的当前结点
	qb = NextPos_E(hb);

	while (qa && qb)							//qa、qb均非空
	{
		a = GetCurElem_E(qa);				//a和b为两表中当前比较元素 
		b = GetCurElem_E(qb);

		switch (Cmp_exp(a, b))				//比较当前元素的指数大小 
		{
		case -1:						//多项式Pa中当前结点的指数值较小
			ha = qa;
			qa = NextPos_E(ha);
			break;
		case 0:							//两者数值相等 
			sum = a.coef - b.coef;
			if (sum != 0.0)				//相减不能抵消时更新Pa结点的系数值 
			{
				qa->data.coef = sum;
				SetCurElem_E(qa, qa->data);
				ha = qa;				//此时ha需后移 
			}
			else						//相加抵消时，删除Pa中当前结点
			{
				DelFirst_E(Pa, ha, &qa);
				FreeNode_E(&qa);
			}
			DelFirst_E(Pb, hb, &qb);	//删除Pb中扫描过的结点 
			FreeNode_E(&qb);
			qb = NextPos_E(hb);			//qa、qb均后移 
			qa = NextPos_E(ha);
			break;
		case 1:							//多项式Pb中当前结点的指数值较小
			DelFirst_E(Pb, hb, &qb);	//摘下Pb当前结点
			qb->data.coef = -qb->data.coef;	//改变当前结点符号 
			InsFirst_E(Pa, ha, qb); 	//将摘下结点链入Pa中
			qb = NextPos_E(hb);
			ha = NextPos_E(ha);
			break;
		}//switch
	}//while

	if (qb)									//Pb还未扫描完
	{
		r = qb;
		while (r)
		{
			r->data.coef = -r->data.coef;	//改变剩余结点符号 
			r = r->next;
		}
		Append_E(Pa, qb);
	}

	FreeNode_E(&hb);						//释放Pb头结点
	(*Pb).head = (*Pb).tail = NULL;
	(*Pb).len = 0;
}

void MultiplyPolyn_P(Polynomial * Pa, Polynomial * Pb)
{
	Polynomial Pc, Ptmp;
	int i, j, la, lb;
	Position ha;
	Position qa, qb;
	Link s;

	la = PolynLength_P(*Pa);
	lb = PolynLength_P(*Pb);
	ha = (*Pa).head;

	InitList_E(&Pc);

	for (i = 1; i <= la; i++)
	{
		InitList_E(&Ptmp);

		DelFirst_E(Pa, ha, &qa);
		qb = (*Pb).head->next;

		for (j = 1; j <= lb; j++)
		{
			s = (Link)malloc(sizeof(ELNode));				//申请空间 	
			if (!s)
				exit(OVERFLOW);

			s->data.coef = qa->data.coef * qb->data.coef;	//系数相乘 
			s->data.expn = qa->data.expn + qb->data.expn;	//指数相加 
			s->next = NULL;

			Append_E(&Ptmp, s);

			qb = qb->next;
		}

		AddPolyn_P(&Pc, &Ptmp);
	}

	AddPolyn_P(Pa, &Pc);

	DestroyPolyn_P(Pb);
}

int Cmp_exp(ElemType_P c1, ElemType_P c2)
{
	int i = c1.expn - c2.expn;

	if (i < 0)
		return -1;
	else if (i == 0)
		return 0;
	else
		return 1;
}

void PrintPolyn_P(Polynomial P)
{
	int i;
	Link p;

	p = P.head->next;
	for (i = 1; i <= P.len; i++)
	{
		if (i == 1)
			printf("%g", p->data.coef);
		else
		{
			if (p->data.coef > 0)
			{
				printf(" + ");
				printf("%g", p->data.coef);
			}
			else
			{
				printf(" - ");
				printf("%g", -p->data.coef);
			}
		}

		if (p->data.expn)
		{
			printf("x");

			if (p->data.expn != 1)
				printf("^%d", p->data.expn);
		}

		p = p->next;
	}
}
