#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 2000000;

bool vis[MAX_NUMBER];
int number;

void getAllPrime() {
	memset(vis, 0, sizeof(vis));
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j < MAX_NUMBER; j += i) {
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
			printf("0\n");
		}
		else {
			int min_ans;
			for (int i = number - 1; i >= 3; i--) {
				if (!vis[i]) {
					min_ans = i;
					break;
				}
			}
			int max_ans;
			for (int i = number + 1; i < MAX_NUMBER; i++) {
				if (!vis[i]) {
					max_ans = i;
					break;
				}
			}
			printf("%d\n", max_ans - min_ans);
		}
	}
	return 0;
}