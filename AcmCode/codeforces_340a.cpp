#include <cstdio>
#include <string.h>


long long a, b, x, y;

long long gcd(long long n, long long m) {
	if (m == 0) {
		return n;
	}
	while (m != 0) {
		long long c = m;
		m = n % m;
		n = c;
	}
	return n;
}

int main() {
	scanf("%I64d%I64d%I64d%I64d", &a, &b, &x, &y);
	long long ans = gcd(a, b);
	ans = a * b / ans;
	long long temp = ans;
	if (x >= ans) {
		if (x % ans != 0) {
			ans = ans * (x / ans) + ans;
		}
		else {
			ans = ans * (x / ans);
		}
	}
	if (y < ans) {
		printf("0\n");
		return 0;
	}
	int number = (y - ans) / temp + 1;
	printf("%d\n", number);
	return 0;
}
