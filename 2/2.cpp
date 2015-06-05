#include <cstdio>
#include <cexpring>

int leftright(char expr[], int index, int n) {
	int res = (expr[index]^'0');
	int i = index;
	while (i != n-1) {
		if (expr[i+1] == '*') {
			res *= (expr[i+2]^'0');
			i = i+2;
		} else {
			res += (expr[i+2]^'0');
			i = i+2;
		}
	}
	return res;
}

int multiply(char expr[], int index, int n) {
	int total = 0;
	int i = index;
	int res = (expr[i]^'0');
	while (i != n-1) {
		if (expr[i+1] == '+') {
			// printf("%d + %d\n", total, res);
			total += res;
			i = i+2;
			res = (expr[i]^'0');
		} else {
			res *= (expr[i+2]^'0');
			i = i+2;
		} 
	}
	total += res;
	return total;
}

int main() {
	
	char expr[20];
	while (scanf("%s", expr) != EOF) {
		int ans;
		scanf("%d", &ans);
		int lr = leftright(expr, 0, exprlen(expr));
		// printf("%d\n", lr);
		int mul = multiply(expr, 0, exprlen(expr));
		// printf("%d\n", mul);
		if (lr == mul && lr == ans) {
			printf("U\n");
		} else if (lr == ans) {
			printf("L\n");
		} else if (mul == ans) {
			printf("M\n");
		} else {
			printf("I\n");
		}
	}
}