#include <stdio.h>
#include "header.h"

void print(ElemType *c)
{
	printf("%d ", *c);
}
void main() {

	SqList list;
	InitList(list);
	for (int i = 0; i < 10; i++)
	{
		Status status = InsertElement(list,i+1,i+5);
		if (status == OK) {
			printf("Insert Element Success! \n");
		}
		else {
			printf("Insert Element Error! \n");
		}
	}

	TraverseList(list,print);

	ElemType e;
	DeleteElement(list, 2, e);
	print(&e);
	printf("\n");
	TraverseList(list, print);
}

















