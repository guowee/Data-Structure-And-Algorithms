#include <stdio.h>

#include "Polynomial.h"


int main(int argc, char **argv) {

	FILE *fp;
	errno_t err;
	Polynomial Pa, Pb;
	int m, n, i;

	m = 5;
	n = 6;

	printf("��1\n������ CreatPolyn ����...\n");			//1.����CreatPolyn����
	{
		printf("��Ϊʾ������������Ϊ %d �Ķ���ʽPa...\n", m);
		if ((err = fopen_s(&fp, "TestData_Pa.txt", "r"))!= 0) {
			printf("open 'TestData_Pa.txt' failed.\n");
		}		//�ļ�ָ�룬ָ������Դ
		CreatPolyn_P(fp, &Pa, m);
		fclose(fp);
		printf("��Ϊʾ������������Ϊ %d �Ķ���ʽPb...\n", n);
		if ((err = fopen_s(&fp, "TestData_Pb.txt", "r")) != 0) {
			printf("open 'TestData_Pb.txt' failed.\n");
		}
		CreatPolyn_P(fp, &Pb, n);
		fclose(fp);
		printf("\n");
	}
	PressEnter;

	printf("��8\n������ CreatPolyn ����...\n");			//8.����CreatPolyn����	
	{
		printf("һԪ����ʽ Pa = ");
		PrintPolyn_P(Pa);
		printf("\n");
		printf("һԪ����ʽ Pb = ");
		PrintPolyn_P(Pb);
		printf("\n\n");
	}
	PressEnter;

	printf("��3\n������ PolynLength_P ����...\n");		//3.����PolynLength_P����
	{
		printf(" La ������Ϊ %d ��Lb ������Ϊ %d\n", PolynLength_P(Pa), PolynLength_P(Pb));
		printf("\n");
	}
	PressEnter;

	printf("��4��7\n������ AddPolyn_P �Ȳ���...\n"); 	//4��7.����AddPolyn_P��Cmp_exp
	{
		AddPolyn_P(&Pa, &Pb);
		printf("Pa = Pa + Pb = ");
		PrintPolyn_P(Pa);
		printf("\n\n");
	}
	PressEnter;

	printf("��2\n������DestroyPolyn_P����...\n");		//2.����DestroyPolyn_P����
	{
		printf("���� Pa ǰ��");
		(Pa.head && Pa.tail && Pa.len) ? printf(" Pa ���ڣ�\n") : printf(" Pa �����ڣ���\n");
		DestroyPolyn_P(&Pa);
		printf("���� Pa ��");
		(Pa.head && Pa.tail && Pa.len) ? printf(" Pa ���ڣ�\n") : printf(" Pa �����ڣ���\n");
		printf("\n");
	}
	PressEnter;

	printf("��5\n������ SubtractPolyn_P ����...\n");	//5.����SubtractPolyn_P����	
	{
		fopen_s(&fp, "TestData_Pa.txt", "r");
		CreatPolyn_P(fp, &Pa, m);
		fclose(fp);
		fopen_s(&fp, "TestData_Pb.txt", "r");
		CreatPolyn_P(fp, &Pb, n);
		fclose(fp);
		SubtractPolyn_P(&Pa, &Pb);
		printf(" Pa = Pa - Pb = ");
		PrintPolyn_P(Pa);
		DestroyPolyn_P(&Pa);
		printf("\n\n");
	}
	PressEnter;

	printf("��6\n������ MultiplyPolyn_P ����...\n");	//6.����MultiplyPolyn_P����	
	{
		fopen_s(&fp, "TestData_Pa.txt", "r");
		CreatPolyn_P(fp, &Pa, m);
		fclose(fp);
		fopen_s(&fp, "TestData_Pb.txt", "r");
		CreatPolyn_P(fp, &Pb, n);
		fclose(fp);
		MultiplyPolyn_P(&Pa, &Pb);
		printf(" Pa = Pa * Pb = ");
		PrintPolyn_P(Pa);
		DestroyPolyn_P(&Pa);
		printf("\n\n");
	}
	PressEnter;

	return 0;
}
