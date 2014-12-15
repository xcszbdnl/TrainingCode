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

int main() {
	source = 0;
	maps["XXL"] = 1;
	maps["XL"] = 2;
	maps["L"] = 3;
	maps["M"] = 4;
	maps["S"] = 5;
	maps["XS"] = 6;
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		edge_number = 0;
		memset(head, -1, sizeof(head));
		int t_shirt, people;
		scanf("%d%d", &t_shirt, &people);
		for (int i = 1; i <= 6; i++) {
			addEdge(source, i, t_shirt / 6, 0);
		}
		destination = 6 + people + 1;
		for (int i = 1; i <= people; i++) {
			char like_1[10], like_2[10];
			scanf("%s%s", like_1, like_2);
			int id_1 = maps[like_1];
			int id_2 = maps[like_2];
			addEdge(id_1, i + 6, 1, 0);
			addEdge(id_2, i + 6, 1, 0);
			addEdge(i + 6, destination, 1, 0);
		}
		int ans;
		ans = dinic();
		if (ans == people) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}