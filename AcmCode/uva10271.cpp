#include <cstdio>
#include <string.h>

#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 5005;
const int MAX_CHOP = 1005;

int dp[MAX_NUMBER][MAX_CHOP];
int chopstick[MAX_NUMBER];
int guest_number, total_number;

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(dp, 0, sizeof(dp));
		scanf("%d%d", &guest_number, &total_number);
		for (int i = 1; i <= total_number; i++) {
			scanf("%d", &chopstick[i]);
		}
		int temp = chopstick[total_number - 2] - chopstick[total_number - 3];
		dp[total_number - 3][1] = temp * temp;
		for (int i = total_number - 4; i >= 1; i--) {
			for (int j = 1; j <= guest_number + 8; j++) {
				int temp = chopstick[i + 1] - chopstick[i];
				temp = temp * temp;
				dp[i][j] = dp[i + 2][j - 1] + temp;
				dp[i][j] = min(dp[i + 1][j], dp[i][j]);
			}
		}
		printf("%d\n", dp[1][guest_number + 8]);
	}
	return 0;
}