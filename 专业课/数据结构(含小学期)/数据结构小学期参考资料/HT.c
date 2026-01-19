#include "HT.h"
#pragma warning(disable:4996)


NodeData* HTDataInit(char* string, int* weight)
{
    int len = strlen(string), j = 0, count = 0;
    NodeData* res = calloc(len, sizeof(NodeData));
    char* tmp = malloc(len + 1);
    memcpy(tmp, string, len + 1);   //tmp = string

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (res[j].ch == string[i])
            {
                res[j].weight++;
                break;
            }
            else if (res[j].ch == '\0')
            {
                count++;
                string[j] = string[i];
                res[j].ch = string[i];
                res[j].weight++;
                break;
            }
        }
    }
    memset(string + count, 0, strlen(string) - count);
    return res;
}

HuffmanTree* HTInit(NodeData* data, int len)
{
    HuffmanTree* resTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));

    resTree->node = (Treenode*)malloc(sizeof(Treenode) * (2 * len - 1));  //对于n个叶子结点，哈夫曼树一共有2n+1个结点
    
    resTree->length = len;  //下标0-len-1的地方存叶子节点，先进行初始化
    for (int i = 0; i < len; i++)
    {
        resTree->node[i].data = malloc(sizeof(NodeData));
        resTree->node[i].data->ch = data[i].ch;
        resTree->node[i].data->weight = data[i].weight;
        resTree->node[i].parent = 0;
        resTree->node[i].lChildPos = -1;
        resTree->node[i].rChildPos = -1;
    }
    return resTree;
}

int* SelectMin(HuffmanTree* tree)
{
    int min = 10000, secmin = 10000, minIndex = -1, secminIndex = -1;
    for (int i = 0; i < tree->length; i++)  //找到最小的结点的索引下标
    {
        if (tree->node[i].parent == 0)  //必须是没有和其他结点组合过的结点
        {
            if (tree->node[i].data->weight < min)
            {
                min = tree->node[i].data->weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < tree->length; i++)  //找到第二小的结点的索引下标
    {
        if (tree->node[i].parent == 0 && i != minIndex)  //不能跟第一个结点重合
        {
            if (tree->node[i].data->weight < secmin)
            {
                secmin = tree->node[i].data->weight;
                secminIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int) * 2);  //返回两个数据，用int数组返回
    res[0] = minIndex;
    res[1] = secminIndex;
    return res;
}

void HTCreate(HuffmanTree* tree)
{
    int len = tree->length, res[2] = { 0 }, end = len * 2 - 1;//一个叶子结点为n的树一共有2n-1个结点

    for (int i = len; i < end; i++)
    {
        memcpy(res, SelectMin(tree), 2 * sizeof(int));  //选择两个权值最小的结点进行组合
        tree->node[i].data = malloc(sizeof(NodeData));
        tree->node[i].data->weight = tree->node[res[0]].data->weight + tree->node[res[1]].data->weight;
        tree->node[res[0]].parent = i;  //为参与组合的结点设置双亲结点
        tree->node[res[1]].parent = i;
        tree->node[i].parent = 0;   //新生成的结点没有双亲
        tree->node[i].lChildPos = res[0];  //为新生成的结点设置左右孩子
        tree->node[i].rChildPos = res[1];
        tree->length++;
    }
}

static char storage[100][100] = { 0 };   //一开始全部赋0
static char tempStr[100] = { 0 };
static int storagePos[2] = { 0,-1 }; //[0]char position  [1]encoding position

char* HTEncode(char* string, HuffmanTree* tree)
{
    int len = strlen(string);
    char* res = calloc(len * 20, sizeof(char));//malloc a large memory space in case of overflowing

    HTStore(tree, tree->length - 1);
    for (int i = 0; i < len + 1; i++)
    {
        for (int j = 0; j < storagePos[0]; j++)
        {
            if (storage[j][0] == string[i])
            {
                strcat(res, storage[j] + 2);//skip the first 2 characters ( ch and space ' ')
            }
        }
    }
    return res;
}

/**
 *  @brief  存储哈夫曼树数据信息
 */
static void HTStore(HuffmanTree* tree, int nodeNum)
{
    int tmpPos = storagePos[1];
    if (nodeNum != -1)
    {
        if (tree->node[nodeNum].lChildPos == -1)
        {
            tempStr[storagePos[1] + 1] = '\0'; //truncate
            sprintf(storage[storagePos[0]++], "%c %s", tree->node[nodeNum].data->ch, tempStr);
            return;
        }
        tempStr[++storagePos[1]] = '0';
        HTStore(tree, tree->node[nodeNum].lChildPos);
        storagePos[1] = tmpPos + 1;
        tempStr[storagePos[1]] = '1';
        HTStore(tree, tree->node[nodeNum].rChildPos);
    }
}

void FillInText(char str[], FILE* fp)  //将文件中内容传入str中
{
    char ch;
    int length = 0;
    ch = fgetc(fp);
    while (ch != EOF)
    {
        str[length] = ch;
        ch = fgetc(fp);
        length++;
    }
    str[length] = '\0';
}