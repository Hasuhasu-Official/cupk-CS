#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#define FactSize 50                    //事实的最大长度
#define STATUS int
#define TRUE 1                      //真
#define FALSE 0                     //假

typedef char FACT[FactSize];              //定义事实类型
struct FACTNODE
{
    FACT fact;                    //一个事实
    struct  FACTNODE* next;          //多个事实链接
};

typedef struct FACTNODE* FACTS;

typedef struct {
    FACTS ifs;         //多个前提
    FACTS thens;       //多个结论
} RULE;

struct RULENODE {         //规则节点类型
    RULE rule;           //一条规则
    struct RULENODE* next;      //规则链接
};

typedef struct RULENODE* RULES;   //规则库类型

FACTS AddAFact(FACTS facts, FACT newfact)           //在事实库中加入一个事实
{
    struct FACTNODE* factnode, * lastnode;   //事实节点指针
    factnode = (struct FACTNODE*)malloc(sizeof(struct FACTNODE));   //分配事实空间
    strcpy(factnode->fact, newfact);        //复制事实形成节点
    factnode->next = NULL;
    if (facts == NULL) facts = factnode;                          //若事实库为空，创建事实库
    else {
        lastnode = facts;               //事实库头指针
        while (lastnode->next != NULL) lastnode = lastnode->next;           //指针后移
        lastnode->next = factnode;                  //插入事实节点
    }
    return facts;
}

void priFacts(FACTS facts)
{
    while (facts != NULL)                 //若事实库存在
    {
        printf("%s", facts->fact);
        facts = facts->next;             //指针后移
        if (facts != NULL) printf(",");         //显示分隔符
    }
    printf("\n");
}

void CreateStr(char* factset)          //字符数组转换为多个字符串
{
    char* c = factset;          //临时字符串
    while (*c) {
        if (*c == '/') *c = '\0';    //插入字符串结束标志
        c++;
    }
    c++;
    *c = '\0';                    //多一个结束标记
}

FACTS CreateFacts(FACTS facts, char* factset)        //将若干事实加入事实库中
{
    char* p = factset;
    FACT fact;
    CreateStr(factset);                 //将字符数组转换为多个事实
    while (*p)
    {
        strcpy(fact, p);            //读取一个事实
        facts = AddAFact(facts, fact);   //将事实加入事实库中
        p += strlen(fact) + 1;              //下一个事实
    }
    return facts;
}

FACTS CreateFactBase(FACTS facts, char* filename)   //从文件中读入多个事实并加入事实库中
{
    FILE* fp;
    char factset[500];
    fp = fopen(filename, "r");               //打开文件
    fscanf(fp, "%s", factset);               //读取若干事实
    facts = CreateFacts(facts, factset);           //创建事实库
    fclose(fp);                              //关闭
    return facts;                            //获得事实库
}

FACTS ClearFactBase(FACTS facts)               //回收事实库空间
{       //问题求解结束后需要回收该空间（每个事实空间）
    struct FACTNODE* fact = facts, * p;                    //指针变量
    while (fact)                              //非空循环
    {
        p = fact;                         //暂时指针
        fact = fact->next;                    //指针前移
        free(p);                                   //回收事实空间
    }
    return NULL;                             //没有空间
}

RULE* InitRule()                        //初始化一条空规则
{
    RULE* rule;                       //指向规则的指针
    rule = (RULE*)malloc(sizeof(RULE));             //分配一条规则空间
    rule->ifs = NULL;                   //形成没有前提和结论的空规则
    rule->thens = NULL;
    return rule;
}

void AddAIf(RULE* rule, FACT newfact)       //在规则rule中增加一个前提（事实）newfact
{
    rule->ifs = AddAFact(rule->ifs, newfact);     //加入一个前提（事实）
}

void AddAThen(RULE* rule, FACT newfact)      //在规则rule中增加一个新结论（事实）newfact
{
    rule->thens = AddAFact(rule->thens, newfact);    //加入一个结论（事实）
}

void AddIfs(RULE* rule, char* factset)             //在规则中增加多个前提
{
    char* p = factset;
    FACT fact;                         //一个事实
    CreateStr(factset);                    //将字符串转化为多个前提（事实）
    while (*p)
    {
        strcpy(fact, p);         //读取一个前提（事实）
        AddAIf(rule, fact);      //加入一个前提（事实）
        p += strlen(fact) + 1;               //下一个前提（事实）
    }
}

void AddThens(RULE* rule, char* factset)             //在规则中增加多个结论
{
    char* p = factset;
    FACT fact;                         //一个事实
    CreateStr(factset);                    //将字符串转化为多个结论（事实）
    while (*p)
    {
        strcpy(fact, p);         //读取一个结论（事实）
        AddAThen(rule, fact);      //加入一个结论（事实
        p += strlen(fact) + 1;               //下一个结论（事实）
    }
}

RULE* CreateRule(char* ifset, char* thenset)  //根据字符数组ifs和thens创建一条规则
{
    RULE* rule;                         //规则指针
    rule = InitRule();             //创建空指针
    AddIfs(rule, ifset);                     //在规则rule中加入若干前提ifs
    AddThens(rule, thenset);                   //在规则rule中加入若干前提thens
    return rule;
}

RULES AddARule(RULES rules, RULE rule)     //将一条规则rule增加到规则库rules中
{
    struct RULENODE* rulenode, * lastnode;
    rulenode = (struct RULENODE*)malloc(sizeof(struct RULENODE));             //分配规则节点空间
    rulenode->rule = rule;               //在规则节点rulenode中加入规则rule
    rulenode->next = NULL;
    if (rules == NULL)                    //创建规则库rules
        rules = rulenode;
    else              //或在已有规则库中加入新规则
    {
        lastnode = rules;          //在规则节点rulenode中加入规则库rules的尾部
        while (lastnode->next != NULL)  lastnode = lastnode->next;          //lastnode指针后移
        lastnode->next = rulenode;
    }
    return rules;                   //加入到规则rule后的规则库rules中
}

RULES CreateRuleBase(RULES rules, char* filename)    //在文件中创建规则库rules
{
    RULE* rule;
    FILE* fp;
    char ifset[5000], thenset[500];          //前提与结论的字符数组
    fp = fopen(filename, "r");
    while (!feof(fp)) {
        fscanf(fp, "%s", ifset);                            //读入若干前提，注意分隔符“/”
        fscanf(fp, "%s", thenset);                            //读入若干结论，注意分隔符“/”
        rule = CreateRule(ifset + 4, thenset + 4);                //创建一条规则rule，跳过“如果”“那么”
        rules = AddARule(rules, *rule);                 //将新规则rule加入规则库rules中
    }
    fclose(fp);
    return rules;
}

void priRule(RULE* rule)                         //显示事实的一条规则rule
{
    FACTS ifs, thens;
    ifs = rule->ifs;
    thens = rule->thens;
    printf("IF ");          //显示IF
    priFacts(ifs);
    printf("THEN ");
    priFacts(thens);                 //显示所有结论thens
}


RULES ClearRuleBase(RULES rules)                   //回收规则库rules的空间
{
    struct RULENODE* rule = rules, * p;
    while (rule)                   //规则库是否为空
    {
        p = rule;                  //临时指针p
        ClearFactBase(p->rule.ifs);
        ClearFactBase(p->rule.thens);
        rule = rule->next;                   //下一条规则
        free(p);                           //回收p指向的数据空间
    }
    return NULL;
}

STATUS member(FACT fact, FACTS facts)         //成员判断
{  //若fact在事实库facts内，则返回TRUE，否则返回FALSE
    STATUS flag = FALSE;                 //默认事实不算事实库成员
    struct FACTNODE* p = facts;        //指向事实指针
    while (p) {
        if (strcmp(p->fact, fact) == 0)      //判断事实fact是否为事实库成员
        {
            flag = TRUE;
            break;
        }
        else
            p = p->next;
    }                     //下一个事实库成员
    return flag;                               //事实是否为事实库成员
}

STATUS match(FACTS subfacts, FACTS facts)        //判断若干成员
{//若若干事实subfacts均为事实库facts的成员，则返回TRUE，否则返回FALSE
    STATUS flag = TRUE;                         //默认若干事实都是事实库成员
    struct FACTNODE* p = subfacts;               //指向若干事实
    while (p) {
        if (!member(p->fact, facts))              //一个事实不算事实库成员
        {
            flag = FALSE;                //有一个事实不在事实库中
            break;
        }
        else
            p = p->next;
    }                //下一个事实
    return flag;
}

FACTS update(FACTS subfacts, FACTS facts, STATUS* flag)   //更新事实库
{ //若干事实subfacts中只有一个事实不在事实库facts中，追加该事实
    struct FACTNODE* p = subfacts;                    //若干事实指针
    *flag = FALSE;                         //默认为FALSE ，表示facts没有更新
    while (p)
        if (!member(p->fact, facts))                      //事实不在事实库中
        {
            *flag = TRUE;                            //更新facts
            facts = AddAFact(facts, p->fact);         //追加不在事实库中的事实
        }
        else
            p = p->next;                           //下一个事实
    return facts;
}

STATUS testIfs(FACTS ifs, FACTS facts)        //判断前提集合是否在事实库中
{   //若所有结论均在事实库中，则更新事实库并返回TRUE，否则返回FALSE
    return match(ifs, facts);
}

FACTS testThens(FACTS thens, FACTS facts, STATUS* flag)      //判断结论集合
{  //若所有结论均在事实库中，则更新事实库，返回TRUE，否则返回FALSE
    facts = update(thens, facts, flag);                //更新事实库
    return facts;
}

FACTS testRule(RULE* rule, FACTS facts, STATUS* flag)        //判断规则是否有效
{  //若规则rule前提均在事实库facts中，并且rule至少有一个结论不在事实库中
    //更新事实库并返回TRUE，否则不更新事实库并返回FALSE
    *flag = FALSE;
    if (testIfs(rule->ifs, facts))                         //规则有效性
        facts = testThens(rule->thens, facts, flag);   //更新事实库
    return facts;
}

FACTS stepforward(RULES rules, FACTS facts, STATUS* flag)     //进行一步搜索
{//若规则树中有一条规则满足，则执行一步搜索，更新事实库，返回TRUE
    //否则没有更新事实库，返回FALSE
    do {
        facts = testRule(&(rules->rule), facts, flag);        //若有一条规则有效，则更新事实库
        if (*flag == TRUE)                           //判断更新事实库是否成功
        {
            priRule(&(rules->rule));                          //显示用到的规则
            printf("===========================\n");
            break;
        }
        rules = rules->next;                             //下一条规则
    } while (rules);
    return facts;                                    //得到更新的事实库或没有更新的事实库
}

FACTS deducegui(RULES rules, FACTS facts, STATUS* flag)  //反复持续搜索
{
    static STATUS success = FALSE;              //默认将反复持续搜索的状态设为失败
    facts = stepforward(rules, facts, flag);     //单步搜索
    if (*flag == TRUE)
    {
        success = TRUE;                      //至少进行一次单步搜索
        facts = deducegui(rules, facts, flag);
    }
    *flag = success;
    return facts;
}

struct FACTNODE* deduceResult(FACTS facts)   //获得结论
{ //从更新的事实库中获得最后事实指针
    while (facts->next) facts = facts->next;          //指针后移
    return facts;                       //获得最后事实指针
}

void displayResult(struct  FACTNODE* result, STATUS flag)    //显示搜索结论
{ //若持续搜索成功，则显示最后事实，否则显示搜索不成功信息
    if (flag == TRUE) printf("DeduceResult=%s\n", result->fact);       //搜索成功显示结果
    else printf("DeduceResult=NO Result\n");
    printf("=================================\n");
}

void ProductionSYS(char* rulefilename, char* factfilename)        //集成完整问题求解系统
{ //事实和规则分别在factfilename、rulefilename两个文本文件中
    RULES rules = NULL;                   //规则树为空
    FACTS facts = NULL;                            //事实库为空
    struct FACTNODE* result = NULL;                //求解结果（事实）
    STATUS flag;                   //求解是否成功
    facts = CreateFactBase(facts, factfilename);   //从文件中读取事实，创建事实库
    printf("=======================================\nFact Base:\n");
    priFacts(facts);
    printf("=======================================\nDeducing Procedure:\n");
    rules = CreateRuleBase(rules, rulefilename);   //从文件中读取事实，创建事实库
    facts = deducegui(rules, facts, &flag);                       //文件求解
    result = deduceResult(facts);                   //获得求解结果
    displayResult(result, flag);                    //显示求解结果
    ClearFactBase(facts);                           //回收事实库空间
    ClearRuleBase(rules);                            //回收规则库空间
}

int main()
{
    char* factfilename = "factbase.txt";
    char* rulefilename = "rulebase.txt";
    ProductionSYS(rulefilename, factfilename);
    return 0;
}