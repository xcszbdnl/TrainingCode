#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

#define min(a,b) ((a) > (b)) ? (b) : (a)
bool vis[MAX_NUMBER][MAX_NUMBER];
char step[10][20] = {"fill A", "fill B", "empty A", "empty B", "pour B A", "pour A B"};
struct Point {
	int a, b;
	int father;
	char operation[20];
};

struct Point queue[MAX_NUMBER * MAX_NUMBER];
int cap_a, cap_b, target;

void printPath(int cnt_point) {
	if (queue[cnt_point].father != -1) {
		printPath(queue[cnt_point].father);
		printf("%s\n", queue[cnt_point].operation);
	}
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	int front = 0;
	int rear = 1;
	queue[0].a = 0;
	queue[0].b = 0;
	queue[0].father = -1;
	while (front < rear) {
		struct Point cnt_point = queue[front];
		int cnt_a, cnt_b, next_a, next_b;
		cnt_a = cnt_point.a;
		cnt_b = cnt_point.b;
		if (cnt_b == target) {
			return front;
		}
		next_a = cap_a;
		next_b = cnt_b;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[0], sizeof(step[0]));
			rear++;
		}
		next_a = cnt_a;
		next_b = cap_b;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[1], sizeof(step[1]));
			rear++;
		}
		next_a = 0;
		next_b = cnt_b;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[2], sizeof(step[2]));
			rear++;
		}
		next_a = cnt_a;
		next_b = 0;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[3], sizeof(step[3]));
			rear++;
		}
		int to_pour = min(cap_a - cnt_a, cnt_b);
		next_a = cnt_a + to_pour;
		next_b = cnt_b - to_pour;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[4], sizeof(step[4]));
			rear++;
		}
		to_pour = min(cnt_a, cap_b - cnt_b);
		next_a = cnt_a - to_pour;
		next_b = cnt_b + to_pour;
		if (!vis[next_a][next_b]) {
			vis[next_a][next_b] = 1;
			queue[rear].a = next_a;
			queue[rear].b = next_b;
			queue[rear].father = front;
			memcpy(queue[rear].operation, step[5], sizeof(step[5]));
			rear++;
		}
		front++;
	}
}

int main() {
	while (scanf("%d%d%d", &cap_a, &cap_b, &target) != EOF) {
		int ans = bfs();
		printPath(ans);
		printf("success\n");
	}
	return 0;
}