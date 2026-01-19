#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"
int main()
{
    FILE* fp;
    tnode tree[MAXNODESIZE];
    for (int i = 0; i < MAXNODESIZE; i++)  //对头节点全部赋\0
    {
        for (int t = 0; t < MAXSIZE; t++)
        {
            tree[i].data[t] = '\0';
        }
    }
    char str[100];
    fp = fopen("graph.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        exit(0);
    }
    FillInText(str, fp);
    fclose(fp);
    puts(str);
    create(tree, str, getCount(str));
    int cnt = getCount(str);
    char* path = getPath(tree, cnt);
    printf("%s", path);
    return 0;
}