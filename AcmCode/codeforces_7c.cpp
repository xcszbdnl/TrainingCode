#include <cstdio>
#include <string.h>

void gcd(long long a, long long b, long long &d, long long &x, long long &y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	}
	else {
		gcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}
long long a, b, c;
int main() {
	scanf("%I64d%I64d%I64d", &a, &b, &c);
	long long d, x, y;
	gcd(a, b, d, x, y);
	if (-c % d != 0) {
		printf("-1\n");
	}
	else {
		long long temp = -c / d;
		x = x * temp;
		y = y * temp;
		printf("%I64d %I64d\n", x, y);
	}
	return 0;
}