#include "HTDecoding.h"


void HTDecode(char* binString, HuffmanTree* tree)
{
    int len = strlen(binString), ch = 0, i = tree->length - 1;
    HuffmanTree* tmp = tree;

    printf("解码:");
    while (*binString != '\0')
    {
        while (tmp->node[i].lChildPos != -1)
        {
            if (*binString == '0')
            {
                i = tmp->node[i].lChildPos;
            }
            else if (*binString == '1')
            {
                i = tmp->node[i].rChildPos;
            }
            binString++;
        }
        putchar(tmp->node[i].data->ch);
        i = tree->length - 1;
    }
    printf("\n");
}

static char tmpStr[100];   //全部初始化为0
static int tmpStrPos = -1; //由于函数需要递归调用，因为tmpStrPos必须用static修饰
void HTPrint(HuffmanTree* tree, int nodeNum)
{
    int tmpPos = tmpStrPos;
    if (nodeNum != -1)  //字符串必须有长度
    {
        if (tree->node[nodeNum].lChildPos == -1)  //只打印叶子节点
        {
            tmpStr[tmpStrPos + 1] = '\0'; //增加终止符
            printf("char: %c\tcoding:%-20s\tweight:%d\n", 
                tree->node[nodeNum].data->ch, tmpStr, tree->node[nodeNum].data->weight);
            return;
        }
        tmpStrPos++;
        tmpStr[tmpStrPos] = '0';
        HTPrint(tree, tree->node[nodeNum].lChildPos);  //递归调用该函数
        tmpStrPos = tmpPos + 1;
        tmpStr[tmpStrPos] = '1';
        HTPrint(tree, tree->node[nodeNum].rChildPos);
    }
}
