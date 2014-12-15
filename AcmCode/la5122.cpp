#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 105;
const double eps = 1e-10;

long long fic[MAX_NUMBER];
long long factor[MAX_NUMBER];
int factor_number;
char low_string[MAX_NUMBER], high_string[MAX_NUMBER];

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	long long c;
	while (b) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

long long multi(long long a, long long b, long long n) {
	long long res = a % n;
	long long ans = 0;
	while (b) {
		if (b & 1) {
			ans = (ans + res) % n;
		}
		res = (res * 2) % n;
		b /= 2;
	}
	return ans;
}

long long getMod(long long a, long long b, long long n) {
	long long ans = 1;
	while (b) {
		if (b & 1) {
			ans = multi(ans, a, n);
		}
		a = multi(a, a, n);
		b /= 2;
	}
	return ans;
}

int millerRabin(long long number, int times) {
	if (number == 2) {
		return 0;
	}
	if (number == 1 || number % 2 == 0) {
		return 1;
	}
	long long a, x, y, u = number - 1;
	int t = 0;
	while (u % 2 == 0) {
		t++;
		u /= 2;
	}
	for (int i = 1; i <= times; i++) {
		a = (rand() % (number - 1)) + 1;
		x = getMod(a, u, number);
		y = x;
		for (int i = 0; i < t; i++) {
			y = multi(x, x, number);
			if (y == 1 && x != 1 && x != number - 1) {
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

long long pollardRho(long long number) {
	long long x, y, d, i = 1, k = 2;
	x = (rand() % (number - 1)) + 1;
	y = x;
	while (1) {
		i++;
		x = multi(x, x, number);
		d = gcd(y - x, number);
		if (d > 1 && d < number) {
			return d;
		}
		if (x == y) {
			return number;
		}
		if (i == k) {
			k = k * 2;
			y = x;
		}
	}
}

void findFactor(long long number) {
	if (number == 1) {
		return ;
	}
	if (!millerRabin(number, 6)) {
		factor[factor_number++] = number;
		return ;
	}
	long long p = number;
	while (p >= number) {
		p = pollardRho(number);
	}
	findFactor(p);
	findFactor(number / p);
}

int main() {
	fic[0] = 0;
	fic[1] = 1;
	for (int i = 2; i < MAX_NUMBER; i++) {
		fic[i] = fic[i - 1] + fic[i - 2];
	}
	int find;
	long long low, high;
	int first = 1;
	while (scanf("%s%s", low_string, high_string) != EOF) {
		low = 0;
		high = 0;
		for (int i = 2; low_string[i]; i++) {
			if (low_string[i] >= '0' && low_string[i] <= '9') {
				low = low * 16 + low_string[i] - '0';
			}
			else {
				low = low * 16 + low_string[i] - 'a';
			}
		}
		for (int i = 2; high_string[i]; i++) {
			if (high_string[i] >= '0' && high_string[i] <= '9') {
				high = high * 16 + high_string[i] - '0';
			}
			else {
				high = high * 16 + high_string[i] - 'a' + 10;
			}
		}
		if (low >= high) {
			break;
		}
		if (!first) {
			printf("\n");
		}
		int k = 0;
		while (fic[k] < low) {
			k++;
		}
		find = 0;
		printf("Range %I64d to %I64d:\n", low, high);
		for (int i = k; fic[i] <= high; i++) {
			find = 1;
			factor_number = 0;
			if (i == 0) {
				printf("Fib(0) = 0, lg does not exist\n");
			}
			else {
				double log_ans = log10(fic[i] + eps) / log10(2 + eps);
				printf("Fib(%d) = %I64d, lg is %.6lf\n", i, fic[i], log_ans);
				findFactor(fic[i]);
				sort(factor, factor + factor_number);
				if (factor_number == 0) {
					printf("No prime factors\n");
				}
				else {
					printf("Prime factors:");
					for (int j = 0; j < factor_number; j++) {
						printf(" %I64d", factor[j]);
					}
					printf("\n");
				}
			}
		}
		if (!find) {
			printf("No Fibonacci numbers in the range\n");
		}
		first = 0;
	}
	return 0;
}