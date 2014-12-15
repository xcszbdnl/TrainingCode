#include <cstdio>
#include <string.h>
#include <cmath>

const long long MOD = 1000000007;
const int MAX_NUMBER = 10000000; 

bool vis[MAX_NUMBER + 2] = {0};
int prime[MAX_NUMBER];
long long fact[MAX_NUMBER + 2];
int prime_number;
int number;

void getAllPrime() {
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


long long getInverse(long long a, long long power_number) {
	long long ans = 1;
	while (power_number > 0) {
		if (power_number & 1) {
			ans = (ans * a) % MOD;
		}
		a = (a * a) % MOD;
		power_number /= 2;
	}
	return ans;
}

int getSum(int cnt_number, int factor) {
	int ans = 0;
	while (cnt_number > 0) {
		ans += cnt_number / factor;
		cnt_number /= factor;
	}
	return ans;
}

int main() {
	getAllPrime();
	fact[1] = 1;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		long long to_dive = 1;
		for (int i = 1; i <= prime_number && prime[i] <= number; i++) {
			int power = getSum(number, prime[i]);
			if (power & 1) {
				to_dive = (to_dive * prime[i]) % MOD;
			}
		}
		to_dive = getInverse(to_dive, MOD - 2);
		printf("%I64d\n", (fact[number] * to_dive) % MOD);
	}
	return 0;
}