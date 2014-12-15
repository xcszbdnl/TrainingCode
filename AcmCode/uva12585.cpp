#include <cstdio>
#include <string.h>

const double eps = 1e-9;
double ans;

double dfs(int a, int b, int r, double p) {
	if (p < eps) {
		return 0;
	}
	if (a == b) {
		ans += p / 2;
		return r * p;
	}
	if (a > b) {
		ans += p / 2;
		return r * p / 2 + dfs(a - b, 2 * b, r + 1, p / 2);
	}
	else {
		return r * p / 2 + dfs(2 * a, b - a, r + 1, p / 2);
	}
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	int case_number = 1;
	while (test_case--) {
		int a, b;
		ans = 0;
		scanf("%d%d", &a, &b);
		double round = dfs(a, b, 1, 1.0);
		printf("Case %d: %.6lf %.6lf\n", case_number, round, ans);
		case_number++;
	}
	return 0;
}