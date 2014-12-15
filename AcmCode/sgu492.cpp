#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 25;
const long long INF = 4000000000000000000ll;
long long dp[MAX_NUMBER][3];
long long number;
int bit[MAX_NUMBER];

void getDp() {
	dp[1][0] = 10;
	dp[1][1] = 0;
	dp[1][2] = 1;
	for (int i = 2; i < MAX_NUMBER; i++) {
		dp[i][0] = dp[i - 1][0] * 10 - dp[i - 1][2];
		dp[i][1] = dp[i - 1][1] * 10 + dp[i - 1][2];
		dp[i][2] = dp[i - 1][0];
	}
}

long long getIndex(long long cnt_number) {
	int length = 0;
	long long ans = cnt_number;
	cnt_number++;
	while (cnt_number) {
		bit[++length] = cnt_number % 10;
		cnt_number /= 10;
	}
	bit[length + 1] = 0;
	int flag = 0;
	long long temp = 0;
	for (int i = length; i; i--) {
		temp += dp[i - 1][1] * bit[i];
		if (flag) {
			temp += dp[i - 1][0] * bit[i];
		}
		if (!flag && bit[i] > 1) {
			temp += dp[i - 1][2];
		}
		if (!flag && bit[i + 1] == 1 && bit[i] > 3) {
			temp += dp[i][2];
		}
		if (bit[i] == 3 && bit[i + 1] == 1) {
			flag = 1;
		}
	}
	return ans - temp;
}

int main() {
	getDp();
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%I64d", &number);
		long long low = 1;
		long long high = INF;
		while (low <= high) {
			long long mid = (low + high) / 2;
			long long temp = getIndex(mid);
			if (temp >= number) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		printf("%I64d\n", low);
	}
	return 0;
}