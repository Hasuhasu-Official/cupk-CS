#include "AimlessSearch.h"
int main()
{
	char start[10],end[10];
	printf("NOTICE:one dimmensional array 123456780 stands for:\n\t\t1 2 3\n\t\t4 5 6\n\t\t7 8 0\n");
	printf("Please input the start status by one dimmensional array:");
	scanf("%s", start);
	for (int i = 0; i < 9; i++)  //读取初始状态
		st[1][i] = start[i] - '0';
	printf("Please input the end status by one dimmensional array:");
	scanf("%s", end);
	for (int i = 0; i < 9; i++)  //读取初始状态
		goal[i] = end[i] - '0';
	int ans = BFS();  //获取目标状态的下标
	printf("\n");
	if (ans > 0)
		printf("It takes at least %d steps to reach the target\n", dist[ans]);  //输出目标状态到初始状态的距离
	else
		printf("can't reach\n");
	return 0;
}