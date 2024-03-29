//
// Created by 陈中超 on 2024/3/12.
//前缀表达式，后缀表达式
/*
 *  我们正常使用的表达式叫中缀表达式，操作符号在数字之间，前缀表达式是把操作符号提前
 *  后缀表达式是把操作符号放到最后，是最有利于让计算机去解析的
 * */
#include<stdio.h>
#include <malloc.h>
//用数组进行实现stack
#define MAX_SIZE 101
int A[MAX_SIZE];
int top = -1;

void Push(int x)
{
    if(top == MAX_SIZE - 1)
    {
        printf("Error : stack overflow \n");
        return;
    }

    //top++;
    //A[top] = x; 可以简写成下列语句
    A[++top] = x;
}


void Pop()
{
    if(top == -1)
    {
        printf("Error :no element to pop \n");
        return;
    }
    top--;
}

int Top()
{
    return A[top];
}

void Print()
{
    int i;
    printf("Stack: ");
    for(i = 0;i <= top;i++)
        printf("%d ",A[i]);
    printf("\n");

}

int EvaluatePostfix(char* exp)
{
    return 0;
}

void main()
{
    printf("hello world");
}