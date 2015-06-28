#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;

#define MAX 300010
#define DEBUG

int N, Q;
char str[MAX];
int group[MAX];
int depth[MAX];
int switchopen[MAX];
int switchclose[MAX];
int firstopen;
int firstclose;

void printstr() {
	for (int i = 1; i <= N; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

void printgroup() {
	for (int i = 1; i <= N; i++) {
		printf("%d", group[i]);
	}
	printf("\n");
}

void printdepth() {
	for (int i = 1; i <= N; i++) {
		printf("%d", depth[i]);
	}
	printf("\n");
}

void printswopen() {
	for (int i = 1; i <= N; i++) {
		printf("%d", switchopen[i]);
	}
	printf("\n");
}

void printswclose() {
	for (int i = 1; i <= N; i++) {
		printf("%d", switchclose[i]);
	}
	printf("\n");
}

void doswitchopen(int N) {
	int st = 1;
	firstclose = -1;
	memset(switchopen, 0, sizeof switchopen);
	for (int i = 2; i < N; i++) {
		if (str[i] == ')' && firstclose == -1 && st == 1) {
			printf("firstclose = %d\n", i);
			firstclose = i;
		} else if (str[i] == '(') {
			st++;
			if (firstclose != -1) {
				switchopen[i] = 1;
			}
		} else {
			st--;
		}
	} 
}

void doswitchclose(int N) {
	int st = 1;
	firstopen = -1;
	memset(switchclose, 0 , sizeof switchclose);
	for (int i = 2; i < N; i++) {
		if (str[i] == '(' && firstopen == -1 && st > 0) {
			printf("firstopen = %d\n", i);
			firstopen = i;
		} else if (str[i] == ')') {
			st--;
			if (firstopen != -1) {
				switchclose[i] = 1;
			}
		} else {
			st++;
		}
	}

}

int main() {

	while (scanf("%d%d\n", &N, &Q) == 2) {

		int T = 0;
		int st = 0;

		for (int i = 1; i <= N; i++) {
			scanf("%c", &str[i]);
			// When the stack is empty increment the group counter
			if (st == 0) {
				T++;
			}
			// if '('' push onto stack, else remove
			if (str[i] == '(') {
				st++;
				depth[i] = st;
			} else {
				depth[i] = st;
				st--;
			}
			group[i] = T;
		}

		doswitchopen(N);
		doswitchclose(N);
		printstr();
		// printgroup();
		printdepth();
		printswopen();
		printswclose();

		for (int i = 0; i < Q; ++i)
		{
			int target;
			scanf("%d", &target);
			if (str[target] == '(') {
				if (switchopen[target]) {
					str[target] = ')';
					str[firstclose] = '(';
					printf("%d\n", firstclose);
					doswitchopen(N);
					doswitchclose(N);
					printstr();
					// printdepth();
					printswopen();
					printswclose();	
				} else {
					printf("%d\n", target);
				}
			} else {
				if (switchclose[target]) {
					str[target] = '(';
					str[firstopen] = ')';
					printf("%d\n", firstopen);
					doswitchopen(N);
					doswitchclose(N);
					printstr();
					// printdepth();
					printswopen();
					printswclose();
				} else {
					printf("%d\n", target);
				}
			}

		}
	}
}