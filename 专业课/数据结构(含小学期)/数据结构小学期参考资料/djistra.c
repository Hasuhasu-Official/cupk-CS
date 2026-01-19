#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAXSIZE 100
#define INF 999
int Mgraph[MAXSIZE][MAXSIZE];  //邻接矩阵存储顶点信息于边的权值
int n;  //存储顶点个数
int dist[MAXSIZE];
int set[MAXSIZE];
int path[MAXSIZE];
void Djistra(int start)
{
	int min, v;
	for (int i = 1; i <= n; i++)
	{
		dist[i] = Mgraph[start][i];
		set[i] = 0;
		if (Mgraph[start][i] < INF)
			path[i] = start;
		else
			path[i] = -1;
	}
	set[start] = 1;
	path[start] = -1;
	for (int i = 1; i <= n - 1; i++)  //对表一共进行n-1次更新
	{
		min = INF;
		for (int j = 1; j <= n; j++)
		{
			if (set[j] == 0 && dist[j] < min)
			{
				v = j;  //选出相邻的最短的路径对应的结点
				min = dist[j];
			}
		}
		set[v] = 1;
		for (int j = 1; j <= n; j++) //以v为起点，对dist和path表进行更新
		{
			if (set[j] == 0 && (dist[v] + Mgraph[v][j] < dist[j]))
			{
				dist[j] = dist[v] + Mgraph[v][j];
				path[j] = v;
			}
		}
	}
}

void showPath(int end)
{
	int p = end;
	int sum = 0;
	int ShowPath[MAXSIZE];
	int cnt = 0;
	while (p != -1)
	{
		ShowPath[cnt] = p;
		p = path[p];
		cnt++;
	}
	for (int i = 0; i <= (cnt - 1) / 2; i++)
	{
		int t = ShowPath[i];
		ShowPath[i] = ShowPath[cnt - i-1];
		ShowPath[cnt - i - 1] = t;
	}
	printf("路径为:%d", ShowPath[0]);
	for (int i = 1; i < cnt; i++)
		printf("->%d", ShowPath[i]);
	printf("\n");
}

int getFare(int end, int FoodPrice[])
{
	int p = end;
	int sum = 0;
	int ShowPath[MAXSIZE];
	int cnt = 0;
	while (p != -1)
	{
		ShowPath[cnt] = p;
		p = path[p];
		cnt++;
	}
	for (int i = 0; i <= (cnt - 1) / 2; i++)  //将路径逆序为start到end
	{
		int t = ShowPath[i];
		ShowPath[i] = ShowPath[cnt - i - 1];
		ShowPath[cnt - i - 1] = t;
	}
	for (int i = 0; i < cnt - 1; )  //cnt个结点共有cnt-1条路
	{
		//检查自己这一站的路费比后面的多少站的路费要便宜
		int cheaper = 1;
		for (int j = i + 1; j < cnt - 1; j++)  //最后一站不需要买食物，所以这里是cnt-1
		{
			if (FoodPrice[ShowPath[i]] > FoodPrice[ShowPath[j]])  //一直比较到有一站更便宜就停止
				break;
			cheaper++;
		}
		int j = i;
		for (int t = 0; t < cheaper; t++)
		{
			sum += Mgraph[ShowPath[j]][ShowPath[j + 1]] * FoodPrice[ShowPath[i]];
			j++;
		}
		i += cheaper;
	}
	return sum;
}

int main()
{
	int fare[10];
	int m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n+1; i++)
		for (int j = 0; j < n+1; j++)
			Mgraph[i][j] = INF;
	int foodPrice[MAXSIZE];
	for (int i = 1; i <= n; i++)
		scanf("%d", &foodPrice[i]);
	int city1, city2, length;
	for (int i = 1; i <= n - 1; i++)
	{
		scanf("%d %d %d", &city1, &city2, &length);
		Mgraph[city1][city2] = length;
		Mgraph[city2][city1] = length;
	}
	int start, end;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &start, &end);
		Djistra(start);
		fare[i] = getFare(end,foodPrice);
	}
	for (int i = 0; i < m; i++)
		printf("%d\n", fare[i]);
	return 0;
}