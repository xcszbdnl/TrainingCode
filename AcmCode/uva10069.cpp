#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

const int MAX_NUMBER_1 = 10001;
const int MAX_NUMBER_2 = 101;

char string_1[MAX_NUMBER_1];
char string_2[MAX_NUMBER_2];

long long dp[MAX_NUMBER_2][MAX_NUMBER_1];
int index_array[MAX_NUMBER_2][MAX_NUMBER_1];
int index_number[MAX_NUMBER_2];
long long ans;

int main() {

	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(dp, 0, sizeof(dp));
		memset(index_array, 0, sizeof(index_array));
		memset(index_number, 0, sizeof(index_number));
		scanf("%s%s", string_1, string_2);
		int length_1, length_2;
		length_1 = strlen(string_1);
		length_2 = strlen(string_2);
		for (int i = 0; i < length_2; i++) {
			for (int j = 0; j < length_1; j++) {
				if (string_2[i] == string_1[j]) {
					index_array[i][index_number[i]] = j;
					index_number[i]++;
				}
			}
		}
		for (int i = 0; i < index_number[0]; i++) {
			dp[0][index_array[0][i]] = 1;
		}
		for (int i = 1; i < length_2; i++) {
			for (int j = 0; j < index_number[i]; j++) {
				for (int k = 0; k < index_number[i - 1]; k++) {
					if (index_array[i - 1][k] < index_array[i][j]) {
						dp[i][index_array[i][j]] += dp[i - 1][index_array[i - 1][k]];
					}
				}
			}
		}
		ans = 0;
		for (int i = 0; i < index_number[length_2 - 1]; i++) {
			ans += dp[length_2 - 1][index_array[length_2 - 1][i]];
		}
		cout << ans << endl;
	}
	return 0;
}
