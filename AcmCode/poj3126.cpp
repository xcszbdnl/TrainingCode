#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 10000;

bool vis[MAX_NUMBER + 5], is_prime[MAX_NUMBER + 5];
int queue[MAX_NUMBER * 10], depth[MAX_NUMBER];
int start, end, result;
int power[] = {1000, 100, 10, 1};

void getAllPrime() {
	memset(is_prime, 0, sizeof(is_prime));
	int m = (int)sqrt(MAX_NUMBER + 0.5);
	for (int i = 2; i <= m; i++) {
		if (!is_prime[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				is_prime[j] = 1;
			}
		}
	}
}

void bfs() {
	int front = 0;
	int rear = 1;
	memset(vis, 0, sizeof(vis));
	memset(depth, 0, sizeof(depth));
	queue[front] = start;
	vis[start] = 1;
	while (front < rear) {
		int cnt_number = queue[front];
		if (cnt_number == end) {
			result = depth[cnt_number];
			return ;
		}
		int a[4];
		for (int i = 0; i < 4; i++) {
			a[i] = cnt_number / power[i];
			cnt_number = cnt_number - a[i] * power[i];
		}
		cnt_number = queue[front];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				if (i != 0 || j != 0 && (j != a[i])) {
					int next_number = j * power[i] + cnt_number - a[i] * power[i];
					if (!vis[next_number] && !is_prime[next_number]) {
						queue[rear++] = next_number;
						depth[next_number] = depth[cnt_number] + 1;
						vis[next_number] = 1;
					}
				}
			}
		}
		front++;
	}
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	getAllPrime();
	while (test_case--) {
		scanf("%d%d", &start, &end);
		bfs();
		printf("%d\n", result);
	}
	return 0;
}