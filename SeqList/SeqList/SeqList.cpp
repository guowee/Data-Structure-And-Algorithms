#include "header.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10 

Status InitList(SqList &L) {
	/* 操作结果：构造一个空的顺序线性表 */
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) {
		exit(OVERFLOW); /* 存储分配失败 */
	}
	L.length = 0;/* 空表长度为0 */
	L.listsize = LIST_INIT_SIZE;/* 初始存储容量 */
	return OK;
}

Status DestoryList(SqList & L)
{ /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}

Status ClearList(SqList & L)
{/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
	L.length = 0;
	return OK;
}

Status ListEmpty(SqList L)
{/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
	if (L.length == 0) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int ListLength(SqList L)
{/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
	return L.length;
}

Status GetElem(SqList L, int index, ElemType & e)
{/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：用e返回L中第i个数据元素的值 */
	if (index < 1 ||index > L.length) {
		return ERROR;
	}
	e = *(L.elem + index - 1);
	return OK;
}

int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType))
{/* 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1,否则为0) */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0。 */
	ElemType *p;
	int i = 1; /* i的初值为第1个元素的位序 */
	p = L.elem; /* p的初值为第1个元素的存储位置 */
	while (i <= L.length && !compare(*p++, e))
		++i;
	if (i <= L.length)
		return i;
	else
		return 0;
}

Status PriorElem(SqList L, ElemType cur_e, ElemType & pre_e)
{/* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
	int i = 2;
	ElemType *p = L.elem + 1;
	while (i <= L.length && *p != cur_e)
	{
		p++;
		i++;
	}
	if (i > L.length)
		return INFEASIBLE;
	else
	{
		pre_e = *--p;
		return OK;
	}
}

Status NextElem(SqList L, ElemType cur_e, ElemType & next_e)
{
	/* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
	int i = 1;
	ElemType *p = L.elem;
	while (i < L.length && *p != cur_e)
	{
		i++;
		p++;
	}
	if (i == L.length)
		return INFEASIBLE;
	else
	{
		next_e = *++p;
		return OK;
	}
}

Status ListInsert(SqList &L, int index, ElemType element) {
	/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
   /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
	ElemType *newBase, *q, *p;
	if (index < 1 || index > L.length + 1) {
		return ERROR;
	}

	if(L.length >= L.listsize ){
		newBase = (ElemType*)realloc(L.elem,(L.listsize + LIST_INCREMENT) * sizeof(ElemType));
		 if (!newBase)
		 {
			 exit(OVERFLOW);
		 }
		 L.elem = newBase;
		 L.listsize += LIST_INCREMENT;
	}

	q = L.elem + index - 1;

	for (p = L.elem + L.length - 1; p >= q; p--) {
		*(p + 1) = *p;
	}
	*q = element;
	++L.length;
	return OK;
}

Status ListDelete(SqList &L, int index, ElemType &e)
{
	/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
	ElemType *p, *q;
	if (index<1 || index > L.length) /* index值不合法 */
		return ERROR;
	p = L.elem + index - 1; /* p为被删除元素的位置 */
	e = *p; /* 被删除元素的值赋给e */
	q = L.elem + L.length - 1; /* 表尾元素的位置 */
	for (++p; p <= q; ++p) /* 被删除元素之后的元素左移 */
		*(p - 1) = *p;
	L.length--; /* 表长减1 */
	return OK;
}

Status ListTraverse(SqList L,void(*vi)(ElemType*)) {
	/* 初始条件：顺序线性表L已存在 */
   /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
   /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
	ElemType *p;
	int i;
	p = L.elem;
	for (i = 1; i <= L.length; i++)
		vi(p++);
	printf("\n");
	return OK;
}


