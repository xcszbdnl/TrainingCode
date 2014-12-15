#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1000;
const double INF = 100000000.0;
const double eps = 1e-6;

struct Edge {
	int start;
	int end;
	double cost;
	int cap;
	int next;
};

struct Edge edge[MAX_NUMBER];
int head[MAX_NUMBER], queue[MAX_NUMBER], pre_edge[MAX_NUMBER], vis[MAX_NUMBER];
double dist[MAX_NUMBER];
int point_number, edge_number, n, m;
int source, destination;

void addEdge(int start, int end, int cap_1, int cap_2, double cost_1, double cost_2) {
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

int spfa(double &cost) {
	for (int i = 0; i <= point_number; i++) {
		dist[i] = INF;
	}
	dist[source] = 0;
	memset(vis, 0, sizeof(vis));
	int front = 0;
	int rear = 1;
	queue[front] = source;
	while (front < rear) {
		int cnt_point = queue[front];
		vis[cnt_point] = 1;
		for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
			int end = edge[i].end;
			if (edge[i].cap > 0 && dist[end] > dist[cnt_point] + edge[i].cost) {
				dist[end] = dist[cnt_point] + edge[i].cost;
				pre_edge[end] = i;
				if (!vis[end]) {
					vis[end] = 1;
					queue[rear++] = end;
				}
			}
		}
		front++;
		vis[cnt_point] = 0;
	}
	if (dist[destination] == INF) {
		return 0;
	}
	int min_flow = 100000;
	for (int i = destination; i != source; i = edge[pre_edge[i]].start) {
		if (min_flow > edge[pre_edge[i]].cap) {
			min_flow = edge[pre_edge[i]].cap;
		}
	}
	for (int i = destination; i != source; i = edge[pre_edge[i]].start) {
		edge[pre_edge[i]].cap -= min_flow;
		edge[pre_edge[i] ^ 1].cap += min_flow;
		cost += edge[pre_edge[i]].cost * min_flow;
	}
	return 1;
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (!n && !m) {
			break;
		}
		memset(head, -1, sizeof(head));
		edge_number = 0;
		source = 0;
		destination = n + m + 1;
		point_number = n + m + 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				double cnt_cost;
				scanf("%lf", &cnt_cost);
				addEdge(i, j + n, 1, 0, cnt_cost, -cnt_cost);
			}
		}
		for (int i = 1; i <= n; i++) {
			addEdge(source, i, 1, 0, 0, 0);
		}
		for (int j = 1; j <= m; j++) {
			addEdge(j + n, destination, 1, 0, 0, 0);
		}
		double ans = 0;
		while (spfa(ans)) {
			;
		}
		printf("%.2lf\n", (ans + eps) / n);
	}
	return 0;
}
