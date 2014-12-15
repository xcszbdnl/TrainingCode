#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 500006;

int phi[MAX_NUMBER + 1];

void getPhi() {
	for (int i = 2; i <= MAX_NUMBER; i++) {
		phi[i] = 0;
	}
	phi[1] = 1;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		if (!phi[i]) {
			for (int j = i; j <= MAX_NUMBER; j += i) {
				if (!phi[j]) {
					phi[j] = j;
				}
				phi[j] = phi[j] / i * (i - 1);
			}
		}
	}
}

long long number;

int main() {
	getPhi();
	while (scanf("%lld", &number) != EOF) {
		if (!number) {
			break;
		}
		long long ans = 0;
		for (int i = 1; i <= number; i++) {
			ans += phi[i];
		}
		printf("%lld\n", ans * 2 - 1);
	}
	return 0;
}