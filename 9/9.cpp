#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define MAX 160
#define ALICE 0

struct ball {
	int nutri;
	int deli;
} balls[MAX];

int n;

unordered_map<int, unordered_map<int, unordered_map<int, int> > > cache;

/*
	If we have less energy than our opponent then we must eat the ball
	Else we can choose to skip
*/
int findmax(int u, int a, int b, int player) {

	// printf("findmax %d %d %d %d\n", u, a, b, player);
	if (u == n) return 0;
	int nutri = balls[u].nutri;
	int deli = balls[u].deli;

	if (player == ALICE) {
		if (a <= b) {
			if (cache[u+1][nutri-(b-a)][!player] == 0) {
				cache[u+1][nutri-(b-a)][!player] = findmax(u+1, nutri, b - a, !player);
				// printf("%d %d\n", findmax(u+1, nutri, b - a, !player), cache[u+1][nutri-(b-a)][!player]);
			}
			return deli + cache[u+1][nutri-(b-a)][!player];
			// return deli + findmax(u+1, nutri, b - a, !player);
		} else {
			if (cache[u+1][a+nutri-b][!player] == 0) {
				cache[u+1][a+nutri-b][!player] = findmax(u+1, a+nutri-b, 0, !player);
				// printf("%d %d\n", findmax(u+1, a+nutri-b, 0, !player), cache[u+1][a+nutri-b][!player]);
			}
			if (cache[u][a-b][!player] == 0) {
				cache[u][a-b][!player] = findmax(u, a, b, !player);
			}
			return max(deli + cache[u+1][a+nutri-b][!player], cache[u][a-b][!player]);
			// return max(deli + findmax(u+1, a+nutri-b, 0, !player), findmax(u, a, b, !player));
		}
	} else {
		if (b < a) {
			if (cache[u+1][(a-b)-nutri][!player] == 0) {
				cache[u+1][(a-b)-nutri][!player] = findmax(u+1, a - b, nutri, !player);
			}
			return cache[u+1][(a-b)-nutri][!player];
			// return findmax(u+1, a - b, nutri, !player);
		} else {
			if (cache[u+1][-(b+nutri-a)][!player] == 0) {
				cache[u+1][-(b+nutri-a)][!player] = findmax(u+1, 0, b+nutri-a, !player);
			}
			if (cache[u][a-b][!player] == 0) {
				cache[u][a-b][!player] = findmax(u, a, b, !player);
			}
			return min(cache[u+1][-(b+nutri-a)][!player], cache[u][a-b][!player]);
			// return min(findmax(u+1, 0, b+nutri-a, !player), findmax(u, a, b, !player));
		}
	}
}


int main() {
	int x, y;
	while (scanf("%d%d%d", &n, &x, &y) == 3) {
		int totaldeli = 0;
		cache.clear();
		for (int i = 0; i < n; ++i)
		{
			int r, s;
			scanf("%d%d", &r, &s);
			balls[i].nutri = r;
			balls[i].deli = s;
			totaldeli += s;
		}
		int alice = findmax(0, x, y, ALICE);
		int brianna = totaldeli - alice;
		printf("%d %d\n", alice, brianna);
	}
}