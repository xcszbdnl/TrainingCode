#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
const int MAX_NUMBER = 1005;

long long value[MAX_NUMBER];
long long a, b;
int prime_number;

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
		value[++prime_number] = n;
		return ;
	}
	long long p = n;
	while (p >= n) {
		p = pollardRho(p);
	}
	findFactor(p);
	findFactor(n / p);
}
long long min_number, ans, number;
int s;

void dfs(long long cnt_number, int cnt_order) {
    if (cnt_number * cnt_number > number) {
        return ;
    }
    if (cnt_order == s + 1) {
        if (cnt_number + number / cnt_number < min_number) {
            min_number = cnt_number + number / cnt_number;
            ans = cnt_number;
        }
        return ;
    }
    dfs(cnt_number * value[cnt_order], cnt_order + 1);
    dfs(cnt_number, cnt_order + 1);
}

int main() {

	srand(0);
	while (scanf("%lld%lld", &a, &b) != EOF) {
        memset(value, 0, sizeof(value));
        if (a == b) {
            printf("%lld %lld\n", a, b);
            continue;
        }
        prime_number = 0;
        number = b / a;
        findFactor(number);
        min_number = number + 1;
        s = 1;
        sort(value + 1, value + 1 + prime_number);
        for (int i = 2; i <= prime_number; i++) {
            if (value[i] != value[i - 1]) {
                value[++s] = value[i];
            }
            else {
                value[s] *= value[i];
            }
        }
        dfs(1, 1);
        long long ans_1 = a * ans;
        long long ans_2 = a * (number / ans);
        if (ans_1 > ans_2) {
            printf("%lld %lld\n", ans_2, ans_1);
        }
        else {
            printf("%lld %lld\n", ans_1, ans_2);            
        }
	}
	return 0;
}
