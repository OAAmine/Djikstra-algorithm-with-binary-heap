#include <stdlib.h> /* rand */

struct TasMinNoed
{
    int v;
    int dist;
};typedef struct TasMinNoed tasminnoed;


struct TasMin
{
    
    // Number of heap nodes present currently
    int taille;

    // Capacity of min heap
    int capacite;

    // This is needed for decreaseKey()
    int *pos;
    struct TasMinNoed **tableau;
};

// A utility function to create a
// new Min Heap Node
struct TasMinNoed *newTasMinNoed(int v,
                                   int dist)
{
    struct TasMinNoed *tasMinNoed =
        (struct TasMinNoed *)
            malloc(sizeof(struct TasMinNoed));
    tasMinNoed->v = v;
    tasMinNoed->dist = dist;
    return tasMinNoed;
}

// A utility function to create a Min Heap
struct TasMin *createMinHeap(int capacite)
{
    struct TasMin *tasMin =
        (struct MinHeap *)
            malloc(sizeof(struct TasMin));
    tasMin->pos = (int *)malloc(
        capacite * sizeof(int));
    tasMin->taille = 0;
    tasMin->capacite = capacite;
    tasMin->tableau =
        (struct TasMinNoed **)
            malloc(capacite *
                   sizeof(struct TasMinNoed *));
    return tasMin;
}   


// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void permuterTasMinNoed(struct TasMinNoed **a,
                     struct TasMinNoed **b);





// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void transformer_en_TasMin(struct TasMin *minHeap,
                int indice);


// A utility function to check if
// the given minHeap is empty or not
int estVide(struct TasMin *tasMin);



// Standard function to extract
// minimum node from heap
struct TasMinNoed *get_min(struct TasMin *
                                   tasMin);



// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decrementerCle(struct TasMin *tasMin,
                 int v, int dist)
{


// A utility function to check if a given vertex
// 'v' is in min heap or not
bool inclusDansTasMin(struct TasMin *tasMin, int v);


