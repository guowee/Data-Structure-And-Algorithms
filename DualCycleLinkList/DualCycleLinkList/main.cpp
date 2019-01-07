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
			printf("�� L �� %d ��λ�ò��� \"%d\" ...\n", i, 2 * i);
			ListInsert_DuL(L, i, 2 * i);
		}
		printf("\n");
	}
	PressEnter;

	printf(">>4.Function ListTraverse_DuL Test...\n");
	{
		printf(" L �е�Ԫ��Ϊ��L = ");
		ListTraverse_DuL(L, PrintElem);
		printf("\n\n");
	}
	PressEnter;

	printf(">>5.Function ListLength_DuL Test...\n");
	{
		printf(" L �ĳ���Ϊ %d \n", ListLength_DuL(L));
		printf("\n");
	}
	PressEnter;

	printf(">>6.Function ListDelete_DuL Test...\n");
	{
		ListDelete_DuL(L, 5, &e);
		printf("ɾ�� L �е�5��Ԫ�� \"%d\" ...\n", e);
		printf(" L �е�Ԫ��Ϊ��L = ");
		ListTraverse_DuL(L, PrintElem);
		printf("\n\n");
	}
	PressEnter;

	printf(">>7.Function GetElem_DuL Test...\n");		
	{
		GetElem_DuL(L, 4, &e);
		printf(" L �е� 4 ��λ�õ�Ԫ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>8.Function LocateElem_DuL Test...\n");		
	{
		i = LocateElem_DuL(L, 7, Compare);
		printf(" L �е�һ��Ԫ��ֵ���� \"7\" ��Ԫ�ص�λ��Ϊ %d \n", i);
		printf("\n");
	}
	PressEnter;

	printf(">>9.Function PriorElem_DuL Test...\n");		
	{
		PriorElem_DuL(L, 6, &e);
		printf("Ԫ�� \"6\" ��ǰ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>10.Function NextElem_DuL Test...\n");		//9.����NextElem_DuL����
	{
		NextElem_DuL(L, 6, &e);
		printf("Ԫ�� \"6\" �ĺ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;

	printf(">>11.Function GetElemPtr_DuL Test...\n");			//10.����GetElem_P����
	{
		DuLinkList p;
		p = GetElemPtr_DuL(L, 3);
		printf("����� 3 ������ָ��Ϊ 0x%x�����Ӧ��ֵΪ \"%d\" \n", p, p->data);
		printf("\n");
	}
	PressEnter;

	
	printf(">>12.Function ClearList_DuL Test...\n");		
	{
		printf("��� L ǰ��");
		ListEmpty_DuL(L) ? printf(" L Ϊ�գ���\n") : printf(" L ��Ϊ�գ�\n");
		ClearList_DuL(L);
		printf("��� L ��");
		ListEmpty_DuL(L) ? printf(" L Ϊ�գ���\n") : printf(" L ��Ϊ�գ�\n");
		printf("\n");
	}
	PressEnter;
	

	printf(">>13.Function DestroyList_DuL Test...\n");	//2.����DestroyList_DuL����
	{
		printf("���� L ǰ��");
		L ? printf(" L ���ڣ�\n") : printf(" L �����ڣ���\n");
		DestroyList_DuL(&L);
		printf("���� L ��");
		L ? printf(" L ���ڣ�\n") : printf(" L �����ڣ���\n");
		printf("\n");
	}
	PressEnter;
	return 0;
}


