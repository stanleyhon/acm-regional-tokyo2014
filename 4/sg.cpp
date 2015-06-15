#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <float.h>

using namespace std;

vector < pair <double ,double> > obstacles;
int totalDistance, numObstacles, maxBounces;

double check (double perHop) {
    double smallestVx = 0xFFFFFFFF;
    // for each post, check what sort of Vx we need to clear it
    for (vector < pair <double, double> >::iterator it = obstacles.begin();
         it != obstacles.end();
         it++) {

        double postDistance = it->first; // need to shorten this to closest hop
        while (perHop < postDistance) {
            postDistance = postDistance - perHop;
        }

        double postHeight = it->second;
        
        // This equation, given:
        //    - The height of the post
        //    - The distance to the post
        //    - the hop distance (i.e. distance to bounce point)
        // Gives us the minimum Vx required to clear it.
        // For a proof, see notes.
        double clearPostVx = (perHop * postDistance - postDistance * postDistance) / (2 * postHeight);

        // We take the smallestVx, since the relationship between Vx and Vy are inverse,
        // in that, shooting it with a very fast vx, means relatively little opportunity 
        // for vy to grow.
        smallestVx = min (smallestVx, clearPostVx);
    }

    // Using the initial equations relating to Vx and Vy, and the combined speed equations,
    // It can be shown that, in the graph of all possible combined velocities satisying our scenario
    // that there is a minimum at V = hopDistance / 2; (see notes for more information)
    
    // If the vx to clear a post has been found to be larger than hopDistance / 2, just take hopDistance / 2
    // As this is a more optimal solution.
    smallestVx = min (smallestVx, perHop / 2); 

    // NOTE: smallestVx at this point is actualy Vx^2
    // This equation is derived from 2 vx vy = hop distance
    // Rearranging this equation as a definition for vy in terms of vx then squaring 
    // gives us this result. 
    double VySquared = (perHop * perHop) / (4 * smallestVx);
    // Using the given combined velocity formula, apply it to vx and vy.
    double resultV = sqrt (smallestVx + VySquared);
    return resultV;
}

void work (void) {
    double minimalVelocity = 0xFFFFFFFF;
    // Try every bounce num    
    for (double bounces = 0; bounces <= maxBounces; bounces++) {
        // for 0 bounces, you have 1 segment.
        // for 1 bounce, you have two segments.
        // hence + 1

        // F**$!@#ing type conversions/promotion BS just cast everything
        double distancePerHop = double(totalDistance) / double(bounces + 1);
        minimalVelocity = min (minimalVelocity, check (distancePerHop));
    }

    printf ("%.5lf\n", minimalVelocity);
}

int main (void) {
    while (scanf ("%d %d %d", &totalDistance, &numObstacles, &maxBounces) != EOF) {
        obstacles.clear();

        // read in obstacles
        while (numObstacles > 0) {
            int distanceToPost, height;
            scanf ("%d %d", &distanceToPost, &height);
            obstacles.push_back (make_pair (distanceToPost, height));
            numObstacles--;
        }

        work();
    }
    return 0;
}
