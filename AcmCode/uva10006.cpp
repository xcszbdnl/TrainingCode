#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 65007;
int number;
bool vis[MAX_NUMBER + 3];

long long getMod(int a, int power, int mod_number) {
	if (power == 0) {
		return 1;
	}
	long long x = getMod(a, power / 2, mod_number);
	x = (x * x) % mod_number;
	if (power % 2 == 1) {
		x = (x * a) % mod_number;
	}
	return x;
}

void getAllPrime() {
	memset(vis, 0, sizeof(vis));
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				vis[j] = 1;
			}
		}
	}
}

int main() {
	getAllPrime();
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		if (!vis[number]) {
			printf("%d is normal.\n", number);
		}
		else {
			int flag = 0;
			for (int i = 2; i <= number - 1; i++) {
				if (getMod(i, number, number) != i) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				printf("%d is normal.\n", number);
			}
			else {
				printf("The number %d is a Carmichael number.\n", number);
			}
		}
	}
	return 0;
}