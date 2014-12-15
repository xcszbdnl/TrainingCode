#include <cstdio>
#include <string.h>

long long a, b, x, y;

long long gcd(long long m, long long n) {
	if (n == 0) {
		return m;
	}
	while (n) {
		long long c = n;
		n = m % n;
		m = c;
	}
	return m;
}

int main() {
	scanf("%I64d%I64d%I64d%I64d", &a, &b, &x, &y);
	long long k = gcd(x, y);
	if (y / x >= b) {
		printf("0 0\n");
		return 0;
	}
	long long x_1 = x / k;
	long long y_1 = y / k;
	long long c = a % x_1;
	if (y_1 * (a - c) / x_1 <= b) {
		printf("%I64d %I64d", a - c, y_1 * (a - c) / x_1);
		return 0;
	}
	long long m = y_1 * (a - c) / x_1 - b;
	if (m % y_1 == 0) {
		m = m / y_1;
	}
	else {
		m = m / y_1 + 1;
	}
	if (a - (m * x_1 + c) <= 0) {
		printf("0 0\n");
		return 0;
	}
	printf("%I64d %I64d\n", a - (m * x_1 + c), (a - (m * x_1 + c)) * y / x);
	return 0;
}
