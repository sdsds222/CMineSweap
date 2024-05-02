#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Utils.h"

void start(int mw, int mh, int mNum);
int main(int argc, char *argv[])
{
	srand(time(NULL)); // �������������
	while (1)
	{
	start:
		printf("\a\a");
		system("cls");
		printf("�� C����ɨ��2021 ��\n");
		printf("���� 1����ʼ��Ϸ�� 2���鿴���ܣ� 3���˳���Ϸ\n");
		int select = 1;
		scanf("%d", &select);
		printf("\a");
		if (select == 1)
		{ // ѡ��ʼ��Ϸ
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��ѡ����Ϸģʽ��1���򵥣�2����ͨ��3�����ѣ�4��ר��\n");
			int mode = 0;
			scanf("%d", &mode);
			printf("\a");
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("�����õ��׵�����:\n");
			select = 1; // ��λ
			scanf("%d", &select);
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��Ϸ���������ʼ\n");
			sleep(1);
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��...\n");
			printf("\a");
			sleep(1);
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��..\n");
			printf("\a");
			sleep(1);
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("һ.\n");
			printf("\a");
			sleep(1);
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��ʼ��\n");
			printf("\a\a");
			sleep(1);
			system("cls");
			if (mode == 1)
			{ // ѡ���ģʽ
				start(9, 9, select);
			}
			else if (mode == 2)
			{ // ѡ����ͨģʽ
				start(12, 12, select);
			}
			else if (mode == 3)
			{ // ѡ������ģʽ
				start(20, 20, select);
			}
			else if (mode == 4)
			{ // ѡ��ר��ģʽ
				start(36, 36, select);
			}
		}
		else if (select == 2)
		{ // �鿴����
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			printf("��Ϸ��飺\nͨ����������������Ӧλ�õ�������в�����\n�á�,�����������롰3,6����ʾ�ڿ������С������е����飬\n�á�.�����������롰3.6����ʾ�ڵ����С������в��죬\n�á�/�����������롰3/6����ʾ�ڵ����С����������ʺű�ǡ�\n");
			printf("Cony Studio sdsds222��Ʒ��2021��10��25�ա�\n\n");
			printf("�������������������...");
			getchar();
			goto start;
		}
		else
		{ // �˳���Ϸ
			system("cls");
			break;
		}
		printf("�� C����ɨ��2021 ��\n");
		printf("��Ϸ�ѽ��������� 1�����¿�ʼ��Ϸ�� 2���˳���Ϸ\n");
		select = 0;
		scanf("%d", &select);
		if (select == 1)
		{
			system("cls");
		}
		else if (select == 2)
		{
			system("cls");
			break; // �˳���Ϸ
		}
	}
	return 0;
}


void start(int mw, int mh, int mNum)
{													 // mNum�ĺ���Ϊ���׵ĸ���������һ��9*9��ɨ����Ϸ
	int nowTime = time(NULL);						 // ��¼���ڵ�ʱ��
	int *map = (int *)malloc(mw * mh * sizeof(int)); // ��̬��������
	int *showMap = (int *)malloc(mw * mh * sizeof(int));
	int i1;
	for (i1 = 0; i1 < mw * mh; i1++)
	{ // ��ʼ������
		map[i1] = 0;
		showMap[i1] = 0;
	}
	while (getMineNum(map, mw, mh) < mNum)
	{								// ������ɵ���
		int x = getRand(0, mw - 1); // ȡһ��0��8�������
		int y = getRand(0, mh - 1);
		map[x * mw + y] = 9; // ���Ϊ����,9��ʾ�е���
	}

	int i, j;
	for (i = 0; i < mw; i++)
	{ // �������ܱߵ�����
		for (j = 0; j < mh; j++)
		{
			if (map[i * mw + j] != 9)
			{
				int n = 0; // �������ص�����
				int loc[16] = {0};
				getLocation(loc, i, j);
				int leftUpX = loc[0], leftUpY = loc[1],
					upX = loc[2], upY = loc[3],
					rightUpX = loc[4], rightUpY = loc[5],
					rightX = loc[6], rightY = loc[7],
					rightDownX = loc[8], rightDownY = loc[9],
					downX = loc[10], downY = loc[11],
					leftDownX = loc[12], leftDownY = loc[13],
					leftX = loc[14], leftY = loc[15];

				if (upY >= 0)
				{ // �ж��ϱ��Ƿ񳬳���Χ,��δ������Χ��ִ���ж��Ƿ��е��׵Ĳ���
					if (map[upX * mw + upY] == 9)
					{
						n++;
					}
				}
				if (downY <= mh - 1)
				{ // �ж��±��Ƿ񳬳���Χ,��δ������Χ��ִ���ж��Ƿ��е��׵Ĳ���
					if (map[downX * mw + downY] == 9)
					{
						n++;
					}
				}
				if (rightX <= mw - 1)
				{ // �ж��ұ��Ƿ񳬳���Χ
					if (map[rightX * mw + rightY] == 9)
					{
						n++;
					}
				}

				if (leftX >= 0)
				{ // �ж�����Ƿ񳬳���Χ
					if (map[leftX * mw + leftY] == 9)
					{
						n++;
					}
				}
				if (leftUpX >= 0 && leftUpY >= 0)
				{
					if (map[leftUpX * mw + leftUpY] == 9)
					{
						n++;
					}
				}
				if (rightUpX <= mw - 1 && rightUpY >= 0)
				{
					if (map[rightUpX * mw + rightUpY] == 9)
					{
						n++;
					}
				}
				if (rightDownX <= mw - 1 && rightDownY <= mh - 1)
				{
					if (map[rightDownX * mw + rightDownY] == 9)
					{
						n++;
					}
				}
				if (leftDownX >= 0 && leftDownY <= mh - 1)
				{
					if (map[leftDownX * mw + leftDownY] == 9)
					{
						n++;
					}
				}
				map[i * mw + j] = n;
			}
		}
	}

	while (1)
	{
		printf("�� C����ɨ��2021 ��\n");
		printf("һ��������%d������\n", getMineNum(map, mw, mh));
		print(showMap, map, mw, mh);
		int p, m, num1 = 0;
		for (p = 0; p < mw; p++)
		{ // ɨ�貢ͳ������δɨ�ķ��������������������ڵ��׵���������ô���ж�ΪӮ
			for (m = 0; m < mh; m++)
			{
				if (showMap[p * mw + m] == 0 || showMap[p * mw + m] == 2 || showMap[p * mw + m] == 3)
				{
					num1++;
				}
			}
		}
		if (num1 == mNum)
		{
			int k1;
			for (k1 = 0; k1 < mw * mh; k1++)
			{
				showMap[k1] = 1;
			}
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			print(showMap, map, mw, mh);
			printf("��Ӯ��! ��ʱ%d�롣\n�������������...", time(NULL) - nowTime);
			printf("\a\a\a");
			getchar();
			system("cls");
			break;
		}

		char command = 0;
		int cx = 0, cy = 0, isOnMine = 0;
		scanf("%d%c%d", &cy, &command, &cx);
		if (cy < 1 || cy > mh)
		{
			cy = 1;
		}
		if (cx < 1 || cx > mw)
		{
			cx = 1;
		}
		switch (command)
		{
		case '.':
			printf("\a\a");
			if (showMap[(cx - 1) * mw + (cy - 1)] != 1)
			{ // �жϸ������Ƿ��ڿ�
				if (showMap[(cx - 1) * mw + (cy - 1)] == 2)
				{
					showMap[(cx - 1) * mw + (cy - 1)] = 0;
				}
				else
				{
					showMap[(cx - 1) * mw + (cy - 1)] = 2;
				}
			}
			break;
		case '/':
			printf("\a\a");
			if (showMap[(cx - 1) * mw + (cy - 1)] != 1)
			{ // �жϸ������Ƿ��ڿ�
				if (showMap[(cx - 1) * mw + (cy - 1)] == 3)
				{
					showMap[(cx - 1) * mw + (cy - 1)] = 0;
				}
				else
				{
					showMap[(cx - 1) * mw + (cy - 1)] = 3;
				}
			}
			break;
		case ',':
			printf("\a");
			isOnMine = clean(showMap, map, mw, mh, cx - 1, cy - 1, 0);
			break;
		default:
			break;
		}
		if (isOnMine == 1)
		{ // �ж��Ƿ�ȵ�����
			int k1;
			for (k1 = 0; k1 < mw * mh; k1++)
			{
				showMap[k1] = 1;
			}
			system("cls");
			printf("�� C����ɨ��2021 ��\n");
			print(showMap, map, mw, mh);
			printf("��ȵ������ˣ���Ϸ������\n�����������...");
			printf("\a\a"); // SOS
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a\a\a");
			getchar();
			system("cls"); // ��տ���̨
			break;		   // ����ѭ��
		}
		system("cls"); // ��տ���̨
					   // ��ʼ��һ��ѭ��
	}
	free(map); // �ͷ��ڶ��϶�̬����������
	free(showMap);
}
