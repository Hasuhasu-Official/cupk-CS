#ifndef __HT_H
#define __HT_H

#include "stdio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//ADT
typedef struct
{
    char ch;
    int weight;
}NodeData;

typedef struct      //定义树结点
{
    NodeData* data;
    int parent;
    int lChildPos;
    int rChildPos;
}Treenode;

typedef struct  //定义huffmantree，用数组表示树
{
    Treenode* node;
    int length;
}HuffmanTree;

static void HTStore(HuffmanTree* tree, int nodeNum); //存储哈夫曼树
NodeData* HTDataInit(char* string, int* weight);  
HuffmanTree* HTInit(NodeData* data, int len);
int* SelectMin(HuffmanTree* tree);  //选择两个权值最小的结点
void HTCreate(HuffmanTree* tree);  //建哈夫曼树
char* HTEncode(char* string, HuffmanTree* tree);  //用哈夫曼树对字符串进行编码
void FillInText(char str[], FILE* fp);  //获取文件中的字符串
#endif  // !__HT_H

