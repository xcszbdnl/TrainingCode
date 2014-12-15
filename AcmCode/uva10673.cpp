#include <cstdio>
#include <string.h>
long long x, k, p, q, c, d;

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%I64d%I64d", &x, &k);
		c = x / k;
		d = (x / k) + (x % k > 0);
		for (p = 0; c != 0 && p <= x / c; p++) {
			if ((x - p * c) % d == 0) {
				break;
			}
		}
		q = (x - p * c) / d;
		printf("%I64d %I64d\n", p, q);
	}
	return 0;
}