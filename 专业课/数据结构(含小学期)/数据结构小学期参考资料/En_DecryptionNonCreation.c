/*****************************
NAME:刘灿
CLASS:COMPUTER 21-4
STUDENT NUMBER:2021015442
COMPLETION TIME:2022/6/27
*****************************/
#define _CRT_SECURE_NO_WARNINGS  //vs2022需要此行代码用于屏蔽对scanf的error
#include "stdio.h"
#include "stdlib.h"

void FillText(FILE* fp, char text[]);  //将文本内容填充到字符串
void En_Decryption(char str[], int key);  //加密解密函数

int main()
{
	FILE* fp;
	char str[100];
	fp = fopen("En_Decryption.txt", "r+");
	FillText(fp, str);
	printf("This is the information before Encryption/Decryption:\n");
	puts(str);
	int key = 0;
	printf("Please input the key:");
	scanf("%d", &key);
	En_Decryption(str, key);
	printf("This is the information after Encryption/Decrypeion:\n");
	puts(str);
	rewind(fp);
	fputs(str,fp);
	fclose(fp);
	return 0;
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

void En_Decryption(char str[],int key)
{
	int p = 0;
	while (str[p] != '\0')
	{
		str[p] = key ^ str[p];
		p++;
	}
}