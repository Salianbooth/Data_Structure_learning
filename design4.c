/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/5/31 14:32
* @version: 1.0
* @description: 图的基本操作
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#define MAX_VERTICES 100
#define INFINITY INT_MAX
typedef struct AdjListNode {
    char dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct {
    AdjListNode* head;
} AdjList;

typedef struct {
    int V;
    int E;
    AdjList* array;
    char* vertices;  // Array to store vertex names
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(char dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    graph->vertices = (char*)malloc(V * sizeof(char));
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, char src, char dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    int srcIndex = strchr(graph->vertices, src) - graph->vertices;
    newNode->next = graph->array[srcIndex].head;
    graph->array[srcIndex].head = newNode;
}

// Function to calculate the in-degree and out-degree of each vertex
void calculateDegrees(Graph* graph, int inDegree[], int outDegree[]) {
    for (int i = 0; i < graph->V; i++) {
        outDegree[i] = 0;
        inDegree[i] = 0;
    }

    for (int v = 0; v < graph->V; v++) {
        AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl) {
            outDegree[v]++;
            int destIndex = strchr(graph->vertices, pCrawl->dest) - graph->vertices;
            inDegree[destIndex]++;
            pCrawl = pCrawl->next;
        }
    }
}

// DFS traversal of the vertices reachable from v
void DFSUtil(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%c ", graph->vertices[v]);

    AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl) {
        int adj = strchr(graph->vertices, pCrawl->dest) - graph->vertices;
        if (!visited[adj]) {
            DFSUtil(graph, adj, visited);
        }
        pCrawl = pCrawl->next;
    }
}

// DFS traversal of the entire graph
void DFS(Graph* graph, char startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    int startIndex = strchr(graph->vertices, startVertex) - graph->vertices;
    printf("DFS starting from vertex %c:\n", startVertex);
    DFSUtil(graph, startIndex, visited);
    printf("\n");
    free(visited);
}

// Function to perform BFS traversal
void BFS(Graph* graph, char startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    int startIndex = strchr(graph->vertices, startVertex) - graph->vertices;
    visited[startIndex] = true;
    queue[rear++] = startIndex;

    printf("BFS starting from vertex %c:\n", startVertex);
    while (front < rear) {
        int currVertex = queue[front++];
        printf("%c ", graph->vertices[currVertex]);

        AdjListNode* pCrawl = graph->array[currVertex].head;
        while (pCrawl) {
            int adj = strchr(graph->vertices, pCrawl->dest) - graph->vertices;
            if (!visited[adj]) {
                visited[adj] = true;
                queue[rear++] = adj;
            }
            pCrawl = pCrawl->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}
// Function to delete edges connected to a specific vertex
void deleteEdges(Graph* graph, char vertex) {
    int vertexIndex = strchr(graph->vertices, vertex) - graph->vertices;

    // Delete outgoing edges
    AdjListNode* current = graph->array[vertexIndex].head;
    while (current) {
        AdjListNode* temp = current;
        current = current->next;
        free(temp);
    }
    graph->array[vertexIndex].head = NULL;

    // Delete incoming edges
    for (int i = 0; i < graph->V; i++) {
        AdjListNode* pCrawl = graph->array[i].head;
        AdjListNode* prev = NULL;
        while (pCrawl) {
            if (pCrawl->dest == vertex) {
                if (prev) {
                    prev->next = pCrawl->next;
                } else {
                    graph->array[i].head = pCrawl->next;
                }
                free(pCrawl);
                break;
            }
            prev = pCrawl;
            pCrawl = pCrawl->next;
        }
    }
}

// Check if graph is connected using DFS
bool isConnected(Graph* graph, char startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    int startIndex = strchr(graph->vertices, startVertex) - graph->vertices;
    DFSUtil(graph, startIndex, visited);

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            free(visited);
            return false;
        }
    }
    free(visited);
    return true;
}
// Convert adjacency list to adjacency matrix
void adjListToAdjMatrix(Graph* graph, int adjMatrix[][MAX_VERTICES]) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < graph->V; i++) {
        AdjListNode* pCrawl = graph->array[i].head;
        while (pCrawl) {
            int destIndex = strchr(graph->vertices, pCrawl->dest) - graph->vertices;
            adjMatrix[i][destIndex] = pCrawl->weight;
            pCrawl = pCrawl->next;
        }
    }
}


typedef struct {
    int adjvex;
    int lowcost;
} Closedge;

Closedge closedge[MAX_VERTICES]; // Auxiliary array


int getVertexIndex(Graph* graph, char vertex) {
    return strchr(graph->vertices, vertex) - graph->vertices;
}

void PrimMiniSpanTree(Graph* graph, char v0) {
    int v0Index = getVertexIndex(graph, v0);
    closedge[v0Index].lowcost = 0;

    for (int i = 0; i < graph->V; i++) {
        if (i != v0Index) {
            closedge[i].adjvex = v0Index; // Initialize all vertices' adjacent vertices to v0
            closedge[i].lowcost = INFINITY;
        }
    }

    AdjListNode* pCrawl = graph->array[v0Index].head;
    while (pCrawl) {
        int adjIndex = getVertexIndex(graph, pCrawl->dest);
        closedge[adjIndex].lowcost = pCrawl->weight;
        pCrawl = pCrawl->next;
    }

    for (int i = 0; i < graph->V - 1; i++) { // Loop V-1 times since v0 is already included
        int min = INFINITY;
        int index = 0; // To store the index of the vertex with the minimum edge

        for (int j = 0; j < graph->V; j++) {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min) {
                min = closedge[j].lowcost;
                index = j;
            }
        }

        printf("(%c, %c) ", graph->vertices[closedge[index].adjvex], graph->vertices[index]); // Output the minimum edge
        closedge[index].lowcost = 0; // Mark this vertex as included in MST

        pCrawl = graph->array[index].head;
        while (pCrawl) {
            int adjIndex = getVertexIndex(graph, pCrawl->dest);
            if (closedge[adjIndex].lowcost != 0 && pCrawl->weight < closedge[adjIndex].lowcost) {
                closedge[adjIndex].lowcost = pCrawl->weight;
                closedge[adjIndex].adjvex = index;
            }
            pCrawl = pCrawl->next;
        }
    }
}


int main() {
    int V = 5;
    int E = 6;

    Graph* graph = createGraph(V);
    graph->vertices[0] = 'A';
    graph->vertices[1] = 'B';
    graph->vertices[2] = 'C';
    graph->vertices[3] = 'D';
    graph->vertices[4] = 'E';

    addEdge(graph, 'A', 'B', 3);
    addEdge(graph, 'A', 'C', 2);
    addEdge(graph, 'B', 'C', 1);
    addEdge(graph, 'C', 'D', 4);
    addEdge(graph, 'D', 'E', 6);
    addEdge(graph, 'D', 'B', 9);
    addEdge(graph, 'E', 'A', 7);

    int inDegree[MAX_VERTICES], outDegree[MAX_VERTICES];
    calculateDegrees(graph, inDegree, outDegree);

    printf("Vertex\tIn-Degree\tOut-Degree\n");
    for (int i = 0; i < V; i++) {
        printf("%c\t%d\t\t%d\n", graph->vertices[i], inDegree[i], outDegree[i]);
    }

    DFS(graph, 'A');
    BFS(graph, 'A');

/*     char deleteVertex;
     deleteEdges(graph, 'E');*/

    if (isConnected(graph, 'A')) {
        printf("The graph is connected.\n");
    } else {
        printf("The graph is not connected.\n");
    }


    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    adjListToAdjMatrix(graph, adjMatrix);
    for(int i = 0;i < V;i++){
        for(int j = 0;j < E ;j++){
            printf("%d ",adjMatrix[i][j]);
        }
        printf("\n");
    }
    PrimMiniSpanTree(graph, 'A');
/*     printf("Enter the number of vertices: ");
     scanf("%d", &V);
     printf("Enter the number of edges: ");
     scanf("%d", &E);

     Graph* graph = createGraph(V);
     printf("Enter the vertices (single character):\n");
     for (int i = 0; i < V; i++) {
         printf("Vertex %d: ", i + 1);
         scanf(" %c", &graph->vertices[i]);
     }

     printf("Enter the edges (src dest weight):\n");
     for (int i = 0; i < E; i++) {
         char src, dest;
         int weight;
         printf("Edge %d: ", i + 1);
         scanf(" %c %c %d", &src, &dest, &weight);
         addEdge(graph, src, dest, weight);
     }*/

/*     int inDegree[MAX_VERTICES], outDegree[MAX_VERTICES];
     calculateDegrees(graph, inDegree, outDegree);

     printf("Vertex\tIn-Degree\tOut-Degree\n");
     for (int i = 0; i < V; i++) {
         printf("%c\t%d\t\t%d\n", graph->vertices[i], inDegree[i], outDegree[i]);
     }*/


/*     char startVertex;
     printf("Enter the starting vertex for DFS and BFS: ");
     scanf(" %c", &startVertex);

     DFS(graph, startVertex);
     BFS(graph, startVertex);*/

/*     char deleteVertex;
     printf("Enter the vertex to delete edges: ");
     scanf(" %c", &deleteVertex);
     deleteEdges(graph, deleteVertex);

     if (isConnected(graph, startVertex)) {
         printf("The graph is connected.\n");
     } else {
         printf("The graph is not connected.\n");
     }*/
    /*
    int vertexToDelete;
    printf("Enter the vertex to delete its edges: ");
    scanf("%d", &vertexToDelete);
    deleteEdges(graph, vertexToDelete);

    printf("DFS after deleting edges of vertex %d:\n", vertexToDelete);
    DFS(graph, startVertex);

    bool connected = isConnected(graph, startVertex);
    if (connected) {
        printf("The graph is connected.\n");
    } else {
        printf("The graph is not connected.\n");
    }

    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    adjListToAdjMatrix(graph, adjMatrix);

    primMST(adjMatrix, V);
*/
    free(graph->vertices);
    for (int i = 0; i < V; i++) {
        AdjListNode* current = graph->array[i].head;
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
