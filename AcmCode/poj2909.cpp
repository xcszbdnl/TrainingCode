#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 70000;
bool vis[MAX_NUMBER + 1];
int prime[MAX_NUMBER];
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
	vis[1] = 1;
}

int number;

int main() {
	getAllPrime();
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		int ans = 0;
		for (int i = 1; i <= prime_number && prime[i] <= number / 2; i++) {
			int temp = number - prime[i];
			if (!vis[temp]) {
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}