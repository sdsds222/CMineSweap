#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int clean(int *showMap, int *map, int w, int h, int x, int y, int mode);

int getRand(int min, int max)
{ // 取随机数
	return rand() % (max - min + 1) + min;
}
int getMineNum(int *map, int w, int h)
{ // 获取总地雷数
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
{ // 获取周围八个方块的位置,保存在传入的地址指向的数组中
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
{ // 用于清除连片的空方块
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
		{ // 判断下边是否超出范围,若未超出范围则执行判断是否有地雷的操作

			if (map[downX * w + downY] == 0)
			{
				fillBlank(map, w, h, downX, downY); // 递归
			}
		}

		if (upY >= 0)
		{ // 判断上边是否超出范围
			if (map[upX * w + upY] == 0)
			{
				fillBlank(map, w, h, upX, upY);
			}
		}

		if (rightX <= w - 1)
		{ // 判断右边是否超出范围
			if (map[rightX * w + rightY] == 0)
			{
				fillBlank(map, w, h, rightX, rightY);
			}
		}
		if (leftX >= 0)
		{ // 判断左边是否超出范围
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
	{ // 遍历所有方块，并将值为-1的方块清除
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
				{ // 判断上边是否超出范围,若未超出范围则执行判断是否有地雷的操作
					clean(showMap, map, w, h, i, j - 1, 1);
				}
				if (downY <= h - 1)
				{ // 判断下边是否超出范围,若未超出范围则执行判断是否有地雷的操作
					clean(showMap, map, w, h, i, j + 1, 1);
				}
				if (rightX <= w - 1)
				{ // 判断右边是否超出范围
					clean(showMap, map, w, h, i + 1, j, 1);
				}

				if (leftX >= 0)
				{ // 判断左边是否超出范围
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
	{ // 遍历所有方块，把值为-1的方块换成零
		if (map[k] == -1)
		{
			map[k] = 0;
		}
	}
}

int clean(int *showMap, int *map, int w, int h, int x, int y, int mode)
{ // 清扫指定区块,mode = 0时开启连片扫描模式，mode = 1时开启单纯扫描模式；如果返回0，则表示没踩到雷，如果返回1，则表示踩到雷了
	if (showMap[x * w + y] == 0)
	{ // 在showMap中，1表示已经被扫开了，0表示未被扫开
		if (map[x * w + y] == 9)
		{ // 判断是该区域否是地雷
			return 1;
		}
		else if (map[x * w + y] == 0 && mode == 0)
		{									  // 判断该区块是否为0
			clean0(showMap, map, w, h, x, y); // 若该区块为0，则启动连片扫描
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
	printf("   %s\n", xIndex); // 输出列号
	int k, l;
	for (k = 0; k < mw; k++)
	{
		for (l = 0; l < mh; l++)
		{
			if (l == 0)
			{
				if (k + 1 < 10)
				{ // 控制行号的格式
					printf("  %d", k + 1);
				}
				else
				{
					printf(" %d", k + 1);
				}
			}
			if (showMap[k * mw + l] == 1)
			{ // 判断该区块是否已被挖开
				if (map[k * mw + l] == 1)
				{
					printf("壹");
				}
				else if (map[k * mw + l] == 2)
				{
					printf("贰");
				}
				else if (map[k * mw + l] == 3)
				{
					printf("叁");
				}
				else if (map[k * mw + l] == 4)
				{
					printf("肆");
				}
				else if (map[k * mw + l] == 5)
				{
					printf("伍");
				}
				else if (map[k * mw + l] == 6)
				{
					printf("陆");
				}
				else if (map[k * mw + l] == 7)
				{
					printf("柒");
				}
				else if (map[k * mw + l] == 8)
				{
					printf("捌");
				}
				else if (map[k * mw + l] == 9)
				{ // 地雷
					printf("雷");
				}
				else
				{
					printf("□");
				}
			}
			else if (showMap[k * mw + l] == 2)
			{ // 如果是旗帜
				printf("★");
			}
			else if (showMap[k * mw + l] == 3)
			{ // 如果是问号
				printf("？");
			}
			else if (showMap[k * mw + l] == 0)
			{ // 如果是未挖开的方块
				printf("■");
			}
		}
		printf("%c", '\n');
	}
}
