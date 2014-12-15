#include <cstdio>
#include <string.h>
#include <cmath>
long long a_1, p_1;
long long getMod(long long a, long long b) {
	if (b == 1) {
		return a;
	}
	long long ans = getMod(a, b / 2);
	ans = (ans * ans) % p_1;
	if (b % 2 == 1) {
		ans = (ans * a) % p_1;
	}
	return ans;
}

int isPrime(long long cnt_number) {
	long long m = (long long)sqrt(cnt_number + 0.5);
	for (int i = 2; i <= m; i++) {
		if (cnt_number % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	while (scanf("%I64d%I64d", &p_1, &a_1) != EOF) {
		if (!p_1 && !a_1) {
			break;
		}
		if (isPrime(p_1)) {
			printf("no\n");
		}
		else {
			long long ans = getMod(a_1, p_1);
			if (ans == a_1) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
		}
	}
	return 0;
}