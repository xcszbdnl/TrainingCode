#include <cstdio>
#include <string.h>

int a, b, c;

int main() {
	while (scanf("%d%d%d", &a, &b, &c) != EOF) {
		double ans = 0;
		ans = a * 1.0 / (a + b + 0.0) * b * 1.0 / (a - c + b + 0.0 - 1);
		ans = ans + b * 1.0 / (a + b + 0.0) * (b - 1) * 1.0 / (a + b - c + 0.0 - 1);
		printf("%.5lf\n", ans);
	}
	return 0;
}