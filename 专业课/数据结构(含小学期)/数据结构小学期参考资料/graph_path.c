#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int vis[100];
int haspath = 0;
typedef struct ArcNode {
    int adjvex;//边指向的顶点
    struct ArcNode* nextarc; // 下一条边的指针
}ArcNode;
typedef struct VNode {
    int data;//顶点信息
    ArcNode* firstarc;//该结点的第一条边
}VNode, AdjList[MAX];
typedef struct {
    AdjList vertices;//头结点数组
    int vexnum, arcnum; // 图的当前顶点数和边数
}ALGraph;
//寻找v1，v2在G中的位置
int LocateVex(ALGraph* G, int v) {
    int i;
    for (i = 0; i <= G->vexnum; i++)
        if (G->vertices[i].data == v)
            return i;
}
//创建图
void creatGraph(ALGraph* G) {
    int i, j, k, m, n;
    ArcNode* s;
    G->vexnum = 6;
    G->arcnum = 8;
    G->vertices[0].data = 1;
    G->vertices[1].data = 2;
    G->vertices[2].data = 3;
    G->vertices[3].data = 4;
    G->vertices[4].data = 5;
    G->vertices[5].data = 6;
    for (i = 0; i < G->vexnum; i++)  //将头结点的firstarc设置为null
        G->vertices[i].firstarc = NULL;
    int a[8] = { 1,1,2,3,3,4,5,6 };
    int b[8] = { 4,2,5,5,6,2,4,6 };
    for (k = 0; k < G->arcnum; k++) 
    {
        i = a[k]; j = b[k];
        m = LocateVex(G, i); // 找到输入结点的在 数组中的索引值。直接使用i，j 会出错。因为之后的插入和查找都是使用Adjlist数组
        n = LocateVex(G, j);
        s = (ArcNode*)malloc(sizeof(ArcNode));//头插法
        s->adjvex = j;
        s->nextarc = G->vertices[m].firstarc;
        G->vertices[m].firstarc = s;
    }
}
void readGraph(ALGraph G) {//深度遍历图
    int i, j;
    ArcNode* p;
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%d V%d", i, G.vertices[i].data);
        for (p = G.vertices[i].firstarc; p; p = p->nextarc)
            printf(" ->V%d", p->adjvex);
        printf("\n");
    }
}
//求两点间是否存在路径
int existPath(int a, int b, ALGraph* G) {
    int m, n;
    m = LocateVex(G, a);
    n = LocateVex(G, b);
    vis[m] = 1;
    ArcNode* p;
    p = G->vertices[m].firstarc;
    //printf("p :%d\n",p->adjvex);
    if (m == n)
 {
        haspath = 1;
    }
    while (p) {
        if (p->adjvex == b) { // 如果p的出边等于 b  意味着找到了
            haspath = 1;
            break;
        }
        if (!vis[LocateVex(G, p->adjvex)]) // p的出边没有被访问
            existPath(p->adjvex, b, G);   // 递归调用
        p = p->nextarc;
    }
}
void print_Path(int d, int z, ALGraph* G) {//输出两点连接路径
    int m, n;
    m = LocateVex(G, d);
    n = LocateVex(G, z);
    ArcNode* p = G->vertices[m].firstarc;
    printf("\n路径为：V%d", d);
    while (p) {
        printf("->V%d", p->adjvex);
        if (p->adjvex == z)break;
        p = G->vertices[LocateVex(G, p->adjvex)].firstarc;
    }printf("\n");
}
int main() {
    ALGraph G;
    creatGraph(&G);
    //int a, b;
    //scanf("%d %d", &a, &b);
    //existPath(a, b, &G);
    print_Path(2, 1, &G);
    printf("%d", haspath);
}
