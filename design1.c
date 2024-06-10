/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/5/31 14:10
* @version: 1.0
* @description:
 * 11.2.1 一元稀疏多项式计算器
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// 定义多项式节点
typedef struct PolyNode {
    int coef; // 系数
    int exp;  // 指数
    struct PolyNode *next;
} PolyNode;

// 创建一个新的节点
PolyNode* createNode(int coef, int exp) {
    PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 插入节点到多项式中
void insertNode(PolyNode **poly, int coef, int exp) {
    PolyNode *newNode = createNode(coef, exp);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        PolyNode *temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 打印多项式
void printPoly(PolyNode *poly) {
    while (poly != NULL) {
        if (poly->coef > 0 && poly != NULL) {
            printf("+ ");
        }
        printf("%dx^%d ", poly->coef, poly->exp);
        poly = poly->next;
    }
    printf("\n");
}

// 多项式加法
PolyNode* addPolys(PolyNode *poly1, PolyNode *poly2) {
    PolyNode *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {//当两个多项式都不为空时
        if (poly1->exp == poly2->exp) { //如果两个多项式的指数相等，则让他们系数相加，插入到result中
            insertNode(&result, poly1->coef + poly2->coef, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertNode(&result, poly1->coef, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertNode(&result, poly2->coef, poly2->exp);
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {//当一方不为空时，把它所有的都加入到结点后面
        insertNode(&result, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertNode(&result, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}
// 多项式减法
PolyNode* delPolys(PolyNode *poly1, PolyNode *poly2) {
    PolyNode *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {//当两个多项式都不为空时
        if (poly1->exp == poly2->exp) { //如果两个多项式的指数相等，则让他们系数相减，插入到result中
            insertNode(&result, poly1->coef - poly2->coef, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertNode(&result, poly1->coef, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertNode(&result, poly2->coef, poly2->exp);
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {//当一方不为空时，把它所有的都加入到结点后面
        insertNode(&result, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertNode(&result, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}
// 多项式乘法
PolyNode* multiplyPolys(PolyNode *poly1, PolyNode *poly2) {
    PolyNode *result = NULL;
    PolyNode *tempPoly2 = poly2;

    while (poly1 != NULL) {
        while (tempPoly2 != NULL) {
            insertNode(&result, poly1->coef * tempPoly2->coef, poly1->exp + tempPoly2->exp);
            tempPoly2 = tempPoly2->next;
        }
        tempPoly2 = poly2;
        poly1 = poly1->next;
    }

    return result;
}

int main() {
    PolyNode *poly1 = NULL;
    PolyNode *poly2 = NULL;

    int n1,n2;
    printf("请输入第一个多项式的项数: ");
    scanf("%d",&n1);
    for(int i = 0;i < n1 ;i++){
        int coef1,exp1;
        printf("请输入第%d个元素的系数和指数的指：",(i+1));
        scanf("%d %d",&coef1,&exp1);
        printf("\n");
        insertNode(&poly1, coef1, exp1);
    }
/*    // 创建第一个多项式 5x^3 + 4x^2 + 2x^1
    insertNode(&poly1, 5, 3);
    insertNode(&poly1, 4, 2);
    insertNode(&poly1, 2, 1);*/

    printf("请输入第二个多项式的项数: ");
    scanf("%d",&n2);
    printf("\n");
    for(int i = 0;i < n2 ;i++){
        int coef2,exp2;
        printf("请输入第%d个元素的系数和指数的指：",(i+1));
        scanf("%d %d",&coef2,&exp2);
        insertNode(&poly2, coef2, exp2);
    }
/*
    // 创建第二个多项式 3x^3 + 2x^2 + 1x^0
    insertNode(&poly2, 3, 3);
    insertNode(&poly2, 2, 2);
    insertNode(&poly2, 1, 0);
*/

    printf("多项式 1: ");
    printPoly(poly1);
    printf("多项式 2: ");
    printPoly(poly2);

    // 多项式相加
    PolyNode *sum = addPolys(poly1, poly2);
    printf("多项式相加结果: ");
    printPoly(sum);

    PolyNode *sub = delPolys(poly1, poly2);
    printf("多项式相减结果: ");
    printPoly(sub);

   /* // 多项式相乘
    PolyNode *product = multiplyPolys(poly1, poly2);
    printf("多项式相乘结果: ");
    printPoly(product);*/

    return 0;
}