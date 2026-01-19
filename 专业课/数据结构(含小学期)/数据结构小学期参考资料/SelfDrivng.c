#define _CRT_SECURE_NO_WARNINGS
#include "SelfDriving.h"
int main()
{
	FILE* fp1, *fp2;
	char coordinate[100],relationship[100];
	fp1 = fopen("coordinate.txt","r");
	fp2 = fopen("relationship.txt", "r");
	FillText(fp1,coordinate);
	FillText(fp2, relationship);
	UpdatePoint(coordinate);
	UpdateGraph(relationship);
	init();
	UpdateClose();
	return 0;
}