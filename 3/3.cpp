#include <cstdio>
#include <algorithm>
#include <utility>

#define x first
#define y second
using namespace std;



typedef pair<int, int> Edge;

// bool operator<(const Edge& a, const Edge& b) {
//  return a.y < b.y;
// } 

Edge edges[1001];


int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		// printf("TEST\n");
		int totalcost = 0;
		for (int i = 0; i < m; ++i)
		{		
			int c, d;
			scanf("%d%d", &c, &d);
			edges[i] = make_pair(c, d);
		}
		sort(edges, edges+m);
		int currbase = 0;
		int currtop = 0;
		for (int i = 0; i < m; ++i)
		{	
			Edge e = edges[i];
			// printf("%d %d\n", e.x, e.y);
			if (e.x <= currtop) {
				if (e.y > currtop) {
					currtop = e.y;
					// printf("UPDATE %d <-> %d \n", currbase, currtop);
				}
			} else {
				if (currtop != 0) {
					// printf("ADD %d <-> %d = %d\n", currbase, currtop, 3 * (currtop - currbase));
					totalcost += 2 * (currtop - currbase);
				}
				// printf("UPDATE %d <-> %d \n", currbase, currtop);
				// printf("ADD %d -> %d = %d\n", e.x, currtop, e.x - currtop);
				currbase = e.x;
				currtop = e.y;
				// printf("NEW %d <-> %d \n", currbase, currtop);
			}
		}
		if (currtop != 0) {
			// printf("ADD %d <-> %d = %d\n", currbase, currtop, 3 * (currtop - currbase));
			totalcost += 2 * (currtop - currbase);
		}
		// printf("ADD %d -> %d \n", n+1, currtop);
		totalcost += n+1;
		printf("%d\n", totalcost);

	}
}