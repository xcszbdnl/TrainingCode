#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 100000;

bool vis[MAX_NUMBER + 1];
int prime[MAX_NUMBER], factor[MAX_NUMBER];
int prime_number;

void getAllPrime() {
	memset(vis, 0, sizeof(vis));
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				vis[j] = 1;
			}
		}
	}
	prime_number = 0;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		if (!vis[i]) {
			prime[++prime_number] = i;
		}
	}
}

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	getAllPrime();
	int number;
	while (scanf("%d", &number) != EOF) {
		memset(factor, 0, sizeof(factor));
		if (!number) {
			break;
		}
		int ans = 0;
		for (int i = 1; i <= prime_number; i++) {
			while (number % prime[i] == 0) {
				number /= prime[i];
				factor[i]++;
			}
		}
		int first = 0;
		int flag = 0;
		int first_factor;
		for (int i = 1; i <= prime_number; i++) {
			if (factor[i] != 0) {
				if (first == 0) {
					first_factor = factor[i];
					first = 1;
				}
				else {
					first_factor = gcd(first_factor, factor[i]);
				}
			}
		}
		if (first == 0) {
			first_factor = 1;
		}
		if (number < 0) {
			while (first_factor % 2 == 0) {
				first_factor = first_factor / 2;
			}
			printf("%d\n", first_factor);
		}
		else {
			printf("%d\n", first_factor);
		}
	}
	return 0;
}