#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAXSIZE 50
typedef struct RULE
{
	int ifs;
	int result;
}rule;
rule rules[MAXSIZE];
int rulesLength = 0;
char facts[MAXSIZE][20];
int factsLength = 0;

void factsAdd()
{
	char newrule[20];
	printf("please input a fact name:");
	scanf("%s", newrule);
	strcpy(facts[factsLength], newrule);
	factsLength++;
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

void factsBuild(char str[])
{
	int p = 0, j;
	while (str[p] != '\0')
	{
		j = 0;
		while (str[p] != '\n')
		{
			facts[factsLength][j] = str[p];
			p++;
			j++;
		}
		facts[factsLength][j] = '\0';
		factsLength++;
		printf("%d\t", factsLength);
		p++;
	}
	for (int i = 0; i < factsLength-2; i++)
		puts(facts[i]);
}

int main()
{
	char str[1000];
	FILE* fp;
	fp = fopen("facts.txt", "r");
	FillText(fp, str);
	factsBuild(str);
	return 0;
}