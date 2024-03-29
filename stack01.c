//
// Created by 陈中超 on 2024/3/1.
// 栈 Stack Last-in-First-off(LIFO)
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

//用链表实现stack ----- 头插法
struct Node{
    int data;
    struct Node* link;
};
struct Node* head = NULL;

void Push_list(int x){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node*));
    temp->data = x;
    temp->link = head;
    head = temp;
}
void Pop_list(){
    struct Node *temp;
    if(top == NULL) return;
    temp = head;
    head = head ->link;
    free(temp);
}

void Print_list()
{
    struct Node* temp = head;
    if(temp != NULL)
    {
        printf(" %d" , temp -> data); //打印data
        temp = temp -> link; //移动下一节点
    }
    printf("\n");

}

int main(){
/*    Push(2);
    Push(5);
    Push(10);
    Print();
    Pop();
    Print();
    Push(12);
    Print();*/

    Push_list(2);
    Push_list(5);
    Push_list(10);
    Print_list();
    Pop_list();
    Push_list(12);
    Print_list();


}
