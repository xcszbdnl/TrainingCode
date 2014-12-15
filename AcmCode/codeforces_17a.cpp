#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 1005;
bool vis[MAX_NUMBER + 2];
bool addSum[MAX_NUMBER * 5];
int prime[MAX_NUMBER];
int prime_number;

void getAllPrime() {
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	memset(vis, 0, sizeof(vis));
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

int main() {
	getAllPrime();
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i < prime_number; i++) {
		int sums = prime[i] + prime[i + 1] + 1;
		if (!vis[sums]) {
			addSum[sums] = 1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (addSum[i]) {
			ans++;
		}
	}
	if (ans >= k) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}