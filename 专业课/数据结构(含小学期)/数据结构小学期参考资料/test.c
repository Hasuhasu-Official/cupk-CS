#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

#define  NAMESIZE 20

typedef char NODE[NAMESIZE];

typedef struct BROTHERNODE          //兄弟结点类型
{
    NODE node;
    int info;                    //权值
    struct BROTHERNODE* next;     //兄弟节点链接指针
} BROTHERNODE, * BROTHER, * STACK;  //重命名兄弟节点类型

typedef struct PARENTNODE        //双亲结点类型
{
    NODE node;              //双亲结点名称
    BROTHER chirdren;    //所有子节点
} PARENT;    //重命名双亲结点类型

typedef struct TREENODE      //树类型
{
    PARENT node;
    struct TREENODE* next;        //双亲结点指针指向其他双亲结点
} TREENODE, * TREE;     //重命名所有双亲结点类型，表示为树的存储结构

