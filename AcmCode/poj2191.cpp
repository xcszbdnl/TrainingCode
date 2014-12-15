#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 1005;

long long value[MAX_NUMBER];
int prim_number;

long long multi(long long a, long long b, long long n) {
	long long res = a % n;
	long long ans = 0;
	while (b > 0) {
		if (b & 1) {
			ans = (ans + res) % n;
		}
		res = (res * 2) % n;
		b = b / 2;
	}
	return ans;
}

long long getMod(long long a, long long b, long long n) {
	long long ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = multi(ans, a, n);
		}
		a = multi(a, a, n);
		b = b / 2;
	}
	return ans;
}

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	long long c;
	while (b != 0) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

int millerRabin(long long n, long long times) {
	if (n == 2) {
		return 0;
	}
	if (n == 1 || n % 2 == 0) {
		return 1;
	}
	long long u = n - 1;
	long long a, x, y;
	int t = 0;
	while (u % 2 == 0) {
		t++;
		u /= 2;
	}
	for (int i = 0; i < times; i++) {
		a = rand() % (n - 1) + 1;
		x = getMod(a, u, n);
		for (int j = 0; j < t; j++) {
			y = multi(x, x, n);
			if (y == 1 && x != 1 && x != n - 1) {
				return 1;
			}
			x = y;
		}
		if (y != 1) {
			return 1;
		}
	}
	return 0;
}

long long pollardRho(long long n) {
	long long x, y, d, k = 2, i = 1;
	x = (rand() % (n - 1)) + 1;
	y = x;
	while (1) {
		i++;
		x = multi(x, x, n) % n;
		d = gcd(y - x, n);
		if (d > 1 && d < n) {
			return d;
		}
		if (y == x) {
			return n;
		}
		if (i == k) {
			k = k * 2;
			y = x;
		}
	}
}

void findFactor(long long n) {
	if (n == 1) {
		return ;
	}
	if (!millerRabin(n, 6)) {
		value[++prim_number] = n;
		return ;
	}
	long long p = n;
	while (p >= n) {
		p = pollardRho(p);
	}
	findFactor(p);
	findFactor(n / p);
}

int main() {
	srand(0);
	int number;
	while (scanf("%d", &number) != EOF) {
		for (int i = 11; i <= number; i++) {
			long long n = (1LL << i) - 1;
			if (millerRabin(i, 30)) {
				continue;
			}
			if (!millerRabin(n, 30)) {
				continue;
			}
			prim_number = 0;
			findFactor(n);
			sort(value + 1, value + 1 + prim_number);
			for (int j = 1; j < prim_number; j++) {
				printf("%I64d * ", value[j]);
			}
			printf("%I64d = %I64d = ( 2 ^ %d ) - 1\n", value[prim_number], n, i);
		}
	}
	return 0;
}