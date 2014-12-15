#include <cstdio>
#include <string.h>
#include <iostream>

const int MAX_COIN = 22;
const int MAX_NUMBER = 10005;

long long dp[MAX_COIN][MAX_NUMBER];
int coin[MAX_COIN];
int amount;

int main() {
	for (int i = 1; i < MAX_COIN; i++) {
		coin[i] = i * i * i;
	}
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 1; i < MAX_COIN; i++) {
		for (int j = 0; j < MAX_NUMBER; j++) {
			for (int k = 0; k * coin[i] <= j; k++) {
				dp[i][j] += dp[i - 1][j - k * coin[i]];
			}
		}
	}
	while (scanf("%d", &amount) != EOF) {
		long long ans;
		for (int i = 21; i >= 1; i--) {
			if (dp[i][amount] != 0) {
				ans = dp[i][amount];
				break;
			}
		}
		std::cout << ans << std::endl;
	}
	return 0;
}