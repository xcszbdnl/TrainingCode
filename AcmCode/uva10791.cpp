#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 100000;

bool vis[MAX_NUMBER + 2];
int prim[MAX_NUMBER];
int value[MAX_NUMBER];
int prim_number;
long long number;

void getAllPrim() {
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				vis[j] = 1;
			}
		}
	}
	prim_number = 0;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		if (!vis[i]) {
			prim[++prim_number] = i;
		}
	}
}

int main() {
	getAllPrim();
	int case_number = 1;
	while (scanf("%lld", &number) != EOF) {
		if (!number) {
			break;
		}
		memset(value, 0, sizeof(value));
		long long temp = number;
		for (int i = 1; i <= prim_number && prim[i] <= number / 2; i++) {
			value[i] = 1;
			while (temp % prim[i] == 0) {
				value[i] = value[i] * prim[i];
				temp /= prim[i];
			}
		}
		long long ans = 0;
		int factor = 0;
		if (number == 1) {
			ans = 2;
		}
		else {
			for (int i = 1; i <= prim_number && prim[i] <= number / 2; i++) {
				if (value[i] != 1) {
					factor++;
					ans += value[i];
				}
			}
			if (temp > 1) {
				ans += temp;
				factor++;
			}
			if (factor == 1) {
				ans = number + 1;
			}
		}
		printf("Case %d: %lld\n", case_number, ans);
		case_number++;
	}
	return 0;
}