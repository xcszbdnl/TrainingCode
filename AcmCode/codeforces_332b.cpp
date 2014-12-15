#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 200006;

long long dp[MAX_NUMBER];
int input[MAX_NUMBER];
int length, k;

int main() {
	scanf("%d%d", &length, &k);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= length; i++) {
		scanf("%d", &input[i]);
	}
	for (int i = 1; i <= k; i++) {
		dp[1] += input[i];
	}
	for (int i = 2; i <= length - k + 1; i++) {
		dp[i] = dp[i - 1] - input[i - 1] + input[i + k - 1];
	}
	long long left_max = dp[1];
	int left_ans = 1, temp = 1;
	int right_ans;
	long long max_sum = 0;
	for (int i = k + 1; i <= length - k + 1; i++) {
		if (dp[i] + left_max > max_sum) {
			right_ans = i;
			left_ans = temp;
			max_sum = dp[i] + left_max;
		}
		if (left_max < dp[i - k + 1]) {
			temp = i - k + 1;
			left_max = dp[i - k + 1];
		}
	}
	printf("%d %d\n", left_ans, right_ans);
	return 0;
}