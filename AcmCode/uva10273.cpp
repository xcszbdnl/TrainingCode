#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

int value[MAX_NUMBER][20];
int cycle[MAX_NUMBER], vis[MAX_NUMBER * 10];
int cow;

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d", &cow);
		int cnt_number = 1;
		for (int i = 1; i <= cow; i++) {
			scanf("%d", &cycle[i]);
			int temp = gcd(cnt_number, cycle[i]);
			cnt_number *= cycle[i];
			cnt_number /= temp;
			for (int j = 0; j < cycle[i]; j++) {
				scanf("%d", &value[i][j]);
			}
		}
		int change = 1;
		int cnt_day = 0;
		memset(vis, 0, sizeof(vis));
		int ans = 0;
		int last_day = 0;
		while (change) {
			int min_number = 10000000;
			change = 0;
			for (int i = 1; i <= cow; i++) {
				if (!vis[i]) {
					int cnt_value = value[i][cnt_day % cycle[i]];
					if (cnt_value < min_number) {
						min_number = cnt_value;
					}
				}
			}
		}
	}
}