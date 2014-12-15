#include <cstdio>
#include <string.h>

const int MAX_POINT = 120;
const int MAX_EDGE = 100006;
const int INF = 10000000;
#define min(a,b) ((a) > (b)) ? (b) : (a)
struct Edge {
	int start;
	int end;
	int cap;
	int next;
};

struct Edge edge[MAX_EDGE];
int edge_number;
int head[MAX_POINT], stack[MAX_POINT], distance[MAX_POINT], queue[MAX_POINT * 4], cur[MAX_POINT];
int regulator[MAX_POINT];
int regulator_number, source, destination;

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
	memset(distance, -1, sizeof(distance));
	int front = 0;
	int rear = 1;
	distance[source] = 0;
	queue[front] = source;
	while (front < rear) {
		int cnt_point = queue[front];
		for (int i = head[cnt_point]; i != -1; i = edge[i].next) {
			int next_point = edge[i].end;
			if (edge[i].cap > 0 && distance[next_point] == -1) {
				distance[next_point] = distance[cnt_point] + 1;
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
	int top, min_flow, min_flow_number;
	int ans = 0;
	while (bfs()) {
		memcpy(cur, head, sizeof(head));
		top = 0;
		int cnt_point = source;
		while (1) {
			if (cnt_point == destination) {
				min_flow = INF;
				for (int i = 0; i < top; i++) {
					if (min_flow > edge[stack[i]].cap) {
						min_flow = edge[stack[i]].cap;
						min_flow_number = i;
					}
				}
				for (int i = 0; i < top; i++) {
					edge[stack[i]].cap -= min_flow;
					edge[stack[i] ^ 1].cap += min_flow;
				}
				ans += min_flow;
				top = min_flow_number;
				cnt_point = edge[stack[top]].start;
			}
			for (int i = cur[cnt_point]; i != -1; cur[cnt_point] = i = edge[i].next) {
				if (edge[i].cap > 0 && distance[edge[i].end] == distance[cnt_point] + 1) {
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
				distance[cnt_point] = -1;
				top--;
				cnt_point = edge[stack[top]].start;
			}
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &regulator_number) != EOF) {
		memset(head, -1, sizeof(head));
		edge_number = 0;
		source = 0;
		destination = regulator_number + 1;
		for (int i = 1; i <= regulator_number; i++) {
			scanf("%d", &regulator[i]);
		}
		int cnt_edge;
		scanf("%d", &cnt_edge);
		for (int i = 1; i <= cnt_edge; i++) {
			int start, end, cap;
			scanf("%d%d%d", &start, &end, &cap);
			int cap_min = min(cap, regulator[start]);
			addEdge(start, end, cap_min, 0);
		}
		int start_number, end_number;
		scanf("%d%d", &start_number, &end_number);
		for (int i = 1; i <= start_number; i++) {
			int start;
			scanf("%d", &start);
			addEdge(source, start, regulator[start], 0);
		}
		for (int i = 1; i <= end_number; i++) {
			int end;
			scanf("%d", &end);
			addEdge(end, destination, regulator[end], 0);
		}
		int max_flow;
		max_flow = dinic();
		printf("%d\n", max_flow);
	}
	return 0;
}