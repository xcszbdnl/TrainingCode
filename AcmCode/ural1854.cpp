#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;
const int MAX_NUMBER = 1005;

long long value[MAX_NUMBER];
long long number;
int prim_number;

inline long long multi(long long a, long long b, long long n) {
	long long res = a % n;
	long long ans = 0;
	while (b > 0) {
		if (b & 1) {
			ans = (ans + res) % n;
		}
		res = (res << 1) % n;
		b >>= 1;
	}
	return ans;
}

inline long long getMod(long long a, long long b, long long n) {
	long long ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = multi(ans, a, n);
		}
		a = multi(a, a, n);
		b >>= 1;
	}
	return ans;
}

inline long long gcd(long long a, long long b) {
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

inline int millerRabin(long long n, long long times) {
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
		a = (rand() % (n - 1)) + 1;
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

inline long long pollardRho(long long n, int c) {
	long long x, y, d, k = 2, i = 1;
	x = (rand() % (n - 1)) + 1;
	y = x;
	while (1) {
		i++;
		x = (multi(x, x, n) + c) % n;
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

void findFactor(long long n, int k) {
	if (n == 1) {
		return ;
	}
	if (!millerRabin(n, 6)) {
		value[++prim_number] = n;
		return ;
	}
	long long p = n;
	while (p >= n || p == 1) {
		p = pollardRho(p, k--);
	}
	findFactor(p, k);
	findFactor(n / p, k);
}


int main() {
	srand(time(0));
	prim_number = 0;
	scanf("%I64d", &number);
	//clock_t t1 = clock();
	findFactor(number, 75);
	sort(value + 1, value + 1 + prim_number);
	//clock_t t2 = clock();
	//printf("Time %d\n", t2-t1);
	long long ans = number;
	long long pre = 1;
	long long pre_number = 0;
	value[prim_number + 1] = 1;
	for (int i = 1; i <= prim_number + 1; i++) {
		if (value[i] != pre) {
			if (pre_number & 1) {
				ans /= pre;
			}
			pre = value[i];
			pre_number = 1;
		}
		else {
			pre_number++;
		}
	}
	printf("%I64d\n", ans);
	//clock_t t3 = clock();
	//printf("Time2 %d\n", t3-t1);
	return 0;
}