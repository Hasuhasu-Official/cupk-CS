#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODESIZE 999999
#define N 3
//ADT
typedef struct node
{
    int a[N][N];  //结点状态
    int i_0, j_0;  //空格的位置
    int d, w, f; //搜索深度，各棋子不在正确位置的数目，总代价
    struct node* father;  //指向父节点指针
} node, * p_node;

typedef struct list
{
    p_node a[MAX_NODESIZE];
    long length;
} list, * p_list;

static int s0[N][N]; //初始结点
static int sg[N][N]; //目标结点

p_node s_0 = NULL;  //初始节点
p_node s_g = NULL;  //目标节点

p_list OPEN = NULL;  // OPEN表
p_list CLOSE = NULL;  // CLOSE表

int w(p_node s);                      //启发函数，再次设置为曼哈顿距离
int f(p_node s);                      //估价函数
void init_node();                     //初始化
void out_node(p_node s);              //输出八数码
void out_list(p_list l);              //输出OPEN表
bool search_list(p_list l, p_node s); //对表进行查找，成功返回true
void sort_list(p_list l);             //对OPEN表进行排序（按f从小到大）
void add_list(p_list l, p_node s);    //加入结点到OPEN表中或CLOSE表中
void copy_node(p_node s1, p_node s2); //生成新的结点（将s2赋值给s1）
void delete_list(p_list l);           //从OPEN表或CLOSE中删除结点
bool is_equal(p_node s1, p_node s2);  //判断两节点是否相等
bool up_mov(p_node s);                //空格上移
bool down_mov(p_node s);              //空格下移
bool left_mov(p_node s);              //空格左移
bool right_mov(p_node s);             //空格右移
void move(p_node s);                  //移动父节点并加入未探索表中（扩展结点）
int find_i(int a);
int find_j(int a);
void SetStartAndEnd();                //设置初始结点和目标结点

void SetStartAndEnd()
{
    char start[10], end[10];
    printf("NOTICE:one dimmensional array 123456780 stands for:\n\t\t1 2 3\n\t\t4 5 6\n\t\t7 8 0\n");
    printf("Please input the start status by one dimmensional array:");
    scanf("%s", start);
    printf("Please input the end status by one dimmensional array:");
    scanf("%s", end);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            s0[i][j] = start[i * N + j] - '0';
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sg[i][j] = end[i * N + j] - '0';
}

int w(p_node s)
{
    int r = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            r += abs(i - find_i(s->a[i][j])) + abs(j - find_j(s->a[i][j]));
        }
    }
    return r;
}

int f(p_node s)
{
    return (s->d + s->w);
}

void init_node()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s_0->a[i][j] = s0[i][j];

            if (s_0->a[i][j] == 0)
            {
                s_0->i_0 = i;
                s_0->j_0 = j;
            }
        }
    }
    s_0->d = 0;
    s_0->w = w(s_0);
    s_0->f = f(s_0);
    s_0->father = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s_g->a[i][j] = sg[i][j];
            if (s_g->a[i][j] == 0)
            {
                s_g->i_0 = i;
                s_g->j_0 = j;
            }
        }
    }
    s_g->d = 0;
    s_g->w = w(s_g);
    s_g->f = f(s_g);
    OPEN->length = 0;
    CLOSE->length = 0;
    add_list(OPEN, s_0); //初始节点加入OPEN表中
    printf("start status：\n"); //打印初始节点
    out_node(s_0);
    printf("target status：\n"); //打印目标节点
    out_node(s_g);
}

void out_node(p_node s)
{
    printf("-------------------\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%5d", s->a[i][j]);
        }

        printf("\n");
    }
    printf("-------------------");
    printf(" d=%d,w=%d;  f=%d\n\n\n", s->d, s->w, s->f);
}

void out_list(p_list l)
{
    printf("****************************************************************\n");
    for (int i = 0; i < l->length; i++)
    {
        out_node(l->a[i]);
    }
    printf("****************************************************************\n");
}

bool search_list(p_list l, p_node s)
{
    for (int i = 0; i < l->length; i++)
    {
        if (is_equal(l->a[i], s))
            return true;
    }
    return false;
}

void sort_list(p_list l)
{
    p_node temp = (p_node)malloc(sizeof(node));

    for (int i = 1; i < l->length; i++)
    {
        int j = i - 1;
        copy_node(temp, l->a[i]);
        while (j >= 0 && (temp->f < l->a[j]->f))
        {
            copy_node(l->a[j + 1], l->a[j]);
            j--;
        }
        copy_node(l->a[j + 1], temp);
    }
}

void add_list(p_list l, p_node s)
{
    l->a[l->length++] = s;
}

void copy_node(p_node s1, p_node s2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s1->a[i][j] = s2->a[i][j];
        }
    }
    s1->i_0 = s2->i_0;
    s1->j_0 = s2->j_0;
    s1->d = s2->d;
    s1->w = s2->w;
    s1->f = s2->f;
    s1->father = s2->father;
}

void delete_list(p_list l)
{
    for (int i = 0; i < l->length; i++)
    {
        l->a[i] = l->a[i + 1];
    }
    l->length--;
}

bool is_equal(p_node s1, p_node s2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (s1->a[i][j] != s2->a[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool left_mov(p_node s)
{
    if (s->j_0 == 0)
        return false;
    int temp;
    temp = s->a[s->i_0][s->j_0];
    s->a[s->i_0][s->j_0] = s->a[s->i_0][s->j_0 - 1];
    s->a[s->i_0][s->j_0 - 1] = temp;

    s->j_0--;
    return true;
}

bool right_mov(p_node s)
{
    if (s->j_0 == N - 1)
        return false;

    int temp;
    temp = s->a[s->i_0][s->j_0];
    s->a[s->i_0][s->j_0] = s->a[s->i_0][s->j_0 + 1];
    s->a[s->i_0][s->j_0 + 1] = temp;

    s->j_0++;
    return true;
}

bool up_mov(p_node s)
{
    if (s->i_0 == 0)
        return false;

    int temp;
    temp = s->a[s->i_0][s->j_0];
    s->a[s->i_0][s->j_0] = s->a[s->i_0 - 1][s->j_0];
    s->a[s->i_0 - 1][s->j_0] = temp;

    s->i_0--;
    return true;
}

bool down_mov(p_node s)
{
    if (s->i_0 == N - 1)
        return false;

    int temp;
    temp = s->a[s->i_0][s->j_0];
    s->a[s->i_0][s->j_0] = s->a[s->i_0 + 1][s->j_0];
    s->a[s->i_0 + 1][s->j_0] = temp;

    s->i_0++;
    return true;
}

void move(p_node s)
{
    p_node p1 = (p_node)malloc(sizeof(node));
    p_node p2 = (p_node)malloc(sizeof(node));
    p_node p3 = (p_node)malloc(sizeof(node));
    p_node p4 = (p_node)malloc(sizeof(node));

    copy_node(p1, s);
    copy_node(p2, s);
    copy_node(p3, s);
    copy_node(p4, s);

    p1->father = s;
    p2->father = s;
    p3->father = s;
    p4->father = s;
    if (left_mov(p1) && !is_equal(p1, p1->father) && !search_list(CLOSE, p1) && !search_list(OPEN, p1))
    {
        add_list(OPEN, p1);
        p1->d++;
        p1->w = w(p1);
        p1->f = f(p1);
    }
    else
        free(p1);

    if (right_mov(p2) && !is_equal(p2, p2->father) && !search_list(CLOSE, p2) && !search_list(OPEN, p2))
    {
        add_list(OPEN, p2);
        p2->d++;
        p2->w = w(p2);
        p2->f = f(p2);
    }
    else
        free(p2);

    if (up_mov(p3) && !is_equal(p3, p3->father) && !search_list(CLOSE, p3) && !search_list(OPEN, p3))
    {
        add_list(OPEN, p3);
        p3->d++;
        p3->w = w(p3);
        p3->f = f(p3);
    }
    else
        free(p3);

    if (down_mov(p4) && !is_equal(p4, p4->father) && !search_list(CLOSE, p4) && !search_list(OPEN, p4))
    {
        add_list(OPEN, p4);
        p4->d++;
        p4->w = w(p4);
        p4->f = f(p4);
    }
    else
        free(p4);
}

int find_i(int a)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (sg[i][j] == a)
                return i;
        }
    }
    return 0;
}

int find_j(int a)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (sg[i][j] == a)
                return j;
        }
    }
    return 0;
}