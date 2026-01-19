#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "time.h"
#define N 8  //城市个数

int L = 1000;  //单个结点的最大迭代次数
int city_path_now[N];  //当前路径
int city_path_new[N];  //新路径
double city[N][2] = { 1,3,2,4,3,1,4,2,4,5,5,3,6,2,7,3 };  //城市坐标
int cnt = 0;

double Distance(double* city1, double* city2)  //计算欧式距离
{
	return sqrt((city1[0] - city2[0]) * (city1[0] - city2[0]) + (city1[1] - city2[1]) * (city1[1] - city2[1]));
}

double PathLength(int City[])  //计算当前路径的总长度
{
	double length = 0;
	for (int i = 0; i < N - 1; i++)
		length += Distance(city[City[i]], city[City[i + 1]]);
	length += Distance(city[City[0]], city[City[N - 1]]);
	return length;
}

void CreateNewPath()
{
	memcpy(city_path_new, city_path_now, N * sizeof(int));
	int point1, point2;
	point1 = rand() % N;
	point2 = rand() % N;
	int t;
	t = city_path_new[point1];
	city_path_new[point1] = city_path_new[point2];
	city_path_new[point2] = t;
}

void init()
{
	for (int i = 0; i < N; i++)
	{
		city_path_now[i] = i;
	}
}

int main()
{
	double path1;
	double path2;
	double dE;
	init();
	srand(time(NULL));
	for (int i = 0; i < L; i++)
	{
		CreateNewPath();
		path1 = PathLength(city_path_new);
		path2 = PathLength(city_path_now);
		dE = path2 - path1;  //求出路径长度差(能量差)
		if (dE > 0)
		{
				memcpy(city_path_now, city_path_new, N * sizeof(int));
		}
	}
	printf("Path:");
	for (int i = 0; i < N; i++)
	{
		printf("%d->", city_path_now[i]);
	}
	printf("%d\n", city_path_now[0]);
	printf("Total Distance:%5lf", PathLength(city_path_now));
	return 0;
}