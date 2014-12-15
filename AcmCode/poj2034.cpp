#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 1005;
const int MAX_PRIME = 10005;
int vis[MAX_NUMBER], ans[MAX_NUMBER];
bool isPrime[MAX_PRIME];
int left, right, length, flag;

void getAllPrime() {
	int m = (int)sqrt(MAX_PRIME + 0.5);
	memset(isPrime, 0, sizeof(isPrime));
	for (int i = 2; i <= m; i++) {
		if (!isPrime[i]) {
			for (int j = i * i; j <= MAX_PRIME; j += i) {
				isPrime[j] = 1;
			}
		}
	}
}

void dfs(int cnt_location) {
	if (flag) {
		return ;
	}
	if (cnt_location == right - left + 1) {
		flag = 1;
		return ;
	}
	else {
		for (int i = left; i <= right && !flag; i++) {
			if (!vis[i]) {
				ans[cnt_location] = i;
				int can_search = 1;
				if (cnt_location + 1 - length >= 0) {
					int sums = ans[cnt_location + 1 - length];
					for (int k = cnt_location + 2 - length; k <= cnt_location; k++) {
						sums += ans[k];
						if (!isPrime[sums]) {
							can_search = 0;
							break;
						}
					}
				}
				else {
					int sums = ans[0];
					for (int k = 1; k <= cnt_location; k++) {
						sums += ans[k];
						if (!isPrime[sums]) {
							can_search = 0;
							break;
						}
					}
				}
				if (can_search) {
					vis[i] = 1;
					dfs(cnt_location + 1);
					vis[i] = 0;
				}
			}
		}
	}
}
int main() {
	getAllPrime();
	while (scanf("%d%d%d", &left, &right, &length) != EOF) {
		if (!left && !right && !length) {
			break;
		}
		memset(vis, 0, sizeof(vis));
		memset(ans, 0, sizeof(ans));
		flag = 0;
		dfs(0);
		if (!flag) {
			printf("No anti-prime sequence exists.\n");
		}
		else {
			for (int i = 0; i < right - left + 1; i++) {
				if (!i) {
					printf("%d", ans[i]);
				}
				else {
					printf(",%d", ans[i]);
				}
			}
			printf("\n");
		}
	}
	return 0;
}