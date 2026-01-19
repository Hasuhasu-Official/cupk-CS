#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "time.h"
#define X 3
#define N 8  //城市个数

int L = 1000;  //单个结点的最大迭代次数
int city_path_now[X][N];  //当前路径
int city_path_new[2 * X][N];  //新路径
double city[N][2] = { 1,3,2,4,3,1,4,2,4,5,5,3,6,2,7,3 };  //城市坐标

double Distance(double* city1, double* city2)  //计算欧式距离
{
	return sqrt((city1[0] - city2[0]) * (city1[0] - city2[0]) + (city1[1] - city2[1]) * (city1[1] - city2[1]));
}

double PathLength(int City[][N], int No)  //计算当前路径的总长度
{
	double length = 0;
	int i = 0; 
	for ( i = 0; i < N - 1; i++)
		length += Distance(city[City[No][i]], city[City[No][i + 1]]);
	length += Distance(city[City[No][0]], city[City[No][N - 1]]);
	return length;
}

void Init()  //初始化
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < N; j++)
			city_path_now[i][j] = j;
}

void change(int City[][N], int No)  //交换
{
	int point1 = -1, point2 = -1;
	while (point1 == point2)
	{
		point1 = rand() % N;
		point2 = rand() % N;
	}
	for (int i = 0; i < N; i++)
		if (City[No][i] == point1)
		{
			for (int j = i; j < N - 1; j++)
				City[No][j] = City[No][j + 1];
		}
	for (int i = 0; i < N; i++)
		if (City[No][i] == point2)
		{
			for (int j = i; j < N - 2; j++)
				City[No][j] = City[No][j + 1];
		}
	City[No][N - 2] = point1;
	City[No][N - 1] = point2;
}

void variation(int City[][N], int No)  //变异
{
	int point1 = -1, point2 = -1;
	point1 = rand() % N;
	point2 = rand() % N;
	int t;
	t = city_path_new[No][point1];
	city_path_new[No][point1] = city_path_new[No][point2];
	city_path_new[No][point2] = t;
}

int* Select(double path[])
{
	int* res = (int*)malloc(sizeof(int) * X);
	int min1 = 10000, min2 = 10000, min3 = 10000;
	for (int i = 0; i < 2 * X; i++)
	{
		if (path[i] < min1)
		{
			min1 = path[i];
			res[0] = i;
		}
	}
	for (int i = 0; i < 2 * X; i++)
	{
		if (i == res[0])
			continue;
		if (path[i] < min2)
		{
			min2 = path[i];
			res[1] = i;
		}
	}
	for (int i = 0; i < 2 * X; i++)
	{
		if (i == res[0] || i == res[1])
			continue;
		if (path[i] < min3)
		{
			min3 = path[i];
			res[2] = i;
		}
	}
	return res;
}
