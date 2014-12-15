#include <cstdio>
#include <string.h>
#include <iostream>

const int MAX_NUMBER = 100;

long long dp[MAX_NUMBER][MAX_NUMBER];
char input_string[MAX_NUMBER];

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(dp, 0, sizeof(dp));
		scanf("%s", input_string);
		int total_length = strlen(input_string);
		for (int i = 1; i <= total_length; i++) {
			dp[i][i] = 1;
		}
		for (int length = 2; length <= total_length; length++) {
			for (int i = 1; i <= total_length - length + 1; i++) {
				int next = i + length - 1;
				if (input_string[i - 1] == input_string[next - 1]) {
					dp[i][next]++;
					dp[i][next] += dp[i + 1][next];
					dp[i][next] += dp[i][next - 1];
				}
				else {
					dp[i][next] = dp[i][next - 1] + dp[i + 1][next] - dp[i + 1][next - 1];
				}
			}
		}
		std::cout << dp[1][total_length] << std::endl;
	}
	return 0;
}