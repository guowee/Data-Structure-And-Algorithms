#include <stdio.h>
#include "header.h"

Status equal(ElemType c1, ElemType c2)
{ /* 判断是否相等的函数，Union()用到 */
	if (c1 == c2)
		return TRUE;
	else
		return FALSE;
}

void print(ElemType *c)
{
	printf("%d ", *c);
}

void Union(SqList &La,SqList Lb) {
 /*将所有在线性表Lb中但不在La中的数据元素插入到La中*/
	ElemType e;
	int La_len, Lb_len;
	int i;
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
	for (i = 1; i <= Lb_len;i++) {
		GetElem(Lb, i, e);
		if (!LocateElem(La, e, equal)) {
			ListInsert(La,++La_len,e);
		}
	}
}


void MergeList(SqList La,SqList Lb,SqList &Lc) {
	/*已知线性表La和Lb中的数据元素按值非递减排列，归并La和Lb得到新的线性表Lc,Lc中的数据元素也按非递减排列*/
	InitList(Lc);
	ElemType ai, bj;
	int La_len, Lb_len;
	int i =1, j = 1, k = 0;
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
	while ((i <= La_len) && (j <= Lb_len)) {
		GetElem(La, i, ai);
		GetElem(Lb, j, bj);
		if (ai<=bj) {
			ListInsert(Lc,++k,ai);
			++i;
		}
		else {
			ListInsert(Lc, ++k, bj);
			++j;
		}
	}

	while (i <= La_len) {
		GetElem(La, i++, ai);
		ListInsert(Lc, ++k, ai);
	}

	while (j <= Lb_len)
	{
		GetElem(Lb, j++, bj);
		ListInsert(Lc, ++k, bj);
	}
}




int main() {

	SqList La,Lb;
	InitList(La);
	for (int i = 0; i < 10; i++)
	{
		Status status = ListInsert(La,i+1,i+5);
		if (status == OK) {
			printf("Insert Element Success! \n");
		}
		else {
			printf("Insert Element Error! \n");
		}
	}

	ListTraverse(La,print);

	ElemType e;
	ListDelete(La, 2, e);
	print(&e);
	printf("\n");
	ListTraverse(La, print);

	InitList(Lb);
	int j;
	for (j = 1; j <= 5; j++)
	{
		ListInsert(Lb, j, 4 * j);
	}
	ListTraverse(Lb,print);

	SqList Lc;
	MergeList(La, Lb, Lc);
	ListTraverse(Lc, print);

	Union(La, Lb);

	ListTraverse(La,print);

	return 0;
}
