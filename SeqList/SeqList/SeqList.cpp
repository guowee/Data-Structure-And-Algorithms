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

//在第i(1<=i<=n)个元素之前插入一个元素，需要将第n至第i个元素向后移动一个位置
Status InsertElement(SqList &L, int index, ElemType element) {
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

Status DeleteElement(SqList &L, int index, ElemType &e)
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

Status TraverseList(SqList L,void(*vi)(ElemType*)) {
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


