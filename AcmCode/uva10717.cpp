#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 55;

long long value[MAX_NUMBER];
long long table[20];
long long ans[20][2];
int n, t;

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	while (b) {
		long long c = b;
		b = a % b;
		a = c;
	}
	return a;
}

long long getGcd(int i, int j, int k, int m) {
	long long gcd_1 = gcd(value[i], value[j]);
	gcd_1 = gcd(gcd_1, value[k]);
	gcd_1 = gcd(gcd_1, value[m]);
	return gcd_1;
}

int main() {
	while (scanf("%d%d", &n, &t) != EOF) {
		if (!n && !t) {
			break;
		}
		memset(ans, -1, sizeof(ans));
		for (int i = 1; i <= n; i++) {
			cin >> value[i];
		}
		for (int i = 1; i <= t; i++) {
			cin >> table[i];
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = j + 1; k <= n; k++) {
					for (int m = k + 1; m <= n; m++) {
						long long temp = value[i] * value[j];
						long long gcd_1 = gcd(value[i], value[j]);
						temp /= gcd_1;
						gcd_1 = gcd(temp, value[k]);
						temp *= value[k];
						temp /= gcd_1;
						gcd_1 = gcd(temp, value[m]);
						temp *= value[m];
						temp /= gcd_1;
						for (int s = 1; s <= t; s++) {
							if (table[s] % temp == 0) {
								ans[s][0] = table[s];
								ans[s][1] = table[s];
							}
							else {
								long long ans_1 = table[s] / temp * temp;
								long long ans_2 = (table[s] / temp + 1) *temp;
								if (ans[s][0] == -1 || ans_1 > ans[s][0]) {
									ans[s][0] = ans_1;
								}
								if (ans[s][1] == -1 || ans_2 < ans[s][1]) {
									ans[s][1] = ans_2;
								}
							}
						}
					}
				}
			}
		}
		for (int i = 1; i <= t; i++) {
			cout << ans[i][0] << " " << ans[i][1] << endl;
		}
	}
	return 0;
}