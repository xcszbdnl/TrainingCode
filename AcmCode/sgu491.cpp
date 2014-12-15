#include <cstdio>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 100005;

vector<int> factor[MAX_NUMBER];
int temp_ans[MAX_NUMBER * 50];
int temp_factor[MAX_NUMBER];
int number;

void getAllFactor(int n) {
	int factor_number = 0;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			if (i * i == n) {
				temp_factor[factor_number++] = i;
			}
			else {
				temp_factor[factor_number++] = i;
				temp_factor[factor_number++] = n / i;
			}
		}
	}
	sort(temp_factor, temp_factor + factor_number);
	for (int i = 0; i < factor_number; i++) {
		factor[n].push_back(temp_factor[i]);
	}
}

int main() {
	for (int i = 2; i < MAX_NUMBER; i++) {
		getAllFactor(i);
	}
	while (scanf("%d", &number) != EOF) {
		long long ans = 0;
		for (int a = 1; a <= number / 2; a++) {
			int temp_number = 0;
			for (int x = 1; number - a * x > 0; x++) {
				int by = number - a * x;
				for (int i = 0; i < factor[by].size(); i++) {
					int b = factor[by][i];
					if (b > a) {
						temp_ans[temp_number++] = b;
					}
				}
			}
			sort(temp_ans, temp_ans + temp_number);
			if (temp_number > 0) {
				ans++;
			}
			for (int i = 1; i < temp_number; i++) {
				if (temp_ans[i] != temp_ans[i - 1]) {
					ans++;
				}
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
