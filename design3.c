/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/5/31 14:14
* @version: 1.0
* @description: 二叉排序树与平衡二叉树的实现
********************************************************************************/
//二叉树的遍历，前序，中序，后序，递归方法
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Node* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Node* dequeue(Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }
    QueueNode* temp = q->front;
    Node* data = temp->data;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return data;
}
/*// Function to visit nodes in Preorder
void Preorder(Node *root) {
    if (root == NULL) return;

    printf("%c ", root->data); // Print data
    Preorder(root->left);      // Visit left subtree
    Preorder(root->right);     // Visit right subtree
}*/

// Function to visit nodes in Inorder
void Inorder(Node *root) {
    if (root == NULL) return;

    Inorder(root->left);       // Visit left subtree
    printf("%c ", root->data); // Print data
    Inorder(root->right);      // Visit right subtree
}

/*// Function to visit nodes in Postorder
void Postorder(Node *root) {
    if (root == NULL) return;

    Postorder(root->left);     // Visit left subtree
    Postorder(root->right);    // Visit right subtree
    printf("%c ", root->data); // Print data
}*/

// Function to Insert Node in a Binary Search Tree
Node* Insert(Node *root, char data) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->left = root->right = NULL;
    } else if (data <= root->data) { // Insert to the left child
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}
//查找操作
Node* search(Node* root, char key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (root->data < key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}
//计算平均查找长度
//查找深度
int depth(Node* root, char key, int currentDepth) {
    if (root == NULL) {
        return -1; // Node not found
    } else if (root->data == key) {
        return currentDepth;
    } else if (key < root->data) {
        return depth(root->left, key, currentDepth + 1);
    } else {
        return depth(root->right, key, currentDepth + 1);
    }
}
float averageSearchLength(Node* root, int totalNodes) {
    if (root == NULL) {
        return 0.0;
    }

    float sum = 0;

    Queue* q = createQueue();
    enqueue(q, root);
    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        int dep = depth(root, current->data, 1);

        sum +=dep;
        //printf("%c ", current->data);

        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }

    free(q);
    return sum / totalNodes;
}
//找到最小的结点，用于替代被删除的结点
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}
//删除操作
int deleteNode(Node** root, int data) {
    if (*root == NULL) return 0;

    if (data < (*root)->data)
        return deleteNode(&((*root)->left), data);
    else if (data > (*root)->data)
        return deleteNode(&((*root)->right), data);
    else {
        // Node to be deleted found
        if ((*root)->left == NULL) {
            Node* temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            Node* temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            // Node with two children
            Node* temp = findMin((*root)->right);
            (*root)->data = temp->data;
            return deleteNode(&((*root)->right), temp->data);
        }
        return 1;
    }
    return 0;
}

typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Get the height of a node
int height(AVLNode *node) {
    return node ? node->height : 0;
}

// Get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
AVLNode* createNode(int key) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Insert a node into the AVL tree
AVLNode* insert(AVLNode* node, int key) {
    if (node == NULL) return createNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Equal keys are not allowed in AVL tree
    }

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//查找深度
int AVLdepth(AVLNode* root, char key, int currentDepth) {
    if (root == NULL) {
        return -1; // Node not found
    } else if (root->key == key) {
        return currentDepth;
    } else if (key < root->key) {
        return depth(root->left, key, currentDepth + 1);
    } else {
        return depth(root->right, key, currentDepth + 1);
    }
}
float averageSearchLengthAVL(AVLNode* root, int totalNodes) {
    if (root == NULL) {
        return 0.0;
    }

    float sum = 0;

    Queue* q = createQueue();
    enqueue(q, root);
    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        int dep = depth(root, current->data, 1);

        sum +=dep;
        //printf("%c ", current->data);

        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }

    free(q);
    return sum / totalNodes;
}

// Find the node with minimum key value found in that tree
AVLNode *minValueNode(AVLNode* node) {
    AVLNode* current = node;

    // Loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

/*// Delete a node from the AVL tree
AVLNode* deleteAVLNode(AVLNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = deleteAVLNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteAVLNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteAVLNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}*/

// Inorder traversal (for testing)
void inOrder(AVLNode *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

#define MAX_SIZE 100 // Define maximum size of the array

typedef struct {
    int data[MAX_SIZE];
    int size;
} BinaryTree;

// Function to initialize the binary tree
void initBinaryTree(BinaryTree* tree) {
    for (int i = 0; i < MAX_SIZE; i++) {
        tree->data[i] = -1; // Initialize with -1 to indicate empty slots
    }
    tree->size = 0;
}

// Function to insert an element into the binary tree
void BSTinsert(BinaryTree* tree, int key) {
    if (tree->size >= MAX_SIZE) {
        printf("The tree is full\n");
        return;
    }

    int index = 0;
    while (index < MAX_SIZE && tree->data[index] != -1) {
        if (key < tree->data[index]) {
            index = 2 * index + 1;
        } else if (key > tree->data[index]) {
            index = 2 * index + 2;
        } else {
            return; // Duplicate keys are not allowed
        }
    }

    if (index < MAX_SIZE) {
        tree->data[index] = key;
        tree->size++;
    } else {
        printf("The tree is full or an error occurred\n");
    }
}

// Function to perform inorder traversal
void BSTinorder(BinaryTree* tree, int index) {
    if (index >= MAX_SIZE || tree->data[index] == -1) {
        return;
    }

    BSTinorder(tree, 2 * index + 1);
    printf("%d ", tree->data[index]);
    BSTinorder(tree, 2 * index + 2);
}

/*// Function to find the depth of a node
int BSTdepth(BinaryTree* tree, int index, int key, int currentDepth) {
    if (index >= MAX_SIZE || tree->data[index] == -1) {
        return 0;
    }
    if (tree->data[index] == key) {
        return currentDepth;
    }
    if (key < tree->data[index]) {
        return BSTdepth(tree, 2 * index + 1, key, currentDepth + 1);
    } else {
        return BSTdepth(tree, 2 * index + 2, key, currentDepth + 1);
    }
}

// Function to calculate the average search length
float averageSearchBSTLength(BinaryTree* tree) {
    int totalDepth = 0;
    int count = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (tree->data[i] != -1) {
            totalDepth += BSTdepth(tree, 0, tree->data[i], 1);
            count++;
        }
    }

    return count == 0 ? 0 : (float)totalDepth / count;
}*/


/*// 查找给定子树的最小节点索引
int findMinIndex(BinaryTree* tree, int index) {
    while (2 * index + 1 < MAX_SIZE && tree->data[2 * index + 1] != -1) {
        index = 2 * index + 1;
    }
    return index;
}

// 删除节点函数
int deleteBSTNode(BinaryTree* tree, int key) {
    int index = 0;
    while (index < MAX_SIZE && tree->data[index] != key) {
        if (key < tree->data[index]) {
            index = 2 * index + 1;
        } else {
            index = 2 * index + 2;
        }
    }

    if (index >= MAX_SIZE || tree->data[index] == -1) {
        printf("Element not found in the tree\n");
        return 0;
    }

    // 处理无子节点或只有一个子节点的情况
    if ((2 * index + 1 >= MAX_SIZE || tree->data[2 * index + 1] == -1) &&
        (2 * index + 2 >= MAX_SIZE || tree->data[2 * index + 2] == -1)) {
        tree->data[index] = -1;
    } else if (2 * index + 1 >= MAX_SIZE || tree->data[2 * index + 1] == -1) {
        // 只有右子节点
        tree->data[index] = tree->data[2 * index + 2];
        tree->data[2 * index + 2] = -1;
    } else if (2 * index + 2 >= MAX_SIZE || tree->data[2 * index + 2] == -1) {
        // 只有左子节点
        tree->data[index] = tree->data[2 * index + 1];
        tree->data[2 * index + 1] = -1;
    } else {
        // 有两个子节点
        int minIndex = findMinIndex(tree, 2 * index + 2);
        tree->data[index] = tree->data[minIndex];
        return deleteNode(tree, tree->data[minIndex]);
    }

    tree->size--;
    return 1;
}*/
// Function to delete a node
void deleteBSTNode(BinaryTree* tree, int key) {
    int index = 0;
    while (index < MAX_SIZE && tree->data[index] != key) {
        if (key < tree->data[index]) {
            index = 2 * index + 1;
        } else {
            index = 2 * index + 2;
        }
    }

    if (index >= MAX_SIZE || tree->data[index] == -1) {
        printf("Element not found in the tree\n");
        return;
    }

    tree->data[index] = -1;

    tree->size--;
}

int main() {


    printf("============二叉排序树===================\n");
     //Testing Binary Search Tree
    Node* root = NULL;
    int numNodes;
    char data;
    float ASL;
    printf("Enter the number of nodes to insert: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf(" %c", &data);
        root = Insert(root, data);
    }

    // Print nodes in Inorder
    printf("Inorder: ");
    Inorder(root);
    printf("\n");

    ASL = averageSearchLength(root,numNodes);
    printf("平均查找长度为%.2f\n",ASL);
    char del;
    printf("Enter the value of the node to delete: ");
    scanf(" %c", &del); // Use %c instead of %d

    int result = deleteNode(&root, del);
    if (result) {
        printf("Node %c deleted successfully.\n", del);
    } else {
        printf("Node %c not found.\n", del);
    }

    printf("Inorder: ");
    Inorder(root);
    printf("\n");

/*    root = Insert(root, 'M'); root = Insert(root, 'B');
    root = Insert(root, 'Q'); root = Insert(root, 'Z');
    root = Insert(root, 'A'); root = Insert(root, 'C');
    // Print nodes in Inorder
    printf("Inorder: ");
    Inorder(root);
    printf("\n");

    deleteNode(root,'M');

    printf("Inorder: ");
    Inorder(root);
    printf("\n");*/
    // Print nodes in Preorder
   /* printf("Preorder: ");
    Preorder(root);
    printf("\n");*/





    // Print nodes in Postorder
  /*  printf("Postorder: ");
    Postorder(root);
    printf("\n");*/




   //  Testing AVL Tree
    printf("===============平衡二叉树==============\n");
    AVLNode *avlRoot = NULL;
  /*  avlRoot = insert(avlRoot, 10);
    avlRoot = insert(avlRoot, 20);
    avlRoot = insert(avlRoot, 30);
    avlRoot = insert(avlRoot, 40);
    avlRoot = insert(avlRoot, 50);
    avlRoot = insert(avlRoot, 25);*/

    int L[] = {10, 20, 30, 40, 50, 25}; // Example list
    int n = sizeof(L)/sizeof(L[0]);

    for (int i = 0; i < n; i++) {
        avlRoot = insert(avlRoot, L[i]);
    }



    printf("Inorder traversal of the constructed AVL tree is: ");
    inOrder(avlRoot);
    printf("\n");


    float avlASL = averageSearchLengthAVL(avlRoot,n);
    printf("平均查找长度为%.2f\n",avlASL);

    //avlRoot = deleteAVLNode(avlRoot, 40);
/*

    printf("Inorder traversal after deletion of 40: ");
    inOrder(avlRoot);
    printf("\n");
*/




    printf("============二叉树顺序存储================\n");
    BinaryTree tree;
    initBinaryTree(&tree);

 /*   int L[] = {9, 2, 30, 4, 5, 25}; // Example list
    int n = sizeof(L) / sizeof(L[0]);*/

    for (int i = 0; i < n; i++) {
        BSTinsert(&tree, L[i]);
    }

    printf("Inorder traversal of the constructed binary tree is: ");
    BSTinorder(&tree, 0);
    printf("\n");

/*    float ASL1 = averageSearchBSTLength(&tree);
    printf("Average Search Length is %.2f\n", ASL1);*/

    int keyToDelete = 30;
    deleteBSTNode(&tree, keyToDelete);

    printf("Inorder traversal after deletion of %d: ", keyToDelete);
    BSTinorder(&tree, 0);
    printf("\n");

    return 0;

}
