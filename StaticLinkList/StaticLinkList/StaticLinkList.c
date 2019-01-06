#ifndef STATICLINKLIST_C
#define STATICLINKLIST_C

#include "Header.h"


void InitSpace_SL()
{
	int i;
	for ( i = 0; i < MAXSIZE -1; i++)
	{
		SPACE[i].cur = i + 1;
	}
	SPACE[MAXSIZE - 1].cur = 0;
}

int Malloc_SL()
{//数组的第0分量可看成头结点，其指针域指示链表的第一个节点
	int i;
	i = SPACE[0].cur;
	if (SPACE[0].cur) {
		SPACE[0].cur = SPACE[i].cur;
		return i;
	}
	else
	{
		return 0;
	}
}

void Free_SL(int k)
{
	SPACE[k].cur = SPACE[0].cur;
	SPACE[0].cur = k;
}

int InitList_SL(SLinkList * H)
{
	*H = Malloc_SL();
	if (!(*H))
	{
		exit(OVERFLOW);
	}
	SPACE[*H].cur = 0;
	return OK;
}

Status ClearList_SL(SLinkList H)
{
	int p;
	if (!H) {
		return ERROR;
	}
	p = SPACE[H].cur;
	while (p) {
		SPACE[H].cur = SPACE[p].cur;
		Free_SL(p);
		p = SPACE[H].cur;
	}

	return OK;
}

void DestroyList_SL(SLinkList * H)
{
	ClearList_SL(*H);					//清空静态链表 

	Free_SL(*H);							//释放头结点	
	*H = 0;
}

Status ListEmpty_SL(SLinkList H)
{
	if (H && !SPACE[H].cur)				//只有头结点 
		return TRUE;
	else
		return FALSE;
}

int ListLength_SL(SLinkList H)
{
	int count;							//计数器
	int p;

	if (!H)
		exit(OVERFLOW);

	count = 0;
	p = SPACE[H].cur;

	while (p)
	{
		count++;
		p = SPACE[p].cur;
	}

	return count;
}

Status GetElem_SL(SLinkList H, int i, LElemType_S * e)
{
	int count, p;

	if (!H || i<1 || i>MAXSIZE - 2)
		return ERROR;

	count = 0;
	p = SPACE[H].cur;

	while (p)
	{
		count++;

		if (count == i)
		{
			*e = SPACE[p].data;
			return OK;
		}

		p = SPACE[p].cur;
	}
	return ERROR;
}

int LocateElem_SL(SLinkList H, LElemType_S e)
{
	int k, count;

	count = 1;
	if (H && SPACE[H].cur)
	{
		k = SPACE[H].cur;

		while (k && SPACE[k].data != e)
		{
			count++;
			k = SPACE[k].cur;
		}

		if (k)
			return count;
	}

	return 0;
}

Status PriorElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S * pre_e)
{
	int p, q;

	if (H)
	{
		p = SPACE[H].cur;

		if (p && SPACE[p].data != cur_e)
		{
			q = SPACE[p].cur;

			while (q && SPACE[q].data != cur_e)
			{
				p = q;
				q = SPACE[q].cur;
			}

			if (q)								//找到了cur_e
			{
				*pre_e = SPACE[p].data;
				return OK;
			}
		}
	}

	return ERROR;
}

Status NextElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S * next_e)
{
	int p;

	if (H)
	{
		p = SPACE[H].cur;

		while (p && SPACE[p].data != cur_e)
			p = SPACE[p].cur;

		if (p && SPACE[p].cur)					//找到了cur_e且不是最后一个结点 
		{
			p = SPACE[p].cur;
			*next_e = SPACE[p].data;
			return OK;
		}
	}

	return ERROR;
}

Status ListInsert_SL(SLinkList H, int i, LElemType_S e)
{
	int count, k, p;

	if (!H)								//链表不存在 
		return ERROR;

	if (i > 0)
	{
		count = 0;
		k = H;							//k指向头结点 

		while (k && count < i - 1)			//寻找插入位置的前一个位置 
		{
			count++;
			k = SPACE[k].cur;
		}

		if (k)							//找到了第i-1个元素的位置 
		{
			p = Malloc_SL();
			if (!p)						//申请空间失败 
				return ERROR;

			SPACE[p].data = e;			//插入元素e 
			SPACE[p].cur = SPACE[k].cur;
			SPACE[k].cur = p;

			return OK;
		}
	}

	return ERROR;
}

Status ListDelete_SL(SLinkList H, int i, LElemType_S * e)
{
	int count, k, p;

	if (!H)								//链表不存在 
		return ERROR;

	if (i > 0)
	{
		count = 0;
		k = H;							//k指向头结点 

		while (k && count < i - 1)			//寻找插入位置的前一个位置 
		{
			count++;
			k = SPACE[k].cur;
		}

		if (k && SPACE[k].cur)			//找到了第i-1个元素的位置且不是最后一个元素 
		{
			p = SPACE[k].cur;			//p指向要被删除的结点 
			*e = SPACE[p].data;
			SPACE[k].cur = SPACE[p].cur;
			Free_SL(p);

			return OK;
		}
	}

	return ERROR;
}

Status ListTraverse_SL(SLinkList H, void(Visit)(LElemType_S))
{
	int p;

	if (!H)
		return ERROR;					//静态链表不存在或为空

	p = SPACE[H].cur;

	while (p)
	{
		Visit(SPACE[p].data);
		p = SPACE[p].cur;
	}

	return OK;
}
void difference(SLinkList * S, LElemType_S A[], int len_A, LElemType_S B[], int len_B)
{
	int i, j;
	int r, p, k;
	LElemType_S b;

	InitSpace_SL();
	*S = Malloc_SL();
	r = *S;
	SPACE[r].cur = 0;

	for (j = 0; j < len_A; j++)
	{
		i = Malloc_SL();
		SPACE[i].data = A[j];
		SPACE[r].cur = i;
		r = i;
	}
	SPACE[r].cur = 0;

	for (j = 0; j < len_B; j++)
	{
		b = B[j];
		p = *S;
		k = SPACE[*S].cur;
		while (k && SPACE[k].data != b)
		{
			p = k;
			k = SPACE[k].cur;
		}

		if (!k) {
			i = Malloc_SL();
			SPACE[i].data = b;
			SPACE[i].cur = SPACE[r].cur;
			SPACE[r].cur = i;
		}
		else {
			SPACE[p].cur = SPACE[k].cur;
			Free_SL(k);
			if (k == r) {
				r = p;
			}
		}
	}
}
#endif // !STATICLINKLIST_CPP