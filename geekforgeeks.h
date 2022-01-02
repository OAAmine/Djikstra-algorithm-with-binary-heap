
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
// A structure to represent a
// node in adjacency list
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

// A structure to represent
// an adjacency list
struct AdjList
{
	
// Pointer to head node of list
struct AdjListNode *head;
};

// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph
{
	int V;
	struct AdjList* array;
};

// A utility function to create
// a new adjacency list node
struct AdjListNode* newAdjListNode(
				int dest, int weight)
{
	struct AdjListNode* newNode =
			(struct AdjListNode*)
	malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates
// a graph of V vertices
struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)
			malloc(sizeof(struct Graph));
	graph->V = V;

	// Create an array of adjacency lists.
	// Size of array will be V
	graph->array = (struct AdjList*)
	malloc(V * sizeof(struct AdjList));

	// Initialize each adjacency list
	// as empty by making head as NULL
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}