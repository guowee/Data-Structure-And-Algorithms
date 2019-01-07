#include <stdio.h>
#include "Header.h"
Status Compare(LElemType_DC e, LElemType_DC data)
{
	return data > e ? TRUE : FALSE;
}

void PrintElem(LElemType_DC e)
{
	printf("%d ", e);
}


int main(int argc, char **argv) {
	DuLinkList L;
	LElemType_DC e;
	int i;

	printf(">>1.Function InitList_DuL Test...\n");
	{
		InitList_DuL(&L);
		printf("\n");
	}
	PressEnter;

	printf(">>2.Function ListEmpty_DuL Test...\n");
	{
		ListEmpty_DuL(L) ? printf(" L is NULL.\n") : printf(" L is not NULL.\n");
		printf("\n");
	}
	PressEnter;

	printf(">>3.Function ListInsert_DuL Test...\n");
	{
		for ( i = 1; i <=8; i++)
		{
			printf("在 L 第 %d 个位置插入 \"%d\" ...\n", i, 2 * i);
			ListInsert_DuL(L, i, 2 * i);
		}
		printf("\n");
	}
	PressEnter;

	printf(">>4.Function ListTraverse_DuL Test...\n");
	{
		printf(" L 中的元素为：L = ");
		ListTraverse_DuL(L, PrintElem);
		printf("\n\n");
	}
	PressEnter;

	printf(">>5.Function ListLength_DuL Test...\n");
	{
		printf(" L 的长度为 %d \n", ListLength_DuL(L));
		printf("\n");
	}
	PressEnter;

	printf(">>6.Function ListDelete_DuL Test...\n");
	{
		ListDelete_DuL(L, 5, &e);
		printf("删除 L 中第5个元素 \"%d\" ...\n", e);
		printf(" L 中的元素为：L = ");
		ListTraverse_DuL(L, PrintElem);
		printf("\n\n");
	}
	PressEnter;

	printf(">>7.Function GetElem_DuL Test...\n");		
	{
		GetElem_DuL(L, 4, &e);
		printf(" L 中第 4 个位置的元素为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>8.Function LocateElem_DuL Test...\n");		
	{
		i = LocateElem_DuL(L, 7, Compare);
		printf(" L 中第一个元素值大于 \"7\" 的元素的位置为 %d \n", i);
		printf("\n");
	}
	PressEnter;

	printf(">>9.Function PriorElem_DuL Test...\n");		
	{
		PriorElem_DuL(L, 6, &e);
		printf("元素 \"6\" 的前驱为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>10.Function NextElem_DuL Test...\n");		//9.函数NextElem_DuL测试
	{
		NextElem_DuL(L, 6, &e);
		printf("元素 \"6\" 的后继为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>11.Function GetElemPtr_DuL Test...\n");			//10.函数GetElem_P测试
	{
		DuLinkList p;
		p = GetElemPtr_DuL(L, 3);
		printf("链表第 3 个结点的指针为 0x%x，其对应的值为 \"%d\" \n", p, p->data);
		printf("\n");
	}
	PressEnter;

	
	printf(">>12.Function ClearList_DuL Test...\n");		
	{
		printf("清空 L 前：");
		ListEmpty_DuL(L) ? printf(" L 为空！！\n") : printf(" L 不为空！\n");
		ClearList_DuL(L);
		printf("清空 L 后：");
		ListEmpty_DuL(L) ? printf(" L 为空！！\n") : printf(" L 不为空！\n");
		printf("\n");
	}
	PressEnter;
	

	printf(">>13.Function DestroyList_DuL Test...\n");	//2.函数DestroyList_DuL测试
	{
		printf("销毁 L 前：");
		L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");
		DestroyList_DuL(&L);
		printf("销毁 L 后：");
		L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");
		printf("\n");
	}
	PressEnter;
	return 0;
}


