/*****************************
NAME:ÍõÒ«»Ô 
CLASS:COMPUTER 22-6
STUDENT NUMBER:2022015587
COMPLETION TIME:2022/6/27
*****************************/

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

void FillText(FILE* fp, char text[]);
void En_Decryption(char str[], int key);

int main()
{
	FILE* fp1,* fp2;
	char str[100];
	fp1 = fopen("En_Decryption.txt", "r+");
	FillText(fp1, str);
	printf("This is the information before Encryption/Decryption:\n");
	puts(str);
	int p = 0;
	int key = 0;
	printf("Please input the key:");
	scanf("%d", &key);
	En_Decryption(str, key);
	printf("This is the information after Encryption/Decrypeion:\n");
	puts(str);
	fclose(fp1);
	fp2 = fopen("I_am_a_new_file.txt", "w+");
	fputs(str, fp2);
	fclose(fp2);
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

void En_Decryption(char str[], int key)
{
	int p = 0;
	while (str[p] != '\0')
	{
		str[p] = key ^ str[p];
		p++;
	}
}
