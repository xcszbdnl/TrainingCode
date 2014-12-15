#include <string.h>
#include <cstdio>

const int MAX_EDGE = 150000;
const int MAX_POINT = 30000;
const int INF = 1000000000;

struct Edge {
	int end;
	int value;
	int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_POINT], queue[MAX_EDGE], vis[MAX_POINT];
int distance[MAX_POINT];
int source, destination, point_number, edge_number;

void addEdge(int start, int end, int value) {
	edge[edge_number].end = end;
	edge[edge_number].value = value;
	edge[edge_number].next = head[start];
	head[start] = edge_number;
	edge_number++;

	edge[edge_number].end = start;
	edge[edge_number].value = value;
	edge[edge_number].next = head[end];
	head[end] = edge_number;
	edge_number++;
}

void spfa() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < point_number; i++) {
		distance[i] = INF;
	}
	distance[source] = 0;
	vis[source] = 1;
	int front = 0;
	int rear = 1;
	queue[front] = source;
	while (front < rear) {
		int cnt_point = queue[front];
		vis[cnt_point] = 1;
		for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
			int next_point = edge[next_edge].end;
			if (distance[next_point] > distance[cnt_point] + edge[next_edge].value) {
				distance[next_point] = distance[cnt_point] + edge[next_edge].value;
				if (!vis[next_point]) {
					vis[next_point] = 1;
					queue[rear] = next_point;
					rear++;
				}
			}
		}
		vis[cnt_point] = 0;
		front++;
	}
}

int main() {
	int test_case;
	int case_number = 1;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(head, -1, sizeof(head));
		memset(edge, 0, sizeof(edge));
		edge_number = 0;
		int cnt_edge;
		scanf("%d%d%d%d", &point_number, &cnt_edge, &source, &destination);
		for (int i = 1; i <= cnt_edge; i++) {
			int start, end, value;
			scanf("%d%d%d", &start, &end, &value);
			addEdge(start, end, value);
		}
		spfa();
		printf("Case #%d: ", case_number);
		case_number++;
		if (distance[destination] == INF) {
			printf("unreachable\n");
		}
		else {
			printf("%d\n", distance[destination]);
		}
	}
	return 0;
}
