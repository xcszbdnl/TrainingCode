#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_LENGTH = 1000006;
const int MAX_PRIME = 50000;

bool vis[MAX_PRIME + 2];
bool is_prime[MAX_LENGTH];
int prime[MAX_PRIME];
int prime_number;

void getAllPrime() {
	memset(vis, 0, sizeof(vis));
	int m = (int)sqrt(MAX_PRIME + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_PRIME; j += i) {
				vis[j] = 1;
			}
		}
	}
	prime_number = 0;
	for (int i = 2; i <= MAX_PRIME; i++) {
		if (!vis[i]) {
			prime[++prime_number] = i;
		}
	}
}

void getSegmentPrime(long long left, long long right) {
	memset(is_prime, true, sizeof(is_prime));
	if (left == 1) {
		is_prime[0] = 0;
	}
	for (long long i = 1; i <= prime_number && prime[i] * prime[i] <= right; i++) {
		long long begin = (left / prime[i]) + (left % prime[i] > 0);
		if (begin == 1) {
			begin++;
		}
		for (long long j = begin * prime[i]; j <= right; j = j + prime[i]) {
			is_prime[j - left] = 0;
		}
	}
}

int main() {
	getAllPrime();
	long long left, right;
	while (scanf("%I64d%I64d", &left, &right) != EOF) {
		getSegmentPrime(left, right);
		int flag = 0;
		int first = 1;
		long long pre, dist_1, dist_2, closet_1, closet_2;
		long long max_dist = -1;
		long long min_dist = MAX_LENGTH;
		for (long long i = left; i <= right; i++) {
			if (is_prime[i - left]) {
				if (first != 1) {
					long long temp = i - pre;
					flag = 1;
					if (temp > max_dist) {
						dist_1 = pre;
						dist_2 = i;
						max_dist = temp;
					}
					if (temp < min_dist) {
						closet_1 = pre;
						closet_2 = i;
						min_dist = temp;
					}
				}
				first = 0;
				pre = i;
			}
		}
		if (!flag) {
			printf("There are no adjacent primes.\n");
		}
		else {
			printf("%I64d,%I64d are closest, %I64d,%I64d are most distant.\n", closet_1, closet_2, dist_1, dist_2);
		}
	}
	return 0;
}