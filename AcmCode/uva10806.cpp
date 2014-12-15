#include <string.h>
#include <cstdio>


const int MAX_EDGE = 10001;
const int MAX_POINT = 101;
const int INF = 100000000;

struct Edge {
	int start;
	int end;
	int cap;
	int cost;
	int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_POINT], pre_edge[MAX_POINT], queue[MAX_POINT], distance[MAX_POINT], vis[MAX_POINT];
int edge_number, point_number;
int source, destination;

void addEdge(int start, int end, int cap_1, int cap_2, int cost_1, int cost_2) {
	edge[edge_number].start = start;
	edge[edge_number].end = end;
	edge[edge_number].cap = cap_1;
	edge[edge_number].cost = cost_1;
	edge[edge_number].next = head[start];
	head[start] = edge_number;
	edge_number++;

	edge[edge_number].start = end;
	edge[edge_number].end = start;
	edge[edge_number].cap = cap_2;
	edge[edge_number].cost = cost_2;
	edge[edge_number].next = head[end];
	head[end] = edge_number;
	edge_number++;
}
int spfa(int &flow, int &cost) {
	for (int i = 1; i <= point_number + 1; i++) {
		distance[i] = INF;
	}
	distance[source] = 0;
	memset(vis, 0, sizeof(vis));
	vis[source] = 1;
	int front = 0;
	int rear = 1;
	queue[front] = source;
	while (front < rear) {
		int cnt_point = queue[front];
		for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
			int next_point = edge[i].end;
			if (edge[i].cap > 0 && distance[next_point] > distance[cnt_point] + edge[i].cost) {
				distance[next_point] = distance[cnt_point] + edge[i].cost;
				pre_edge[next_point] = i;
				if (!vis[next_point]) {
					vis[next_point] = 1;
					queue[rear] = next_point;
					rear++;
					rear %= MAX_POINT;
				}
			}
		}
		vis[cnt_point] = 0;
		front++;
		front %= MAX_POINT;
	}
	if (distance[destination] == INF) {
		return 0;
	}
	int min_flow = INF;
	for (int i = destination; i != source; i = edge[pre_edge[i]].start) {
		if (min_flow > edge[pre_edge[i]].cap) {
			min_flow = edge[pre_edge[i]].cap;
		}
	}
	cost += min_flow * distance[destination];
	for (int i = destination; i != source; i = edge[pre_edge[i]].start) {
		edge[pre_edge[i]].cap -= min_flow;
		edge[pre_edge[i] ^ 1].cap += min_flow;
	}
	flow += min_flow;
	return 1;
}

int main() {
	while (scanf("%d", &point_number) != EOF) {
		if (!point_number) {
			break;
		}
		edge_number = 0;
		memset(head, -1, sizeof(head));
		source = 0;
		destination = point_number + 1;
		int cnt_edge;
		scanf("%d", &cnt_edge);
		for (int i = 1; i <= cnt_edge; i++) {
			int start, end, cost;
			scanf("%d%d%d", &start, &end, &cost);
			addEdge(start, end, 1, 0, cost, -cost);
			addEdge(end, start, 1, 0, cost, -cost);
		}
		addEdge(source, 1, 2, 0, 0, 0);
		addEdge(point_number, destination, 2, 0, 0, 0);
		int max_flow = 0, min_cost = 0;
		while (spfa(max_flow, min_cost)) {
			;
		}
		if (max_flow < 2) {
			printf("Back to jail\n");
		}
		else {
			printf("%d\n", min_cost);
		}
	}
	return 0;
}
