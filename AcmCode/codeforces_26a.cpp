#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 3005;

int vis[MAX_NUMBER], prime[MAX_NUMBER];
int number, prime_number;

void getPrime() {
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

void dfs(int i, int j, int cnt_number) {
	if (cnt_number > number) {
		return ;
	}
	vis[cnt_number] = 1;
	dfs(i, j, cnt_number * prime[i]);
	dfs(i, j, cnt_number * prime[j]);
}

int main() {
	scanf("%d", &number);
	getPrime();
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= prime_number; i++) {
		for (int j = i + 1; prime[j] * prime[i] <= number && j <= prime_number; j++) {
			dfs(i, j, prime[i] * prime[j]);
		}
	}
	int ans = 0;
	for (int i = 2; i <= number; i++) {
		if (vis[i]) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}