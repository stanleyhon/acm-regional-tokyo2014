#include <cstdio>
#include <cstring>

#define MAX 300010

int next;

void fix(int w) {
	int x = couples[w];
	int y = next[w];
	int z = couples[y];

	printf("w %d x %d y %d z %d\n", w, x, y, z);
	couples[w] = y;
	couples[y] = w;
	couples[z] = x;
	couples[x] = z;

	printf("%d\n", x+1);
}

int main() {
	int stack[MAX], st = 0;
	stack[0] = 0;
	int N, Q;
	scanf("%d%d\n", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%c", &str[i]);
		if (str[i] == '(') {
			couples[i] = i;
			stack[++st] = i;
		} else {
			couples[i] = stack[st--];
			couples[couples[i]] = i;
		}
	}

	st = 0;
	stack[st] = 0;
	for (int i = N-1; i >= 0; i--) {
		if (str[i] == ')') {
			next[i] = stack[st];
			stack[++st] = i;
		} else {
			next[i] = 0;
			st--;
		}
	}
	for (int j = 0; j < N; j++) {
		printf("%d", couples[j]);
	}
	printf("\n");
	for (int j = 0; j < N; j++) {
		printf("%d", next[j]);
	}
	printf("\n");
	for (int j = 0; j < N; j++) {
		if (couples[j] > j) {
			printf("(");
		} else {
			printf(")");
		}
	}
	printf("\n");

	for (int i = 0; i < Q; ++i)
		{
		int w;
		scanf("%d", &w);

		if (couples[w-1] > w-1) {
			printf("%d\n", w);
			continue;
		}
		fix(w-1);

		for (int j = 0; j < N; j++) {
			printf("%d", couples[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++) {
			printf("%d", next[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++) {
			if (couples[j] > j) {
				printf("(");
			} else {
				printf(")");
			}
		}
		printf("\n");

	}
}