#include <cstdio>
#include <string.h>
#include <cmath>

const double eps = 1e-10;

long long getMod(long long a, long long b) {
	long long result = 1;
	long long k = a % 1000;
	while (b) {
		if (b & 1) {
			result = result * k % 1000;
		}
		k = k * k % 1000;
		b >>= 1;
	}
	return result;
}

long long getLead(long long a, long long b) {
	double log_10 = b * log10(a + eps);
	double ans = log_10 - (int)log_10;
	long long k = (long long)(pow(10, ans) * 100);
	return k;
}

int main() {
	long long test_case;
	scanf("%lld", &test_case);
	while (test_case--) {
		long long a, k;
		scanf("%lld%lld", &a, &k);
		long long traling = getMod(a, k);
		long long leading = getLead(a, k);
		printf("%lld...%03lld\n", leading, traling);
	}
	return 0;
}