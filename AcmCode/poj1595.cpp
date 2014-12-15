#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 10005;

bool vis[MAX_NUMBER + 3];
int prime[MAX_NUMBER];
int prime_number, range, length;
int getFirst(int cnt_number) {
	int low = 1;
	int high = prime_number;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (prime[mid] <= cnt_number) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return high;
}
void getAllPrime() {
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				vis[j] = 1;
			}
		}
	}
	prime_number = 0;
	for (int i = 1; i <= MAX_NUMBER; i++) {
		if (!vis[i]) {
			prime[++prime_number] = i;
		}
	}
}

int main() {
	getAllPrime();
	int first = 1;
	while (scanf("%d%d", &range, &length) != EOF) {
		int number = getFirst(range);
		if (!first) {
			printf("\n");
		}
		printf("%d %d:", range, length);
		if (length > number) {
			length = (number + 1) / 2;
		}
		if (number % 2 == 0) {
			int mid = number / 2;
			for (int i = mid - length + 1; i <= mid + length; i++) {
				printf(" %d", prime[i]);
			}
		}
		else {
			int mid = (number + 1) / 2;
			for (int i = mid - length + 1; i <= mid + length - 1; i++) {
				printf(" %d", prime[i]);
			}
		}
		printf("\n");
		first = 0;
	}
	return 0;
}