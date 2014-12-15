#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 1000006;

bool vis[MAX_NUMBER];
int has[MAX_NUMBER];
int number;

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	while (scanf("%d", &number) != EOF) {
		memset(has, 0, sizeof(has));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= sqrt(number / 2 + 0.5); i++) {
			for (int j = i + 1; i * i + j * j <= number; j += 2) {
				if (i != 1 && gcd(i, j) != 1) {
					continue;
				}
				int a = j * j - i * i;
				int b = 2 * i * j;
				int c = i * i + j * j;
				has[c]++;
				if (c == 45) {
					printf("%d %d", i, j);
				}
				int k = 1;
				while (c * k <= number) {
					int temp_1 = a * k;
					int temp_2 = b * k;
					int temp_3 = c * k;
					vis[temp_1] = vis[temp_2] = vis[temp_3] = 1;
					k++;
				}
			}
		}
		int ans = 0;
		int p_ans = 0;
		for (int i = 1; i <= number; i++) {
			if (!vis[i]) {
				p_ans++;
			}
			ans += has[i];
		}
		printf("%d %d\n", ans, p_ans);
	}
	return 0;
}