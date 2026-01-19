#pragma once
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#define MAXSIZE 100
double Graph[10][10];
typedef struct Node
{
	int x;  //横坐标
	int y;  //纵坐标
	double d1;  //历史欧式距离
	double d2;  //回来欧式距离
	double f;  //估值
	int ID;  //该点对应的编号
	int fatherID;  //记录该结点的父节点
}node;
node point[MAXSIZE];
int point_length = 0;
node open[MAXSIZE];
int open_length = 0;
node close[MAXSIZE];
int close_length = 0;
node start;
node end;

void init();  //对边表进行初始化
double Distance(node node1, node node2);  //计算欧式距离
void FillText(FILE* fp, char text[]);  //将文本文件内容填充到字符串中
int IsEqual(node node1, node node2);  //判断两个点是否相等
void InsertToOpen(node node1);  //插入open表
node DeleteFromOpen();  //从open表中获取顶部元素并删除该元素
void InsertToClose(node node1);  //插入close表
void OpenSort();  //将open表按估值从小到大排序
int* GetNextID(node node1);  //获取结点所连接结点的ID，返回值中res[0]用于记录有多少个连接的结点
double GetF(node node1);  //获取估值
double GetD1(node father, node son);  //获取历史距离
void UpdatePoint(char str[]);  //更新坐标点表
void UpdateGraph(char str[]);  //获取边表
node IDtoNewNode(node father, int id);  //用父结点和子节点的ID创建新的结点
void UpdateClose();  //更新close表

void init()
{
	int ID1, ID2;
	printf("Please input the ID of start point:");
	scanf("%d", &ID1);
	printf("Please input the ID of end point:");
	scanf("%d", &ID2);
	start.x = point[ID1].x;
	start.y = point[ID1].y;
	start.fatherID = -1;
	start.ID = ID1;
	end.x = point[ID2].x;
	end.y = point[ID2].y;
	end.ID = ID2;
	start.d1 = 0;
	start.d2 = Distance(start, end);
	end.d2 = 0;
	InsertToOpen(start);
}

int IsEqual(node node1, node node2)
{
	if (node1.x == node2.x && node1.y == node2.y)
		return 1;
	else
		return 0;
}

double Distance(node node1, node node2)
{
	return sqrt((node2.x - node1.x) * (node2.x - node1.x) + (node2.y - node1.y) * (node2.y - node1.y));
}

void FillText(FILE* fp, char text[])
{
	char ch;
	int length = 0;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		text[length] = ch;
		ch = fgetc(fp);
		length++;
	}
	text[length] = '\0';
}

void InsertToOpen(node node1)
{
	open[open_length++] = node1;
}

node DeleteFromOpen()
{
	node node1 = open[open_length - 1];
	open_length--;
	return node1;
}

void InsertToClose(node node1)
{
	close[close_length++] = node1;
}

void OpenSort()
{
	node tmp;
	for (int i = 0; i < open_length; i++)
		for (int j = i; j < open_length; j++)
		{
			if (open[i].f < open[j].f)  //把估值小的放到top位
			{
				tmp = open[i];
				open[i] = open[j];
				open[j] = tmp;
			}
		}
}

int* GetNextID(node node1)
{
	int* res;  //res[0]用来保存cnt
	int cnt = 0;
	int IDs[10];
	for (int i = 0; i < point_length; i++)
	{
		if (Graph[node1.ID][i] != 0 && i != node1.fatherID)
		{
			IDs[cnt] = i;
			cnt++;
		}
	}
	res = (int*)malloc(sizeof(int) * (cnt + 1));
	res[0] = cnt;
	for (int i = 1; i <= cnt; i++)
		res[i] = IDs[i - 1];
	return res;
}

double GetF(node node1)
{
	return node1.d1 + node1.d2;
}

double GetD1(node father, node son)
{
	return father.d1 + Graph[father.ID][son.ID];
}

void UpdatePoint(char str[])
{
	int coordinate[2] = { 0,0 };
	int p = 0;
	int j = 0;
	int cnt = 0;
	while (1)
	{
		if (str[p] == '\n')
		{
			p++;
			continue;
		}
		if (j == 2)
		{
			point[cnt].x = coordinate[0];
			point[cnt].y = coordinate[1];
			cnt++;
			coordinate[0] = 0;
			coordinate[1] = 0;
			j = 0;
			point_length++;
		}
		if (str[p] == '\0')
			break;
		coordinate[j] = (str[p] - '0')*314;
		j++;
		p++;
	}
}

void UpdateGraph(char str[])
{
	int coordinate[2] = { 0,0 };
	int p = 0;
	int j = 0;
	int cnt = 0;
	while (str[p] != '\0')
	{
		if (str[p] == '\n')
		{
			p++;
			continue;
		}
		if (j == 2)
		{
			Graph[coordinate[0]][coordinate[1]] = Distance(point[coordinate[0]], point[coordinate[1]])*314;
			Graph[coordinate[1]][coordinate[0]] = Distance(point[coordinate[0]], point[coordinate[1]])*314;
			coordinate[0] = 0;
			coordinate[1] = 0;
			j = 0;
			cnt++;
		}
		coordinate[j] = str[p] - '0';
		j++;
		p++;
	}
}

node IDtoNewNode(node father, int id)
{
	node node1 = point[id];
	node1.ID = id;
	node1.fatherID = father.ID;
	node1.d1 = GetD1(father, node1);
	node1.d2 = Distance(node1, end);
	node1.f = GetF(node1);
	return node1;
}

void UpdateClose()
{
	while (open_length != 0 && close_length <= MAXSIZE)
	{
		node p = DeleteFromOpen();
		if (IsEqual(p, end))  //判断是否相等
		{
			InsertToClose(p);
			int x = end.ID;
			int status = 0;
			node path[10];
			int cnt = 0;
			for (int j = 0; j < 10; j++)
			{
				if (status == 1)
					break;
				for (int i = 0; i < close_length; i++)
				{
					if (close[i].ID == x)
					{
						path[cnt] = close[i];
						cnt++;
						x = close[i].fatherID;
					}
					if (x == -1)
					{
						status = 1;
					}
				}
			}
			printf("path:%d(%d,%d)", path[cnt - 1].ID, path[cnt - 1].x, path[cnt - 1].y);
			for (int i = cnt - 2; i >= 0; i--)
			{
				printf("->%d(%d,%d)", path[i].ID, path[i].x, path[i].y);
			}
			printf("\nThe length of path is %lf\n",p.d1);
			break;
		}
		InsertToClose(p);
		int* son = GetNextID(p);  //获取结点p的子节点的ID
		for (int i = 1; i <= son[0]; i++)
		{
			node newNode = IDtoNewNode(p, son[i]);
			InsertToOpen(newNode);
		}
		OpenSort();
	}
}