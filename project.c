#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "graphe-4.c"
#include "graphe-4.h"
#include "msuc.c"
#include "msuc.h"















// Structure to represent a min heap
struct TasMin
{

    // Number of heap nodes present currently
    int taille;

    // Capacity of min heap
    int capacite;

    // This is needed for decreaseKey()
    int *pos;
    struct NoedTasMin **tableau;
};

// Structure to represent a min heap node
struct NoedTasMin
{
    int v;
    int dist;
};

// A utility function to create a
// new Min Heap Node
struct NoedTasMin *newNoedTasMin(int v,
                                 int dist)
{
    struct NoedTasMin *noedTasMin =
        (struct NoedTasMin *)
            malloc(sizeof(struct NoedTasMin));
    noedTasMin->v = v;
    noedTasMin->dist = dist;
    return noedTasMin;
};

















// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void transformerEnTasMin(struct TasMin *tasMin,
                int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < tasMin->taille &&
        tasMin->tableau[left]->dist <
            tasMin->tableau[smallest]->dist)
        smallest = left;

    if (right < tasMin->taille &&
        tasMin->tableau[right]->dist <
            tasMin->tableau[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct NoedTasMin *smallestNode =
            tasMin->tableau[smallest];
        struct NoedTasMin *idxNode =
            tasMin->tableau[idx];

        // Swap positions
        tasMin->pos[smallestNode->v] = idx;
        tasMin->pos[idxNode->v] = smallest;

        // Swap nodes
        permuterNoedTasMin(&tasMin->tableau[smallest],
                        &tasMin->tableau[idx]);

        transformerEnTasMin(tasMin, smallest);
    }
}




// A utility function to create a Min Heap
struct TasMin* creerTasMin(int capacite)
{
    struct TasMin* tasMin =
         (struct TasMin*) 
      malloc(sizeof(struct TasMin));
    tasMin->pos = (int *)malloc(
            capacite * sizeof(int));
    tasMin->taille = 0;
    tasMin->capacite = capacite;
    tasMin->tableau =
         (struct NoedTasMin**) 
                 malloc(capacite * 
       sizeof(struct NoedTasMin*));
    return tasMin;
}



void permuterNoedTasMin(struct NoedTasMin** a, 
                     struct NoedTasMin** b)
{
    struct NoedTasMin* t = *a;
    *a = *b;
    *b = t;
}
  

// Function to decreasy dist value 
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void diminuerDis(struct TasMin* tasMin, 
                         int v, int dist)
{
    // Get the index of v in  heap tableau
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
                                      (i-1)/2;
        tasMin->pos[tasMin->tableau[
                             (i-1)/2]->v] = i;
        permuterNoedTasMin(&tasMin->tableau[i],  
                 &tasMin->tableau[(i - 1) / 2]);
  
        // move to parent index
        i = (i - 1) / 2;
    }
}


// A utility function to check if 
// the given minHeap is ampty or not
int estVide(struct TasMin* tasMin)
{
    return tasMin->taille == 0;
}


// Standard function to extract 
// minimum node from heap
struct NoedTasMin* extraireMin(struct TasMin* 
                                   tasMin)
{
    if (estVide(tasMin))
        return NULL;
  
    // Store the root node
    struct NoedTasMin* racine = 
                   tasMin->tableau[0];
  
    // Replace root node with last node
    struct NoedTasMin* dernierNoed = 
         tasMin->tableau[tasMin->taille - 1];
    tasMin->tableau[0] = dernierNoed;
  
    // Update position of last node
    tasMin->pos[racine->v] = tasMin->taille-1;
    tasMin->pos[dernierNoed->v] = 0;
  
    // Reduce heap taille and heapify root
    --tasMin->taille;
    transformerEnTasMin(tasMin, 0);
  
    return racine;
}







// A utility function to check if a given vertex
// 'v' is in min heap or not
bool estDansTasMin(struct TasMin *tasMin, int v)
{
    if (tasMin->pos[v] < tasMin->taille)
        return true;
    return false;
}



void dijkstra(graphe* g, int src)
{
    // Get the number of vertices in graph
    int V = g->n;
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V]; 
        // tasMin represents set E
    struct TasMin* tasMin = creerTasMin(V);
    // Initialize min heap with all 
    // vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        tasMin->tableau[v] = newNoedTasMin(v, 
                                      dist[v]);
        tasMin->pos[v] = v;
    }


    // Make dist value of src vertex 
    // as 0 so that it is extracted first
    tasMin->tableau[src] = 
          newNoedTasMin(src, dist[src]);
    tasMin->pos[src]   = src;
    dist[src] = 0;
    diminuerDis(tasMin, src, dist[src]);

    // Initially taille of min heap is equal to V
    tasMin->taille = V;



        // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!estVide(tasMin))
    {
        // Extract the vertex with 
        // minimum distance value
        struct NoedTasMin* noedTasMin = 
                     extraireMin(tasMin);
        
        // Store the extracted vertex number
        int u = noedTasMin->v; 
  
        // Traverse through all adjacent 
        // vertices of u (the extracted
        // vertex) and update 
        // their distance values
        msuc* pCrawl =
                     g->tab_sucs[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->sommet;
  
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its 
            // previously calculated distance
            if (estDansTasMin(tasMin, v) && 
                      dist[u] != INT_MAX && 
              pCrawl->valeur + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->valeur;
  
                // update distance 
                // value in min heap also
                diminuerDis(tasMin, v, dist[v]);
            }
            pCrawl = pCrawl->suivant;
        }
    }

    // print the calculated shortest distances
    printArr(dist, V);
}
  

  void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}






int main(){
        graphe g;

    graphe_stable(&g, 20, 20);
    graphe_ajouter_arc(&g, 0, 1, 4);
    graphe_ajouter_arc(&g, 0, 7, 8);
    graphe_ajouter_arc(&g, 1, 2, 8);
    graphe_ajouter_arc(&g, 1, 7, 11);
    graphe_ajouter_arc(&g, 2, 3, 7);
    graphe_ajouter_arc(&g, 2, 8, 2);
    graphe_ajouter_arc(&g, 2, 5, 4);
    graphe_ajouter_arc(&g, 3, 4, 9);
    graphe_ajouter_arc(&g, 3, 5, 14);
    graphe_ajouter_arc(&g, 4, 5, 10);
    graphe_ajouter_arc(&g, 5, 6, 2);
    graphe_ajouter_arc(&g, 6, 7, 1);
    graphe_ajouter_arc(&g, 6, 8, 6);
    graphe_ajouter_arc(&g, 7, 8, 7);
    graphe_ajouter_arc(&g, 4, 2, 10.3);
    dijkstra(&g,0);

}



