#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

/* Minimum Spannign Tree Kruskals */

#define MAX_V 510
#define MAX_E 50010

using namespace std;

/* Marks all paths */
unordered_map<int, unordered_map<int, int> > alternate;
unordered_map<int, unordered_map<int, int> > valid;

struct edge
{
	int u;
	int v;
	int w;
	int valid;
};

bool operator<(const edge& a, const edge& b) {
 return a.w < b.w;
} 

edge edges[MAX_E];
int p[MAX_V];
int k;

void addEdge(int u, int v, int w) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	k++;
}

int root(int u) {
 	return u == p[u] ? u : p[u] = root(p[u]);
}

void join(int u, int v) {
  	u = root(u);
  	v = root(v);
  	p[u] = v;
}

int mst() {
	int n = k;
  	sort(edges, edges + n);
  	int total_weight = 0;
  	for (int i = 0; i < n; i++) {
  		edge e = edges[i];
  		//printf("%d->%d\n", e.u, e.v);
  		if (root(e.v) != root(e.u)) {
  			valid[e.v][e.u] = 1;
  			valid[e.u][e.v] = 1;
  			edges[i].valid = 1;
	  		total_weight += e.w;
	 		join(e.v, e.u);
	  	} else {
	  		k--;
	  		edges[i].w = 10010;
	  	}
	}
	sort(edges, edges + n);
 	return total_weight;
}

int n, m;
int seen1[MAX_V];
int seen2[MAX_V];
vector<int> set1;
vector<int> set2;

void dfs1(int u) {
	if (seen1[u]) return;
	set1.push_back(u);
	seen1[u] = 1;
	for (unordered_map<int, int>::iterator it = alternate[u].begin(); it != alternate[u].end(); it++)
	{
		if (valid[u][it->first]) {
			dfs1(it->first);
		}
	}
}

void dfs2(int u) {
	if (seen2[u]) return;
	set2.push_back(u);
	seen2[u] = 1;
	for (unordered_map<int, int>::iterator it = alternate[u].begin(); it != alternate[u].end(); it++)
	{
		if (valid[u][it->first]) {
			dfs2(it->first);
		}
	}
}


int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		alternate.clear();
		valid.clear();
		for (int i = 0; i < MAX_E; i++) {
			edges[i].u = 0;
	  		edges[i].v = 0;
	  		edges[i].w = 10010;
	  		edges[i].valid = 0;
		}
		k = 0;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			alternate[a][b] = c;
			alternate[b][a] = c;
		}
		for (int i = 0; i <= n; i++) {
			p[i] = i;
		}
		/* Create MST */
		mst();
			
		// for (int i = 0; i < k; i++) {
		// 	edge e = edges[i];
		// 	printf("mst %d <-> %d = %d %d\n", e.u, e.v, e.w, e.valid);	
		// }

		/* For every edge in the MST */
		for (int i = 0; i < k; i++) {
			edge e = edges[i];
			// printf("remove %d <-> %d = %d %d\n", e.u, e.v, e.w, e.valid);	

			/* Remove it and mark the resulting forest */
			set1.clear();
			set2.clear();
			memset(seen1, 0, sizeof seen1);
			memset(seen2, 0, sizeof seen2);
			seen1[e.v] = 1;
			seen2[e.u] = 1;
			dfs1(e.u);
			dfs2(e.v);
			

			/* Attempt to create an alternate path */

			// printf("set1\n");
			// for (int j = 0; j < set1.size(); j++) {
			// 	printf("%d ", set1[j]);
			// }
			// printf("\n");
			// printf("set2\n");
			// for (int j = 0; j < set2.size(); j++) {
			// 	printf("%d ", set2[j]);
			// }
			// printf("\n");
			

			for (int j = 0; j < set2.size(); j++) {
				int u = e.u;
				int v = set2[j];
				if (v == e.v) continue;
				if (alternate[u][v] == e.w) {
					edges[i].valid = 0; 
					break;
				}
			}
			for (int j = 0; j < set1.size(); j++) {
				int u = e.v;
				int v = set1[j];
				if (v == e.u) continue;
				if (alternate[u][v] == e.w) {
					edges[i].valid = 0; 
					break;
				}
			}
		}

		int counter = 0;
		int totalweight = 0;
		for (int i = 0; i < k; i++) {
			edge e = edges[i];
			// printf("%d <-> %d = %d %d\n", e.u, e.v, e.w, e.valid);

			if (e.valid) {
				counter++;
				totalweight += e.w;
			}
		}
		printf("%d %d\n", counter, totalweight);
	}	
}