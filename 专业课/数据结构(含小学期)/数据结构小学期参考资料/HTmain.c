#include "HT.h"
#include "HTDecoding.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#pragma warning(disable:4996)
//#define __DEBUG_MODE

int main()
{
    char* testStr = malloc(1000), * tmpStr = calloc(1000, sizeof(char));
    int weight[0xff] = { 0 };
    char ch;
    FILE* fp = fopen("coding.txt", "r+");
    if (fp == NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    FillInText(testStr, fp);
    strcpy(tmpStr, testStr);

    NodeData* data = HTDataInit(testStr, weight);  //获取每个字符所对应的出现次数，即权重
    HuffmanTree* Tree = HTInit(data,strlen(testStr));
    HTCreate(Tree);
    HTPrint(Tree, 2 * strlen(testStr) - 2);//打印各字符对应的哈夫曼树编码和权重
    //编码部分
    char* encodingStr =  HTEncode(tmpStr, Tree);
    printf("编码:%s\n", encodingStr);
    rewind(fp);
    fwrite(encodingStr, sizeof(char), strlen(encodingStr), fp);
    fclose(fp);
    //解码部分
    memset(encodingStr, 0, strlen(encodingStr));
    fp = fopen("coding.txt", "r");
    fscanf(fp, "%s", encodingStr);
    HTDecode(encodingStr, Tree);
    fclose(fp);
    return 0;
}