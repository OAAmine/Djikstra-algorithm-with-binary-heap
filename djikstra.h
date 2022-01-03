
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


// A structure to represent a
// node in adjacency list
struct AdjListNode //same as msuc 
{
    int dest;
    int val;
    struct AdjListNode *next;
};

// A structure to represent
// an adjacency list
struct AdjList //same as vlist but with card and dm 
{

    // Pointer to head node of list
    struct AdjListNode *head;
};

// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph // same as graph
{
    int V;
    struct AdjList *array;
};

// A utility function to create
// a new adjacency list node
struct AdjListNode *newAdjListNode(
    int dest, int val)
{
    struct AdjListNode *newNode =
        (struct AdjListNode *)
            malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates
// a graph of V vertices
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)
        malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.
    // Size of array will be V
    graph->array = (struct AdjList *)
        malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Structure to represent a min heap node
struct MinHeapNode
{
    int v;
    int dist;
};
typedef struct MinHeapNode minheapnode;

// Structure to represent a min heap
struct MinHeap
{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    struct MinHeapNode **array;
};

// A utility function to create a
// new Min Heap Node
struct MinHeapNode *newMinHeapNode(int v,
                                   int dist)
{
    struct MinHeapNode *minHeapNode =
        (struct MinHeapNode *)
            malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap =
        (struct MinHeap *)
            malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
        capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode **)
            malloc(capacity *
                   sizeof(struct MinHeapNode *));
    return minHeap;
}

struct MinHeapNode *extractMin(struct MinHeap *
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode *root =
        minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode =
        minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}


void swapMinHeapNode(struct MinHeapNode **a,
                     struct MinHeapNode **b);

void minHeapify(struct MinHeap *minHeap,
                int idx);

int isEmpty(struct MinHeap *minHeap);

void decreaseKey(struct MinHeap *minHeap,
                 int v, int dist);

bool isInMinHeap(struct MinHeap *minHeap, int v);

void printArr(int dist[], int n);

void dijkstra(struct Graph *graph, int src);