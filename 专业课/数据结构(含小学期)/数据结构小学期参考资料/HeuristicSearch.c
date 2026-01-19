#include "HeuristicSearch.h"
int main()
{
    int cnt = 0;
    s_0 = (p_node)malloc(sizeof(node)); //初始节点
    s_g = (p_node)malloc(sizeof(node)); //目标节点
    OPEN = (p_list)malloc(sizeof(list));  // OPEN表
    CLOSE = (p_list)malloc(sizeof(list)); // CLOSE表
    SetStartAndEnd();
    init_node();
    while (OPEN->length != 0 && CLOSE->length <= MAX_NODESIZE)
    {
        p_node n = OPEN->a[0]; //把Open表的第一个节点取出放入Close表，并记该节点为n
        printf("This is the %dth step from the start\n", ++cnt);
        out_node(n);
        delete_list(OPEN);

        if (is_equal(n, s_g)) //考察节点n是否为目标节点。若是，则找到了问题的解，成功退出；亦可换成 if(w(n)==0){...}
        {
            while (n)
            {
                printf("%d Step：\n", n->d + 1);
                out_node(n);
                n = n->father;
            }
            printf("All above is how the start get to the end\n");
            break;
        }
        add_list(CLOSE, n);
        move(n); //扩展节点
        sort_list(OPEN);
    }
    if (OPEN->length == 0 || CLOSE->length > MAX_NODESIZE)
    {
        printf("\nNo reachable value！\n\n");
    }
    return 0;
}
