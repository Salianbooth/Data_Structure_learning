/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/5/31 14:10
* @version: 1.0
* @description:
 * 11.2.1 һԪϡ�����ʽ������
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// �������ʽ�ڵ�
typedef struct PolyNode {
    int coef; // ϵ��
    int exp;  // ָ��
    struct PolyNode *next;
} PolyNode;

// ����һ���µĽڵ�
PolyNode* createNode(int coef, int exp) {
    PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// ����ڵ㵽����ʽ��
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

// ��ӡ����ʽ
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

// ����ʽ�ӷ�
PolyNode* addPolys(PolyNode *poly1, PolyNode *poly2) {
    PolyNode *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {//����������ʽ����Ϊ��ʱ
        if (poly1->exp == poly2->exp) { //�����������ʽ��ָ����ȣ���������ϵ����ӣ����뵽result��
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
    while (poly1 != NULL) {//��һ����Ϊ��ʱ���������еĶ����뵽������
        insertNode(&result, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertNode(&result, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}
// ����ʽ����
PolyNode* delPolys(PolyNode *poly1, PolyNode *poly2) {
    PolyNode *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {//����������ʽ����Ϊ��ʱ
        if (poly1->exp == poly2->exp) { //�����������ʽ��ָ����ȣ���������ϵ����������뵽result��
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
    while (poly1 != NULL) {//��һ����Ϊ��ʱ���������еĶ����뵽������
        insertNode(&result, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertNode(&result, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}
// ����ʽ�˷�
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
    printf("�������һ������ʽ������: ");
    scanf("%d",&n1);
    for(int i = 0;i < n1 ;i++){
        int coef1,exp1;
        printf("�������%d��Ԫ�ص�ϵ����ָ����ָ��",(i+1));
        scanf("%d %d",&coef1,&exp1);
        printf("\n");
        insertNode(&poly1, coef1, exp1);
    }
/*    // ������һ������ʽ 5x^3 + 4x^2 + 2x^1
    insertNode(&poly1, 5, 3);
    insertNode(&poly1, 4, 2);
    insertNode(&poly1, 2, 1);*/

    printf("������ڶ�������ʽ������: ");
    scanf("%d",&n2);
    printf("\n");
    for(int i = 0;i < n2 ;i++){
        int coef2,exp2;
        printf("�������%d��Ԫ�ص�ϵ����ָ����ָ��",(i+1));
        scanf("%d %d",&coef2,&exp2);
        insertNode(&poly2, coef2, exp2);
    }
/*
    // �����ڶ�������ʽ 3x^3 + 2x^2 + 1x^0
    insertNode(&poly2, 3, 3);
    insertNode(&poly2, 2, 2);
    insertNode(&poly2, 1, 0);
*/

    printf("����ʽ 1: ");
    printPoly(poly1);
    printf("����ʽ 2: ");
    printPoly(poly2);

    // ����ʽ���
    PolyNode *sum = addPolys(poly1, poly2);
    printf("����ʽ��ӽ��: ");
    printPoly(sum);

    PolyNode *sub = delPolys(poly1, poly2);
    printf("����ʽ������: ");
    printPoly(sub);

   /* // ����ʽ���
    PolyNode *product = multiplyPolys(poly1, poly2);
    printf("����ʽ��˽��: ");
    printPoly(product);*/

    return 0;
}