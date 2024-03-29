#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct Node {
    int data;         // 存储节点的数据
    struct Node *next; // 指向下一个节点的指针
} Node;

// 约瑟夫环问题的函数
void jusephub(int N, int M) {
    // 初始化循环链表的头指针和遍历指针
    Node *head = NULL, *p = NULL, *r = NULL;

    // 为头结点分配内存
    head = (Node *)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败!\n");
        return;
    }
    head->data = 1;         // 设置头结点的数据为1
    head->next = NULL;      // 头结点的next指向NULL
    p = head;               // 遍历指针p指向头结点

    // 使用尾插法创建链表
    for (int i = 2; i <= N; i++) {
        // 为新节点分配内存
        r = (Node *)malloc(sizeof(Node));
        if (r == NULL) {
            printf("内存分配失败!\n");
            return;
        }
        r->data = i;       // 设置新节点的数据
        r->next = NULL;    // 新节点的next指向NULL
        p->next = r;       // 将新节点插入到链表尾部
        p = r;             // 遍历指针p指向新节点
    }

    // 创建循环链表
    p->next = head;       // 最后一个节点的next指向头结点，形成循环
    p = head;             // 将遍历指针p重新指向头结点

    // 模拟约瑟夫环问题的执行过程
    while (p->next != p) {  // 当链表中不止一个节点时
        for (int i = 1; i < M; i++) {  // 报数到M-1
            r = p;           // r保存当前节点的前一个节点
            p = p->next;     // p指向下一个节点
        }
        // 输出出局的节点数据
        printf("%d ", p->data);
        // 移除出局的节点
        r->next = p->next;
        // 释放已出局节点的内存
        free(p);
        p = r->next;       // 更新p为下一个节点
    }
    // 输出最后一个节点的数据
    printf("%d\n", p->data);
    // 释放最后一个节点的内存
    free(p);
}

int main() {
    jusephub(10, 3);  // 调用函数，模拟10个人，报到3的人出局的情况
    return 0;
}