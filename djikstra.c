// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "djikstra.h"





void permuterTasMinNoed(struct TasMinNoed **a,
                     struct TasMinNoed **b)
{
    struct TasMinNoed *t = *a;
    *a = *b;
    *b = t;
}


void transformer_en_TasMin(struct TasMin *tasMin,
                int idx)
{
    int minimum, gauche, droite;
    minimum = idx;
    gauche = 2 * idx + 1;
    droite = 2 * idx + 2;

    if (gauche < tasMin->taille &&
        tasMin->tableau[gauche]->dist <
            tasMin->tableau[minimum]->dist)
        minimum = gauche;

    if (droite < tasMin->taille &&
        tasMin->tableau[droite]->dist <
            tasMin->tableau[minimum]->dist)
        minimum = droite;

    if (minimum != idx)
    {
        // The nodes to be swapped in min heap
        tasminnoed *noedMin =
            tasMin->tableau[minimum];
        tasminnoed *indiceNoed =
            tasMin->tableau[idx];

        // Swap positions
        tasMin->pos[noedMin->v] = idx;
        tasMin->pos[indiceNoed->v] = minimum;

        // Swap nodes
        swapMinHeapNode(&tasMin->tableau[minimum],
                        &tasMin->tableau[idx]);

        permuterTasMinNoed(tasMin, minimum);
    }
}




// A utility function to check if
// the given minHeap is empty or not
int estVide(struct TasMin *tasMin)
{
    return tasMin->taille == 0;
}

        
// Standard function to extract
// minimum node from heap
struct TasMinNoed *get_min(struct TasMin *
                                   tasMin)
{
    if (estVide(tasMin))
        return NULL;

    // Store the root node
    struct TasMinNoed *racine =
        tasMin->tableau[0];

    // Replace root node with last node
    struct TasMinNoed *dernierNoed =
        tasMin->tableau[tasMin->taille - 1];
    tasMin->tableau[0] = dernierNoed;

    // Update position of last node
    tasMin->pos[racine->v] = tasMin->taille - 1;
    tasMin->pos[dernierNoed->v] = 0;

    // Reduce heap size and heapify root
    --tasMin->taille;
    transformer_en_TasMin(tasMin, 0);

    return racine;
}






// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decrementerCle(struct TasMin *tasMin,
                 int v, int dist)
{
    // Get the index of v in heap array
    int i = tasMin->pos[v];

    // Get the node and update its dist value
    tasMin->tableau[i]->dist = dist;

    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && tasMin->tableau[i]->dist <
                    tasMin->tableau[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        tasMin->pos[tasMin->tableau[i]->v] =
            (i - 1) / 2;
        tasMin->pos[tasMin->tableau[(i - 1) / 2]->v] = i;
        permuterTasMinNoed(&tasMin->tableau[i],
                        &tasMin->tableau[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}





// A utility function to check if a given vertex
// 'v' is in min heap or not
bool inclusDansTasMin(struct TasMin *tasMin, int v)
{
    if (tasMin->pos[v] < tasMin->taille)
        return true;
    return false;
}

// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}


int main(){
    return;
}




