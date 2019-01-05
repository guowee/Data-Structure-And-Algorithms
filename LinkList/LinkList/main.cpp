#include <stdio.h>
#include "header.h"

void print(ElemType c)
{
	printf("%d ", c);
}


int main() {

	LinkList La,Lb,Lc;
	InitList(La);
	ListTraverse(La, print);

	CreateListHead(La,5);
	ListTraverse(La, print);

	ClearList(La);

	printf("\n--------------\n");

	CreateListTail(La,8);
	ListTraverse(La,print);

	ElemType e;
	int i = 1;
	GetElem(La, i, e);
	printf("\n");
	printf("The %dth Element of List is: %d\n", i, e);

	e = 100;
	printf("The location of e is: %d\n ", LocateElem(La, e));


	i = 1;
	e = -100;
	ListInsert(La, i, e);
	ListTraverse(La,print);
	printf("\n");
	ListDelete(La, i, e);
	printf("The deleted %dth element is: %d\n", i, e);
    ListTraverse(La,print);
	printf("\n");
	ListReverse(La);
	ListTraverse(La, print);
	printf("\n");
	InitList(Lb);

	CreateListHead(Lb, 6);
	ListTraverse(Lb, print);
	printf("\n");
	MergeList(La, Lb, Lc);
	ListTraverse(Lc,print);

	return 0;
}

