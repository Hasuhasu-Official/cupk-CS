#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef int state[9];
state st[3628800], goal;  //用于存储状态
int dist[3628800] = { 0 };  //距离数组
int father[3628800];
const int dx[4] = { -1,1,0,0 };//上下左右移的操作
const int dy[4] = { 0,0,-1,1 };
int head[1000003], next[1000003];
int cnt = 0;
void init_lookup_table()
{
	memset(head, 0, sizeof(head));
}
int hash(state p)  //hash散列
{
	int v = 0;
	for (int i = 0; i < 9; i++)
		v = v * 10 + p[i];
	return v % 1000003;
}
int try_to_insert(int s)
{
	int h = hash(st[s]);
	int u = head[h];
	while (u)
	{
		if (memcmp(st[u], st[s], sizeof(st[s])))
			return 0;
		u = next[u];
	}
	next[s] = head[h];
	head[h] = s;
	return 1;
}
int BFS()
{
	init_lookup_table();
	int front = 1;  //st[0]不用
	int rear = 2;
	while (front < rear)
	{
		int* p = st[front];
		int z = 0;
		while (z < 9)  //找到z在一位数组中的下标位置
		{
			if (!p[z])
				break;
			z++;
		}
		int x = z / 3, y = z % 3;  //获取0在二维数组中的下标位置
		for (int d = 0; d < 4; d++)  //算出0在新的二维数组中的位置
		{
			int newx = x + dx[d];
			int newy = y + dy[d];
			int newz = newx * 3 + newy;  //算出0在新的一维数组中的位置
			if ((newx >= 0 && newx < 3) && (newy >= 0 && newy < 3))  //判断0在新的二维数组中的位置是否合法
			{
				int* t = st[rear];
				memcpy(t, p, 9 * sizeof(int));  //将图拷贝到新的位置
				t[newz] = p[z];  //改变0的位置
				t[z] = p[newz];
				dist[rear] = dist[front] + 1;  //记录新状态相较初始位置移动的步数
				father[rear] = front;
				if (try_to_insert(rear))
				{
					rear++;
					cnt++;
					printf("-------------------------\n");
					printf("%d %d %d\t\t\t|\n", t[0], t[1], t[2]);
					printf("%d %d %d\t\t\t|\n", t[3], t[4], t[5]);
					printf("%d %d %d\t\t\t|\n", t[6], t[7], t[8]);
					printf("It has been %d steps\t|\n", cnt);
					printf("-------------------------\n\n");
					if (memcmp(goal, t, 9 * sizeof(int)) == 0)  //判断是否和目标状态重合
						return front + 1;
				}
			}
		}
		front++;
	}
}