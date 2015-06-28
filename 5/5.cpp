#include <cstdio>
#include <vector>
#include <set>
#include <functional>
#include <utility>
#include <unordered_map>

#define MAX 51
#define NUMDIR 4

using namespace std;

unordered_map<char, bool> roadmap[MAX][MAX];
int debug[MAX][MAX];

int n, xstart, ystart , T;

/* Note the ordering for set */
struct Move {
	int t;
	int x;
	int y;
	char dir;
	char nextdir;
	bool operator<(struct Move other) const {
		if (t == other.t) {
			if (x == other.x) {
				if (y == other.y) {
					if (dir == other.dir) {
						return nextdir < other.nextdir;
					}
					return dir < other.dir;
				}
				return y < other.y;
			}
			return x < other.x;
		}
        return t < other.t;
    }
};

set<Move> starts;
set<Move> moves;

void resetroadmap() {
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{	
			roadmap[i][j].clear();
		}
	}
}

void drive(char c, int d) {

	// printf("c = %c d = %d\n", c, d);
	while (!moves.empty()) {
		Move curr = *moves.begin();
		moves.erase(moves.begin());
		int t = curr.t;
		int x = curr.x;
		int y = curr.y;
		int dir = curr.dir;
		// printf("t = %d [%d][%d] %c %c\n", d-t, x, y, dir, prevdir);
		if (t == d) {
			/* Check if c EQUALS previous direction OR current direction OR next direction */
			if (dir == c) {
				curr.nextdir = '*';
				starts.insert(curr);
			} else if (c == 'N' && roadmap[x][y][c] && dir != 'S') {
				curr.nextdir = c;
				starts.insert(curr);
			} else if (c == 'S' && roadmap[x][y][c] && dir != 'N') {
				curr.nextdir = c;
				starts.insert(curr);
			} else if (c == 'E' && roadmap[x][y][c] && dir != 'W') {
				curr.nextdir = c;
				starts.insert(curr);	
			} else if (c == 'W' && roadmap[x][y][c] && dir != 'E') {
				curr.nextdir = c;
				starts.insert(curr);
			}
		} else {
			if (roadmap[x][y]['N'] && dir != 'S') {

				Move m;
				m.t = t+1;
				m.x = x;
				m.y = y+1;
				m.dir = 'N';

				moves.insert(m);

			}
			if (roadmap[x][y]['S'] && dir != 'N') {

				Move m;
				m.t = t+1;
				m.x = x;
				m.y = y-1;
				m.dir = 'S';

				moves.insert(m);

			}
			if (roadmap[x][y]['E'] && dir != 'W') {

				Move m;
				m.t = t+1;
				m.x = x+1;
				m.y = y;
				m.dir = 'E';

				moves.insert(m);

			}
			if (roadmap[x][y]['W'] && dir != 'E') {

				Move m;
				m.t = t+1;
				m.x = x-1;
				m.y = y;
				m.dir = 'W';

				moves.insert(m);

			}
		}
	}
}

int main() {
	while (scanf("%d%d%d%d", &n, &xstart, &ystart, &T) == 4) {
		starts.clear();
		moves.clear();
		resetroadmap();
		Move init;
		init.t = 0;
		init.x = xstart;
		init.y = ystart;
		init.dir = '*';
		init.nextdir = '*';
		starts.insert(init);
		for (int i = 0; i < n; ++i)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 == x2) {
				for (int j = min(y1, y2); j < max(y1, y2); ++j)
				{
					roadmap[x1][j]['N'] = true;
					roadmap[x1][j+1]['S'] = true;
				}
			} else {
				for (int j = min(x1, x2); j < max(x1, x2); ++j)
				{
					roadmap[j][y1]['E'] = true;
					roadmap[j+1][y1]['W'] = true;
				}
			}	
		}

		for (int i = 1; i <= T; ++i)
		{
			char c;
			int d;
			scanf("%d %c", &d, &c); 
			// printf("starts size %lu\n", starts.size());
			while (!starts.empty()) {
				Move curr = *starts.begin();
				starts.erase(starts.begin());
				char nextdir = curr.nextdir;
				curr.t = 0;
				if (nextdir == 'N') {
					curr.t = 1;
					curr.y += 1;
					curr.dir = 'N';
				}
				if (nextdir == 'S') {
					curr.t = 1;
					curr.y -= 1;
					curr.dir = 'S';
				}
				if (nextdir == 'E') {
					curr.t = 1;
					curr.x += 1;
					curr.dir = 'E';
				}
				if (nextdir == 'W') {
					curr.t = 1;
					curr.x -= 1;
					curr.dir = 'W';
				}
				moves.insert(curr);
			}
			drive(c, d);			
		}

		int x = -1;
		int y = -1;
		while (!starts.empty()) {
			Move curr = *starts.begin();
			starts.erase(starts.begin());
			if (!(x == curr.x && y == curr.y)) {
				printf("%d %d\n", curr.x, curr.y);
			}
			x = curr.x;
			y = curr.y;
		}
	}
}