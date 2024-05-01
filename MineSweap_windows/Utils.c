#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int clean(int *showMap, int *map, int w, int h, int x, int y, int mode);

int getRand(int min, int max)
{ // ȡ�����
	return rand() % (max - min + 1) + min;
}
int getMineNum(int *map, int w, int h)
{ // ��ȡ�ܵ�����
	int i, j, n = 0;
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			if (map[i * w + j] == 9)
			{
				n++;
			}
		}
	}
	return n;
}
void getLocation(int *block, int i, int j)
{ // ��ȡ��Χ�˸������λ��,�����ڴ���ĵ�ַָ���������
	int leftUpX = i - 1, leftUpY = j - 1;
	int upX = i, upY = j - 1;
	int rightUpX = i + 1, rightUpY = j - 1;
	int rightX = i + 1, rightY = j;
	int rightDownX = i + 1, rightDownY = j + 1;
	int downX = i, downY = j + 1;
	int leftDownX = i - 1, leftDownY = j + 1;
	int leftX = i - 1, leftY = j;
	int location[16] = {leftUpX, leftUpY, upX, upY, rightUpX, rightUpY, rightX, rightY, rightDownX, rightDownY, downX, downY, leftDownX, leftDownY, leftX, leftY};
	int m;
	for (m = 0; m < 16; m++)
	{
		*block = location[m];
		block++;
	}
	block = NULL;
}
void fillBlank(int *map, int w, int h, int x, int y)
{ // ���������Ƭ�Ŀշ���
	if (map[x * w + y] == 0)
	{
		map[x * w + y] = -1;
		int loc[16];
		getLocation(loc, x, y);
		int leftUpX = loc[0], leftUpY = loc[1],
			upX = loc[2], upY = loc[3],
			rightUpX = loc[4], rightUpY = loc[5],
			rightX = loc[6], rightY = loc[7],
			rightDownX = loc[8], rightDownY = loc[9],
			downX = loc[10], downY = loc[11],
			leftDownX = loc[12], leftDownY = loc[13],
			leftX = loc[14], leftY = loc[15];

		if (downY <= h - 1)
		{ // �ж��±��Ƿ񳬳���Χ,��δ������Χ��ִ���ж��Ƿ��е��׵Ĳ���

			if (map[downX * w + downY] == 0)
			{
				fillBlank(map, w, h, downX, downY); // �ݹ�
			}
		}

		if (upY >= 0)
		{ // �ж��ϱ��Ƿ񳬳���Χ
			if (map[upX * w + upY] == 0)
			{
				fillBlank(map, w, h, upX, upY);
			}
		}

		if (rightX <= w - 1)
		{ // �ж��ұ��Ƿ񳬳���Χ
			if (map[rightX * w + rightY] == 0)
			{
				fillBlank(map, w, h, rightX, rightY);
			}
		}
		if (leftX >= 0)
		{ // �ж�����Ƿ񳬳���Χ
			if (map[leftX * w + leftY] == 0)
			{
				fillBlank(map, w, h, leftX, leftY);
			}
		}
	}
}
void clean0(int *showMap, int *map, int w, int h, int x, int y)
{
	fillBlank(map, w, h, x, y);
	int i, j;
	for (i = 0; i < w; i++)
	{ // �������з��飬����ֵΪ-1�ķ������
		for (j = 0; j < h; j++)
		{
			if (map[i * w + j] == -1)
			{
				int loc[16];
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
					clean(showMap, map, w, h, i, j - 1, 1);
				}
				if (downY <= h - 1)
				{ // �ж��±��Ƿ񳬳���Χ,��δ������Χ��ִ���ж��Ƿ��е��׵Ĳ���
					clean(showMap, map, w, h, i, j + 1, 1);
				}
				if (rightX <= w - 1)
				{ // �ж��ұ��Ƿ񳬳���Χ
					clean(showMap, map, w, h, i + 1, j, 1);
				}

				if (leftX >= 0)
				{ // �ж�����Ƿ񳬳���Χ
					clean(showMap, map, w, h, i - 1, j, 1);
				}
				if (leftUpX >= 0 && leftUpY >= 0)
				{
					clean(showMap, map, w, h, i - 1, j - 1, 1);
				}
				if (rightUpX <= w - 1 && rightUpY >= 0)
				{
					clean(showMap, map, w, h, i + 1, j - 1, 1);
				}
				if (rightDownX <= 8 && rightDownY <= h - 1)
				{
					clean(showMap, map, w, h, i + 1, j + 1, 1);
				}
				if (leftDownX >= 0 && leftDownY <= h - 1)
				{
					clean(showMap, map, w, h, i - 1, j + 1, 1);
				}
			}
		}
	}
	int k;
	for (k = 0; j < w * h; j++)
	{ // �������з��飬��ֵΪ-1�ķ��黻����
		if (map[k] == -1)
		{
			map[k] = 0;
		}
	}
}

int clean(int *showMap, int *map, int w, int h, int x, int y, int mode)
{ // ��ɨָ������,mode = 0ʱ������Ƭɨ��ģʽ��mode = 1ʱ��������ɨ��ģʽ���������0�����ʾû�ȵ��ף��������1�����ʾ�ȵ�����
	if (showMap[x * w + y] == 0)
	{ // ��showMap�У�1��ʾ�Ѿ���ɨ���ˣ�0��ʾδ��ɨ��
		if (map[x * w + y] == 9)
		{ // �ж��Ǹ�������ǵ���
			return 1;
		}
		else if (map[x * w + y] == 0 && mode == 0)
		{									  // �жϸ������Ƿ�Ϊ0
			clean0(showMap, map, w, h, x, y); // ��������Ϊ0����������Ƭɨ��
			showMap[x * w + y] = 1;
		}
		else
		{
			showMap[x * w + y] = 1;
		}
	}
	return 0;
}
void print(int *showMap, int *map, int mw, int mh)
{
	char xIndex[1000] = {'\0'};
	int xi, xi2;
	for (xi = 0, xi2 = 0; xi2 < mw; xi += 2, xi2++)
	{
		int g = (xi2 + 1) % 10;
		int s = (xi2 + 1) % 100 / 10;
		if (xi2 + 1 < 10)
		{
			xIndex[xi] = ' ';
		}
		else
		{
			xIndex[xi] = 48 + s;
		}
		xIndex[xi + 1] = 48 + g;
	}
	printf("   %s\n", xIndex); // ����к�
	int k, l;
	for (k = 0; k < mw; k++)
	{
		for (l = 0; l < mh; l++)
		{
			if (l == 0)
			{
				if (k + 1 < 10)
				{ // �����кŵĸ�ʽ
					printf("  %d", k + 1);
				}
				else
				{
					printf(" %d", k + 1);
				}
			}
			if (showMap[k * mw + l] == 1)
			{ // �жϸ������Ƿ��ѱ��ڿ�
				if (map[k * mw + l] == 1)
				{
					printf("Ҽ");
				}
				else if (map[k * mw + l] == 2)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 3)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 4)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 5)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 6)
				{
					printf("½");
				}
				else if (map[k * mw + l] == 7)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 8)
				{
					printf("��");
				}
				else if (map[k * mw + l] == 9)
				{ // ����
					printf("��");
				}
				else
				{
					printf("��");
				}
			}
			else if (showMap[k * mw + l] == 2)
			{ // ���������
				printf("��");
			}
			else if (showMap[k * mw + l] == 3)
			{ // ������ʺ�
				printf("��");
			}
			else if (showMap[k * mw + l] == 0)
			{ // �����δ�ڿ��ķ���
				printf("��");
			}
		}
		printf("%c", '\n');
	}
}
