#include <cstdio>
#include <cmath>
#include <string.h>

const int MAX_NUMBER = 10005;
const int INF = 1000000;

bool vis[MAX_NUMBER];
int prime[MAX_NUMBER];
int distance[1100][1100], maps[1100][1100], queue[MAX_NUMBER], depth[1100];
int prime_number;
int prime_1, prime_2;

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
	prime_number = 0;
	for (int i = 1000; i < MAX_NUMBER; i++) {
		if (i < 10000 && !vis[i]) {
			prime[++prime_number] = i;
		}
	}
}

void buildMap() {
	for (int i = 1; i <= prime_number; i++) {
		maps[i][i] = 0;
		distance[i][i] = 0;
		for (int j = i + 1; j <= prime_number; j++) {
			distance[i][j] = distance[j][i] = INF;
			maps[i][j] = maps[j][i] = INF;
		}
	}
	for (int i = 1; i <= prime_number; i++) {
		for (int j = i + 1; j <= prime_number; j++) {
			char string_1[5];
			char string_2[5];
			int temp_1 = prime[i];
			int temp_2 = prime[j];
			int k = 0;
			while (temp_1) {
				string_1[k] = temp_1 % 10;
				temp_1 /= 10;
				k++;
			}
			k = 0;
			while (temp_2) {
				string_2[k] = temp_2 % 10;
				temp_2 /= 10;
				k++;
			}
			int same = 0;
			for (k = 0; k < 4; k++) {
				if (string_1[k] == string_2[k]) {
					same++;
				}
			}
			if (same == 3) {
				distance[i][j] = distance[j][i] = 1;
			}
		}
	}
}

int getPoint(int cnt_point) {
	int low = 1;
	int high = prime_number;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (prime[mid] == cnt_point) {
			return mid;
		}
		else if (prime[mid] > cnt_point) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
}
void bfs(int cnt_point, int final_point) {
	int front = 0;
	int rear = 1;
	queue[front] = cnt_point;
	memset(vis, 0, sizeof(vis));
	memset(depth, 0, sizeof(depth));
	vis[front] = 1;
	while (front < rear) {
		int queue_point = queue[front];
		if (queue_point == final_point) {
			maps[cnt_point][final_point] = maps[final_point][cnt_point] = depth[queue_point];
			return ;
		}
		for (int i = 1; i <= prime_number; i++) {
			if (distance[queue_point][i] != INF && !vis[i]) {
				vis[i] = 1;
				queue[rear++] = i;
				rear = rear % MAX_NUMBER;
				depth[i] = depth[queue_point] + 1;
			}
		}
		front++;
		front = front % MAX_NUMBER;
	}
}
int main() {
	getAllPrime();
	buildMap();
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d%d", &prime_1, &prime_2);
		int start = getPoint(prime_1);
		int end = getPoint(prime_2);
		if (maps[start][end] >= INF) {
			bfs(start, end);
			if (maps[start][end] == INF) {
				printf("Impossible\n");
			}
			else {
				printf("%d\n", maps[start][end]);
			}
		}
		else {
			printf("%d\n", maps[start][end]);
		}
	}
	return 0;
}