#include <iostream>
#include <cstdio>
#include <string.h>

#define MAX_NUMBER 1005

int dp[MAX_NUMBER][MAX_NUMBER];
char string_1[MAX_NUMBER];

int minThree(int one, int two, int three) {
  int temp;
	if (one < two) {
		temp = one;
	}
	else {
		temp = two;
	}
	if (temp < three) {
		return temp;
	}
	else {
		return three;
	}
}


int main() {
	int test_case;
	int case_number = 1;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%s", string_1);
		memset(dp, 0, sizeof(dp));
		int string_length = strlen(string_1);
		for (int length = 2; length <= string_length; length++) {
			for (int i = 1; i + length - 1 <= string_length; i++) {
				int next = i + length - 1;
				if (string_1[i - 1] == string_1[next - 1]) {
					dp[i][next] = dp[i + 1][next - 1];
				}
				else {
					dp[i][next] = minThree(dp[i + 1][next - 1], dp[i + 1][next], dp[i][next - 1]) + 1;
				}
			}
		}
		printf("Case %d: %d\n", case_number, dp[1][string_length]);
		case_number++;
	}
	return 0;
}
