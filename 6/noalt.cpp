#include <iostream>
#include <queue>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define MAX_NODES 505
#define MAX_EDGES 50005
// #define DEBUG 1

struct kruskal_result {
    int MSTCost;
    int numEdgesInMST;
    bool allUnique;
};

typedef struct kruskal_result kruskal_result;

struct edge {
    int start, end;
    int cost;
    bool ignore; // used to keep track of temporarily "deleted" edges.
    bool inMST;
    bool dupe; // are there other edges of this size
    bool alternative;
    bool operator<(struct edge other) const {
        return cost < other.cost;
    }
};

struct edge edges[MAX_EDGES];

using namespace std;

int uf_array[MAX_NODES];
kruskal_result kruskals (int numEdges, bool modify) {
    bool allUnique = true;
    int totalCost = 0;
    int numEdgesInMST = 0;

    // initialise Union Find
    for (int i = 0; i < MAX_NODES; i++) {
        uf_array[i] = i;
    }

    // Iterate over the edges and see which ones might be part of the MST.
    for (int i = 1; i <= numEdges; i++) {
        // If marked as skip, just skip it
        if (edges[i].ignore == true) continue;

        // While we're here, lets see if this is a dupe
        if (i >= 2) {
            if (edges[i - 1].cost == edges[i].cost) {
                edges[i-1].dupe = true;
                edges[i].dupe = true;
            }
        }

        // check to see if edges[i].start and end are in the same forest
        int startParent = uf_array[edges[i].start];
        while (startParent != uf_array[startParent]) {
            startParent = uf_array[startParent];
        }
        uf_array[edges[i].start] = startParent; // shortcutting.

        // Repeat this for edges[i].end
        int endParent = uf_array[edges[i].end];
        while (endParent != uf_array[endParent]) {
            endParent = uf_array[endParent];
        }
        uf_array[endParent] = endParent;

        if (startParent == endParent) { // same forest, skip this edge
            continue;
        } else { // different forests, join forests
            // Do a union
            uf_array[startParent] = endParent;

            // Register it as used
            if (modify == true) {
                edges[i].inMST = true;
            }

            // Add this to total cost
            totalCost += edges[i].cost;

            // Count this edge
            numEdgesInMST++;

            // Check uniqueness condition
            if (allUnique == true && edges[i].dupe == true) {
                allUnique = false;
            }

            continue;
        }
    }

    // build the result

    kruskal_result res;
    res.MSTCost = totalCost;
    res.numEdgesInMST = numEdgesInMST;
    res.allUnique = allUnique;
    return res;
}
    
int main (void) {

    int numNodes, numEdges;
    while (scanf ("%d %d", &numNodes, &numEdges) != EOF) {

        for (int i = 0; i < MAX_EDGES; i++) {
            edges[i].start = 0;
            edges[i].end = 0;
            edges[i].ignore = false;
            edges[i].inMST = false;
            edges[i].dupe = false;
            edges[i].alternative = false;
        }

        // Read edges in
        int edgeId = 1;
        for (int i = 0; i < numEdges; i++) {
            scanf ("%d %d %d", &edges[edgeId].start, &edges[edgeId].end, &edges[edgeId].cost);
            edgeId++;
        }

        assert (edgeId == numEdges + 1);

        // Now sort the edges. 
        sort (edges, edges + numEdges + 1);

#ifdef DEBUG
        printf ("vvvvvvvvvvvvvv DEBUG edge array vvvvvvvvvvvvvvv\n");
        for (int i = 1; i <= numEdges; i++) {
            printf ("%d %d->%d:%d\n", i, edges[i].start, edges[i].end, edges[i].cost);
        }
        printf ("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
#endif
        kruskal_result result = kruskals (numEdges, true); // argument used to designate whether to 
        // actually mark edges or just do the calculations.

        if (result.allUnique == true) { // if they are all unique weights, there's no possibility of another MST.
            printf ("%d %d", numNodes - 1, result.MSTCost);
            continue;
        } else {

            int numRequiredEdges = 0;
            int costRequiredEdges = 0;

            // we're going to try remove 1 MST edge at a time, 
            // recalculate MST and see if the weight changes, if it doesn't, we have an alternative.
            for (int i = 1; i <= numEdges; i++) { 
                if (edges[i].inMST == true && edges[i].dupe == true) {
                    // Lets try removing it see what happens.
                    edges[i].ignore = true;

                    kruskal_result temp_results = kruskals (numEdges, false); // new edges will not be marked

                    if (temp_results.MSTCost == result.MSTCost && // same cost
                            temp_results.numEdgesInMST >= numNodes - 1) { // All MSTs must have at least n-1 edges
                        // Then we have a new valid MST, thus this edge is not required.
                        edges[i].alternative = true;
                    }
                    edges[i].ignore = false;
                }
                
                if (edges[i].inMST == true && edges[i].alternative == false) {
#ifdef DEBUG 
                    printf ("Edge %d -> %d: %d required\n", edges[i].start, edges[i].end, edges[i].cost);
#endif
                    // There is no alternative!
                    numRequiredEdges++;
                    costRequiredEdges += edges[i].cost;
                }

            }

            // Print out the answer
            printf ("%d %d\n", numRequiredEdges, costRequiredEdges);
        }
    }
    return 0;
}




