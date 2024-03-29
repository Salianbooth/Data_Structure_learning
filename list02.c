//
// Created by 陈中超 on 2024/3/28.
//
#include<stdio.h>
#include<stdlib.h>

struct PolyNode
{
    int coef;
    int expon;
    struct PolyNode* Link;
};//结构体构建多项式项的架构
struct PolyNode* Init_Polynomial1()  //初始化第一个多项式
{
    struct PolyNode* header = (struct PolyNode*)malloc(sizeof(struct PolyNode));
    struct PolyNode* pRear = header;
    header->coef = 0;
    header->expon = 0;
    header->Link = NULL;
    int coef = 0;
    int expon = 0;
    while (1)
    {
        scanf_s("%d", &coef);
        if (coef == 0)
        {
            break;
        }
        scanf_s("%d", &expon);
        struct PolyNode* NewNode = (struct PolyNode*)malloc(sizeof(struct PolyNode));
        NewNode->coef = coef;
        NewNode->expon = expon;
        NewNode->Link = NULL;
        pRear->Link = NewNode;
        pRear = NewNode;
    }
    return header;
}
struct PolyNode* Init_Polynomial2()  //初始化第二个多项式
{
    struct PolyNode* header =(struct PolyNode*) malloc(sizeof(struct PolyNode));
    struct PolyNode* pRear = header;
    header->coef = 0;
    header->expon = 0;
    header->Link = NULL;
    int coef = 0;
    int expon = 0;
    while (1)
    {
        scanf_s("%d", &coef);
        if (coef == 0)
        {
            break;
        }
        scanf_s("%d", &expon);
        struct PolyNode* NewNode =(struct PolyNode*) malloc(sizeof(struct PolyNode));
        NewNode->coef = coef;
        NewNode->expon = expon;
        NewNode->Link = NULL;
        pRear->Link = NewNode;
        pRear = NewNode;
    }
    return header;
}
void Foreach_Polynomial(struct PolyNode* header)
{
    struct PolyNode* pCurrent =(struct PolyNode*) malloc(sizeof(struct PolyNode));
    pCurrent = header->Link;
    while (pCurrent != NULL)
    {
        printf("%dx^%d ", pCurrent->coef, pCurrent->expon);
        pCurrent = pCurrent->Link;
    }
}
int Compare_Expon(int a, int b)
{
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    if (a < b)
        return -1;

}
struct PolyNode* Add_Polynomial(struct PolyNode* P1, struct PolyNode* P2)
{
    int sum = 0, e = 0;
    struct PolyNode* Front =(struct PolyNode*) malloc(sizeof(struct PolyNode));
    struct PolyNode* Rear = Front;
    Front->coef = 0;
    Front->expon = 0;
    Front->Link = NULL;
    while (P1 && P2)
    {
        struct PolyNode* NewNode =(struct PolyNode*) malloc(sizeof(struct PolyNode));
        e = Compare_Expon(P1->expon, P2->expon);
        switch (e)
        {
            case 1:
                NewNode->coef = P1->coef;
                NewNode->expon = P1->expon;
                NewNode->Link = NULL;
                Rear->Link = NewNode;
                Rear = NewNode;
                P1 = P1->Link;
                break;
            case 0:
                sum = P1->coef + P2->coef;
                NewNode->coef = sum;
                NewNode->expon = P1->expon;
                NewNode->Link = NULL;
                Rear->Link = NewNode;
                Rear = NewNode;
                P1 = P1->Link;
                P2 = P2->Link;
                break;
            case -1:
                NewNode->coef = P2->coef;
                NewNode->expon = P2->expon;
                NewNode->Link = NULL;
                Rear->Link = NewNode;
                Rear = NewNode;
                P2 = P2->Link;
                break;
        }

    }
    if (P1 != NULL)
    {
        struct PolyNode* NewNode1 =(struct PolyNode*) malloc(sizeof(struct PolyNode));
        NewNode1 = P1;
        Rear->Link = NewNode1;
        Rear = NewNode1;
        P1 = P1->Link;

    }
    if (P2 != NULL)
    {
        struct PolyNode* NewNode2 = (struct PolyNode*)malloc(sizeof(struct PolyNode));
        NewNode2 = P2;
        Rear->Link = NewNode2;
        Rear = NewNode2;
        P2 = P2->Link;

    }
    return Front;
}
int main()
{
    printf("请输入第一个多项式的各项:");
    struct PolyNode* header1 = Init_Polynomial1();
    printf("请输入第二个多项式的各项:");
    struct PolyNode* header2 = Init_Polynomial2();
    printf("第一个多项式的各项为：");
    Foreach_Polynomial(header1);
    printf("\n第二个多项式的各项为：");
    Foreach_Polynomial(header2);
    struct PolyNode* a = header1->Link;
    struct PolyNode* b = header2->Link;
    struct PolyNode* Front = Add_Polynomial(a,b);
    printf("\n两个多项式相加的结果为:");
    Foreach_Polynomial(Front);
    return 0;
}