#include "header.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10 

Status InitList(SqList &L) {
	/* �������������һ���յ�˳�����Ա� */
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) {
		exit(OVERFLOW); /* �洢����ʧ�� */
	}
	L.length = 0;/* �ձ���Ϊ0 */
	L.listsize = LIST_INIT_SIZE;/* ��ʼ�洢���� */
	return OK;
}

//�ڵ�i(1<=i<=n)��Ԫ��֮ǰ����һ��Ԫ�أ���Ҫ����n����i��Ԫ������ƶ�һ��λ��
Status InsertElement(SqList &L, int index, ElemType element) {
	/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
   /* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
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
	/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
   /* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
	ElemType *p, *q;
	if (index<1 || index > L.length) /* indexֵ���Ϸ� */
		return ERROR;
	p = L.elem + index - 1; /* pΪ��ɾ��Ԫ�ص�λ�� */
	e = *p; /* ��ɾ��Ԫ�ص�ֵ����e */
	q = L.elem + L.length - 1; /* ��βԪ�ص�λ�� */
	for (++p; p <= q; ++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
		*(p - 1) = *p;
	L.length--; /* ����1 */
	return OK;
}

Status TraverseList(SqList L,void(*vi)(ElemType*)) {
	/* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
   /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
	ElemType *p;
	int i;
	p = L.elem;
	for (i = 1; i <= L.length; i++)
		vi(p++);
	printf("\n");
	return OK;
}


