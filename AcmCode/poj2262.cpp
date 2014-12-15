#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 1000000;

bool vis[MAX_NUMBER + 3];
int prime[MAX_NUMBER];
int prime_number, number;

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
		if (!vis[i] && (i % 2 == 1)) {
			prime[++prime_number] = i;
		}
	}
	vis[1] = 1;
}

int main() {
	getAllPrime();
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		int b, a, flag = 0;
		int min_ans = 0;
		for (int i = 1; i <= prime_number && prime[i] <= number / 2; i++) {
			int temp = number - prime[i];
			if (!vis[temp]) {
				flag = 1;
				min_ans = temp - prime[i];
				a = prime[i];
				b = temp;
				break;
			}
		}
		if (flag) {
			printf("%d = %d + %d\n", number, a, b);
		}
		else {
			printf("Goldbach's conjecture is wrong.\n");
		}
	}
	return 0;
}