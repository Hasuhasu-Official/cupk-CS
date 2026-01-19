 #pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAXSIZE 3
#define MAXNODESIZE 10

//ADT
typedef struct Branch
{
    int index;
    struct Branch* next;
}branch;

typedef struct Tnode
{
    char data[MAXSIZE];
    branch* first;
}tnode;

void create(tnode tree[], char str[], int cnt)  //创建邻接表
{
    int j = 0, t = 0;
    for (int i = 0; i < cnt; i++)
    {
        j = 0;
        while (str[t] != '/')  //遇到/就开始找换行符\n，并跳转到下一行，录入下一行头节点
        {
            tree[i].data[j] = str[t];
            j++;
            t++;
        }
        tree[i].data[j] = '\0';  //为tree[i].data加入终止符
        tree[i].first = NULL;
        while (str[t] != '\n' && str[t] != EOF)  //跳转至下一行，准备录下一行的头节点
            t++;
        t++;
    }
    //头节点初始化完成，接下来将子节点连接到头结点
    t = 0;
    int size = strlen(str);
    for (int i = 0; i < cnt && t < size; i++)  //这里需要做两个限制：1.遍历字符串的指针t不能超过字符串长度 2.头结点个数有限制
    {
        while (t < size && str[t] != '/')  //先跳过头节点
            t++;
        t++;
        while (t < size && str[t] != '\n' && str[t] != '\0')
        {
            j = 0;
            char string[MAXSIZE];
            while (t < size && str[t] != '/' && str[t] != '\n')//将字符串截取出来
            {
                string[j] = str[t];
                j++;
                t++;
            }
            string[j] = '\0';  //为该截取出来的字符串添加终止符
            int target = -1;
            for (int n = 0; n < cnt; n++)
            {
                if (!strcmp(tree[n].data, string)) {
                    target = n;
                    break;
                }
            }
            branch* p = tree[i].first;
            if (p == NULL) //如果是第一次将子节点插入头结点，应该特殊处理，这里用尾插法
            {
                p = (branch*)malloc(sizeof(branch));
                p->index = target;
                p->next = NULL;
                tree[i].first = p;
            }
            else
            {
                while (p->next != NULL)  //用p定位到最后一个结点
                {
                    p = p->next;
                }
                p->next = (branch*)malloc(sizeof(branch));  //插入新的结点
                p->next->index = target;
                p->next->next = NULL;
            }
            if (t >= size || str[t] == '\n')
                break;
            t++;  //使t指向下一个单词开头 
        }
        //此时t指向\n
        t++;  //将t指向下一行第一个字符
    }
}

void dfs(int visited[], tnode tree[], int v);

void DFS1(tnode tree[])  //对邻接表进行深度优先遍历
{
    int cnt = 0;
    int visited[MAXNODESIZE];

    for (int i = 0; i < MAXNODESIZE; i++) {
        if (strlen(tree[i].data) >= 1) {
            cnt++;
        }
        else {
            break;
        }
    }
    for (int i = 0; i < cnt; i++)
        visited[i] = 0;

    for (int i = 0; i < cnt; i++) {
        if (!visited[i]) {
            //没有遍历过
            dfs(visited, tree, i);
        }
    }
}

void searchNode(tnode* p, char str[]);

void Search(tnode tree[])  //深度优先遍历(堆栈)
{
    tnode stack[MAXNODESIZE];
    int top = -1;  //栈顶指针,指向真实位置
    int x;
    tnode p;
    branch* q;
    char str[MAXSIZE];
    printf("请输入你想寻找的结点值:");
    scanf("%s", str);
    printf("请问你想从那个结点开始遍历?\n我选择:");
    scanf("%d", &x);
    p = tree[x];
    top++;
    stack[top] = p;
    while (top != -1)
    {
        //第一步:出栈一个元素，并对其访问
        p = stack[top];
        top--;
        searchNode(&p, str);
        //第二步:将该头结点的子节点全部入栈
        q = p.first;
        while (q != NULL)  //将子节点全部入栈
        {
            top++;
            stack[top] = tree[q->index];
            q = q->next;
        }
    }
}

void searchNode(tnode* p, char str[])
{
    puts(p->data);
    if (!strcmp(p->data, str))
        printf("%s结点存在!\n", str);
}

void dfs(int visited[], tnode tree[], int v) {
    tnode t = tree[v];
    puts(t.data);
    visited[v] = 1;
    for (branch* w = t.first; w != NULL; w = w->next) {
        if (!visited[w->index])
        {
            dfs(visited, tree, w->index);
        }
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

int getCount(char str[])  //获取邻接表头节点个数
{
    int cnt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
            cnt++;
    }
    return cnt + 1;
}

char* getPath(tnode tree[], int cnt)
{

    int s1 = -1, s2 = -1;
    char p1[MAXSIZE], p2[MAXSIZE];
    char result[2048] = "\0";  //初始化全部赋0
    printf("请输入起点：");
    scanf("%s", p1);
    printf("请输入终点：");
    scanf("%s", p2);
    for (int i = 0; i < cnt; i++)  //先检查所匹配的字符串是否再
    {
        if (!strcmp(tree[i].data, p1)) 
        {
            s1 = i;  //记录p1所对应的结点的位置
        }
        if (!strcmp(tree[i].data, p2))
        {
            s2 = i;  //记录p2所对应的结点的位置
        }
    }
    if (s1 == -1 || s2 == -1)  //如果两个结点不在树里面就返回null
    {
        printf("字符串匹配异常\n");
        return strcat(result, "NULL");
    }
    int path[MAXNODESIZE];
    memset(path, -1, sizeof(int) * MAXNODESIZE);
    //深度优先:用栈
    int stack[MAXNODESIZE];
    int top = -1;
    stack[++top] = s1;  //从s1开始搜索
    int pres[MAXNODESIZE];
    memset(pres, -1, sizeof(int) * MAXNODESIZE);  //初始化为-1
    //表示起始
    pres[s1] = -2;
    //栈非空
    while (top >= 0) {
        //出栈
        int pre = stack[top--];
        if (pre == s2) { break; }
        for (branch* w = tree[pre].first; w != NULL; w = w->next)
        {
                //没有访问过，入栈
                stack[++top] = w->index;
                pres[w->index] = pre;
        }
    }
    if (pres[s2] == -1) {
        return strcat(result, "NULL");
    }
    else {
        //逆序遍历回来
        int ways[MAXNODESIZE];
        top = -1;
        int s = s2;
        while (s != -2) {
            ways[++top] = s;
            s = pres[s];
        }
        for (int i = top; i >= 0; i--) {
            strcat(result, tree[ways[i]].data);
            if (i > 0) {
                strcat(result, "->");
            }
        }
        return result;
    }
}