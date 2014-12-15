#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 10005;

int sums[MAX_NUMBER], prime[MAX_NUMBER];
int prime_number;
int number;

void getAllPrime() {
	prime_number = 1;
	prime[1] = 2;
	for (int i = 3; i < MAX_NUMBER; i++) {
		int j;
		for (j = 1; prime[j] * prime[j] <= i; j++) {
			if (i % prime[j] == 0) {
				break;
			}
		}
		if (prime[j] * prime[j] > i) {
			prime[++prime_number] = i;
		}
	}
}

int main() {
	getAllPrime();
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		for (int i = 1; i <= prime_number; i++) {
			sums[i] = sums[i - 1] + prime[i];
		}
		int ans = 0;
		for (int i = 0; i < prime_number; i++) {
			for (int j = i + 1; j <= prime_number; j++) {
				if (sums[j] - sums[i] == number) {
					ans++;
				}
				else if (sums[j] - sums[i] > number) {
					break;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}