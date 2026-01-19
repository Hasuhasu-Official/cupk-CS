#include "Genetic.h"
int main()
{
	double path[X*2];
	Init();
	srand(time(NULL));
	for (int i = 0; i < L; i++)
	{
		memcpy(city_path_new[0], city_path_now, sizeof(int) * X * N);
		memcpy(city_path_new[3], city_path_now, sizeof(int) * X * N);
		for (int j = X; j < 2 * X;j++)
		{
			int point1 = rand();
			if (point1 % 3 != 0)
				change(city_path_new, j);
			else
				variation(city_path_new, j);
		}
		for (int j = 0; j < 2 * X; j++)
			path[j] = PathLength(city_path_new, j);
		int *res = Select(path);
		for (int j = 0; j < X; j++)
		{
			memcpy(city_path_now[j], city_path_new[res[j]], sizeof(int) * N);
		}
	}
	double FinalPathLength[X], Min=99999;
	int index;
	for (int i = 0; i < X; i++)
	{
		FinalPathLength[i] = PathLength(city_path_now, i);
		if (FinalPathLength[i] < Min)
		{
			Min = FinalPathLength[i];
			index = i;
		}
	}
	printf("min length:%lf\nPath:%d",FinalPathLength[index],city_path_now[index][0]);
	for (int i = 1; i < N; i++)
		printf("->%d", city_path_now[index][i]);
	return 0;
}