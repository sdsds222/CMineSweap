#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Utils.h"

void start(int mw, int mh, int mNum);
int main(int argc, char *argv[])
{
	srand(time(NULL)); // 设置随机数种子
	while (1)
	{
	start:
		printf("\a\a");
		system("clear");
		printf("☆ C语言扫雷2021 ☆\n");
		printf("输入 1：开始游戏， 2：查看介绍， 3：退出游戏\n");
		int select = 1;
		scanf("%d", &select);
		printf("\a");
		if (select == 1)
		{ // 选择开始游戏
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("请选择游戏模式：1：简单，2：普通，3：困难，4：专家\n");
			int mode = 0;
			scanf("%d", &mode);
			printf("\a");
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("请设置地雷的数量:\n");
			select = 1; // 复位
			scanf("%d", &select);
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("游戏将在三秒后开始\n");
			sleep(1);
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("三...\n");
			printf("\a");
			sleep(1);
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("二..\n");
			printf("\a");
			sleep(1);
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("一.\n");
			printf("\a");
			sleep(1);
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("开始！\n");
			printf("\a\a");
			sleep(1);
			system("clear");
			if (mode == 1)
			{ // 选择简单模式
				start(9, 9, select);
			}
			else if (mode == 2)
			{ // 选择普通模式
				start(12, 12, select);
			}
			else if (mode == 3)
			{ // 选择困难模式
				start(20, 20, select);
			}
			else if (mode == 4)
			{ // 选择专家模式
				start(36, 36, select);
			}
		}
		else if (select == 2)
		{ // 查看介绍
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			printf("游戏简介：\n通过输入坐标来对相应位置的区块进行操作，\n用“,”隔开，输入“3,6”表示挖开第三列、第六行的区块，\n用“.”隔开，输入“3.6”表示在第三列、第六行插旗，\n用“/”隔开，输入“3/6”表示在第三列、第六行做问号标记。\n");
			printf("Cony Studio sdsds222作品，2021年10月25日。\n等待10秒返回主界面...\n");
			sleep(10);
			goto start;
		}
		else
		{ // 退出游戏
			system("clear");
			break;
		}
		printf("☆ C语言扫雷2021 ☆\n");
		printf("游戏已结束，输入 1：重新开始游戏， 2：退出游戏\n");
		select = 0;
		scanf("%d", &select);
		if (select == 1)
		{
			system("clear");
		}
		else if (select == 2)
		{
			system("clear");
			break; // 退出游戏
		}
	}
	return 0;
}

void start(int mw, int mh, int mNum)
{													 // mNum的含义为地雷的个数，创建一个9*9的扫雷游戏
	int nowTime = time(NULL);						 // 记录现在的时间
	int *map = (int *)malloc(mw * mh * sizeof(int)); // 动态创建数组
	int *showMap = (int *)malloc(mw * mh * sizeof(int));
	int i1;
	for (i1 = 0; i1 < mw * mh; i1++)
	{ // 初始化数组
		map[i1] = 0;
		showMap[i1] = 0;
	}
	while (getMineNum(map, mw, mh) < mNum)
	{								// 随机生成地雷
		int x = getRand(0, mw - 1); // 取一个0到8的随机数
		int y = getRand(0, mh - 1);
		map[x * mw + y] = 9; // 标记为地雷,9表示有地雷
	}

	int i, j;
	for (i = 0; i < mw; i++)
	{ // 填充地雷周边的数字
		for (j = 0; j < mh; j++)
		{
			if (map[i * mw + j] != 9)
			{
				int n = 0; // 用来记载地雷数
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
				{ // 判断上边是否超出范围,若未超出范围则执行判断是否有地雷的操作
					if (map[upX * mw + upY] == 9)
					{
						n++;
					}
				}
				if (downY <= mh - 1)
				{ // 判断下边是否超出范围,若未超出范围则执行判断是否有地雷的操作
					if (map[downX * mw + downY] == 9)
					{
						n++;
					}
				}
				if (rightX <= mw - 1)
				{ // 判断右边是否超出范围
					if (map[rightX * mw + rightY] == 9)
					{
						n++;
					}
				}

				if (leftX >= 0)
				{ // 判断左边是否超出范围
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
		printf("☆ C语言扫雷2021 ☆\n");
		printf("一共布置了%d个地雷\n", getMineNum(map, mw, mh));
		print(showMap, map, mw, mh);
		int p, m, num1 = 0;
		for (p = 0; p < mw; p++)
		{ // 扫描并统计所有未扫的方块的数量，如果数量等于地雷的数量，那么就判定为赢
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
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			print(showMap, map, mw, mh);
			printf("你赢了! 用时%d秒。\n等待3秒继续...\n", time(NULL) - nowTime);
			printf("\a\a\a");
			sleep(3);
			system("clear");
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
			{ // 判断该区块是否被挖开
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
			{ // 判断该区块是否被挖开
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
		{ // 判断是否踩地雷了
			int k1;
			for (k1 = 0; k1 < mw * mh; k1++)
			{
				showMap[k1] = 1;
			}
			system("clear");
			printf("☆ C语言扫雷2021 ☆\n");
			print(showMap, map, mw, mh);
			printf("你踩到地雷了，游戏结束。\n等待3秒继续...\n");
			printf("\a\a"); // SOS
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a");
			sleep(1);
			printf("\a\a\a");
			sleep(3);
			system("clear"); // 清空控制台
			break;		   // 跳出循环
		}
		system("clear"); // 清空控制台
					   // 开始下一次循环
	}
	free(map); // 释放在堆上动态创建的数组
	free(showMap);
}
