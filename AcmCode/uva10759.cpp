#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 200;

long long dp[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER][MAX_NUMBER];
int n, x;

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

void search(int cnt_n, int cnt_x) {
	if (cnt_n == 1) {
		return ;
	}
	if (vis[cnt_n][cnt_x]) {
		return ;
	}
	vis[cnt_n][cnt_x] = 1;
	for (int i = 1; i <= 6 && i <= cnt_x; i++) {
		search(cnt_n - 1, cnt_x - i);
		dp[cnt_n][cnt_x] += dp[cnt_n - 1][cnt_x - i];
	}
}
int main() {
	memset(dp, 0, sizeof(dp));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= 6; i++) {
		dp[1][i] = 1;
		vis[1][i] = 1;
	}
	while (scanf("%d%d", &n, &x) != EOF) {
		if (!n && !x) {
			break;
		}
		for (int i = x; i <= 6 * n; i++) {
			search(n, i);
		}
		long long ans = 1;
		for (int i = 1; i <= n; i++) {
			ans *= 6;
		}
		long long sums = 0;
		for (int i = x; i <= 6 * n; i++) {
			sums += dp[n][i];
		}
		long long factor = gcd(ans, sums);
		if (sums == 0) {
			printf("0\n");
			continue;
		}
		else if (sums / factor == 1 && ans / factor == 1) {
			printf("1\n");
			continue;
		}
		printf("%lld/%lld\n", sums / factor, ans / factor);
	}
	return 0;
}