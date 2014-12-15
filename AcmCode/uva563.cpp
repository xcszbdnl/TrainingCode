#include <cstdio>
#include <string.h>
#include <map>
#include <string>

const int MAX_NUMBER = 100;
const int MAX_EDGE = 1000;
const int INF = 100000;

using namespace std;

struct Edge {
	int start;
	int end;
	int cap;
	int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_NUMBER], dist[MAX_NUMBER], queue[MAX_NUMBER], cur[MAX_NUMBER], stack[MAX_NUMBER];
map<string, int> maps;
int edge_number, point_number;
int source, destination;

void addEdge(int start, int end, int cap_1, int cap_2) {
	edge[edge_number].start = start;
	edge[edge_number].end = end;
	edge[edge_number].cap = cap_1;
	edge[edge_number].next = head[start];
	head[start] = edge_number;
	edge_number++;

	edge[edge_number].start = end;
	edge[edge_number].end = start;
	edge[edge_number].cap = cap_2;
	edge[edge_number].next = head[end];
	head[end] = edge_number;
	edge_number++;
}

int bfs() {
	memset(dist, -1, sizeof(dist));
	int front = 0;
	int rear = 1;
	dist[source] = 0;
	queue[front] = source;
	while (front < rear) {
		int cnt_point = queue[front];
		for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
			int next_point = edge[i].end;
			if (edge[i].cap > 0 && dist[next_point] == -1) {
				dist[next_point] = dist[cnt_point] + 1;
				queue[rear] = next_point;
				rear++;
				if (next_point == destination) {
					return 1;
				}
			}
		}
		front++;
	}
	return 0;
}

int dinic() {
	int ans = 0;
	while (bfs()) {
		memcpy(cur, head, sizeof(cur));
		int cnt_point = source;
		int top = 0;
		while (1) {
			if (cnt_point == destination) {
				int min_flow = INF;
				int min_number;
				for (int i = 0; i < top; i++) {
					if (min_flow > edge[stack[i]].cap) {
						min_flow = edge[stack[i]].cap;
						min_number = i;
					}
				}
				for (int i = 0; i < top; i++) {
					edge[stack[i]].cap -= min_flow;
					edge[stack[i] ^ 1].cap += min_flow;
				}
				ans += min_flow;
				top = min_number;
				cnt_point = edge[stack[top]].start;
			}
			for (int i = cur[cnt_point]; i != -1; i = cur[cnt_point] = edge[i].next) {
				if (edge[i].cap > 0 && dist[edge[i].end] == dist[cnt_point] + 1) {
					break;
				}
			}
			if (cur[cnt_point] != -1) {
				stack[top++] = cur[cnt_point];
				cnt_point = edge[cur[cnt_point]].end;
			}
			else {
				if (top == 0) {
					break;
				}
				dist[cnt_point] = -1;
				top--;
				cnt_point = edge[stack[top]].start;
			}
		}
	}
	return ans;
}

int row, column, step[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}};

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		edge_number = 0;
		memset(head, -1, sizeof(head));
		int rob_number;
		source = 0;
		scanf("%d%d%d", &column, &row, &rob_number);
		destination = row * column + 1;
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= column; j++) {
				int cnt_number = (i - 1) * column + j;
				for (int k = 0; k < 4; k++) {
					int next_x = i + step[k][0];
					int next_y = j + step[k][1];
					int next_number = (next_x - 1) * column + next_y;
					if (next_x >= 1 && next_x <= row && next_y >= 1 && next_y <= column) {
						addEdge(cnt_number, next_number, 1, 0);
					}
				}
			}
		}
		for (int i = 1; i <= rob_number; i++) {
			int y, x;
			scanf("%d%d", &y, &x);
			int cnt_number = (x - 1) * column + y;
			addEdge(source, cnt_number, 1, 0);
		}
		for (int i = 1; i <= row; i++) {
			int cnt_number = (i - 1) * column + 1;
			addEdge(cnt_number, destination, 1, 0);
			cnt_number = (i - 1) * column + column;
			addEdge(cnt_number, destination, 1, 0);
		}
		for (int i = 1; i <= column; i++) {
			int cnt_number = i;
			addEdge(cnt_number, destination, 1, 0);
			cnt_number = (row - 1) * column + i;
			addEdge(cnt_number, destination, 1, 0);
		}
		int ans = dinic();
		if (ans == rob_number) {
			printf("possible\n");
		}
		else {
			printf("not possible\n");
		}
	}
	return 0;
}