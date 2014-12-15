#include <cstdio>
#include <string.h>

const int MAX_EDGE = 20006;
const int MAX_POINT = 1000;
const long long INF = 100000ll * 100000ll * 100000ll;

struct Edge {
	int start;
	int end;
	long long cap;
	long long cost;
	int next;
};

struct Temp {
	int start;
	int end;
	long long cost;
};

struct Edge edge[MAX_EDGE];
struct Temp temp[MAX_EDGE];
int head[MAX_POINT], queue[MAX_POINT], pre_edge[MAX_POINT], vis[MAX_POINT];
long long dist[MAX_POINT];
int source, destination, point_number, edge_number;

void addEdge(int start, int end, long long cap_1, long long cap_2, long long cost_1, long long cost_2) {
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

int spfa(long long &flow, long long &cost) {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= point_number; i++) {
		dist[i] = INF;
	}
	int front = 0;
	int rear = 1;
	dist[source] = 0;
	queue[front] = source;
	vis[source] = 1;
	while (front < rear) {
		int cnt_point = queue[front];
		for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
			int end = edge[i].end;
			if (edge[i].cap > 0 && dist[end] > dist[cnt_point] + edge[i].cost) {
				dist[end] = dist[cnt_point] + edge[i].cost;
				pre_edge[end] = i;
				if (!vis[end]) {
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
	long long min_flow = INF;
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
	flow += min_flow;
	return 1;
}
long long total_flow, cap;
int main() {
	int cnt_edge;
	while (scanf("%d%d", &point_number, &cnt_edge) != EOF) {
		memset(head, -1, sizeof(head));
		edge_number = 0;
		for (int i = 1; i <= cnt_edge; i++) {
			int start, end;
			long long cost;
			scanf("%d%d%lld", &start, &end, &cost);
			temp[i].start = start;
			temp[i].end = end;
			temp[i].cost = cost;
		}
		scanf("%lld%lld", &total_flow, &cap);
		for (int i = 1; i <= cnt_edge; i++) {
			addEdge(temp[i].start, temp[i].end, cap, 0, temp[i].cost, -temp[i].cost);
			addEdge(temp[i].end, temp[i].start, cap, 0, temp[i].cost, -temp[i].cost);
		}
		addEdge(point_number, point_number + 1, total_flow, 0, 0, 0);
		point_number++;
		destination = point_number;
		source = 1;
		long long flow = 0, cost = 0;
		while (spfa(flow, cost)) {
			;
		}
		if (flow < total_flow) {
			printf("Impossible.\n");
		}
		else {
			printf("%lld\n", cost);
		}
	}
	return 0;
}