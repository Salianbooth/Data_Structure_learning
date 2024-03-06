//
// Created by 陈中超 on 2023/12/20.
//
#include<stdio.h>
#include<stdlib.h>

/*
    链表学习，插入链表
    先创建相应的节点，头节点，然后指向NULL，然后，创建新的节点temp，让temp中的data指向相应的值，然后将他的节点指向空
    这是头接法，就是接在头指针后面，这时候要判断头指针后的node是否为空，如果为空，那么就需要将temp的next指向下一个节点
    */
struct Node{
    int data;
    struct Node* next;
}typedef Node;
struct Node* head;

void Insert(int data ,int n)
{
    Node* temp1 = (Node*)malloc(sizeof(struct Node));
    temp1 ->data = data;
    temp1 -> next =NULL;
    if(n == 1) //如果要插入的位置为1
    {
        temp1 -> next = head; //使next接入到head 的地址
        head = temp1; //使头节点head = temp1
        return;
    }
    int i;
    Node* temp2 = head; //因为节点的索引是从0 开始的，所以我们要讲节点插入到n-1和n-2之间
    for(i = 0;i < n-2;i++) //每一次都让temp2向后移动，知道到达指定的位置n-2
    {
        temp2 = temp2 -> next;
    }
    temp1 -> next = temp2-> next; //让temp1的next指向n-1的地址
    temp2 -> next = temp1;  //n-2的next要更新，即temp2的next指向temp1的地址
}
//normal approach to reach print the list
void Print()
{
    struct Node* temp = head; //头节点
    while(temp != NULL)
    {
        printf(" %d" , temp -> data); //打印data
        temp = temp -> next; //移动下一节点
    }
    printf("\n");
}
//用递归来实现
void  Reverseprint(struct Node *p)
{
    if(p == NULL) return;
    Reverseprint(p -> next);
    printf("%d ",p -> data);
}
void Delete(int n)
{
    struct Node* temp1 = head;
    if(n == 1){
        head = temp1 -> next;
        free(temp1);
        return ;
    }
    int i;
    for(i = 0; i < n - 2; i ++)
    {
        temp1 = temp1 -> next;
        struct  Node* temp2 = temp1->next;
        temp1 -> next = temp2 ->next;
        free(temp2);
    }
}
/*void Reverce()
{
   struct Node *current,*prev,*next;
   current = head;
   prev = NULL;
   while (current != NULL)
   {
       next = current ->next;
       current->next = prev;
       prev = current;
       current = next;
   }
   head = prev;

}*/
void Reverse(struct Node *p)
{
    if(p -> next ==NULL)
    {
        head = p;
        return;
    }
    Reverse(p->next);
    struct Node * q = p -> next;
    q -> next = p;
    p -> next = NULL;
}

int main()
{
    head = NULL;

    Insert(2,1);
    Insert(3,2);
    Insert(4,3);
    Insert(5,4);

    //Reverseprint(head);
    Print();
    Reverse(head);
    Print();
    //Print();
    // int n ;
    //printf("enter a position\n");
    //scanf("%d\n",&n);
    //Delete(n);
    //Print();


    /*printf("How many numbers?\n");
    int n , i ,x;
    scanf("%d",&n);
    for( i  = 0; i< n ; i++)
    {
        printf("Enter the number \n");
        scanf("%d",&x);
        Insert(x);
        Print();
    }*/

}