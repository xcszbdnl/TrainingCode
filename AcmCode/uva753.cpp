#include <cstdio>
#include <string.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
const int MAX_NUMBER = 3000;
const int MAX_EDGE = 10000;
const int INF = 100000000;

struct Edge {
	int start;
	int end;
	int cap;
	int next;
};

struct Edge edge[MAX_EDGE];
int head[MAX_NUMBER], dist[MAX_NUMBER], queue[MAX_NUMBER], cur[MAX_NUMBER], stack[MAX_NUMBER];
int value[MAX_NUMBER];
map<string, int> maps;
vector<int> plug;
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

int cnt;

int main() {
	int test_case;
	int first = 1;
	scanf("%d", &test_case);
	while (test_case--) {
		if (!first) {
			printf("\n");
		}
		memset(head, -1, sizeof(head));
		memset(value, 0, sizeof(value));
		maps.clear();
		edge_number = 0;
		cnt = 1;
		source = 0;
		plug.clear();
		int plug_number, device, adapter;
		scanf("%d", &plug_number);
		int temp = plug_number;
		for (int i = 1; i <= plug_number; i++) {
			string name;
			cin >> name;
			plug.push_back(cnt);
			if (maps[name]) {
				value[maps[name]]++;
				temp--;
			}
			else {
				value[cnt] = 1;
				maps[name] = cnt++;
			}
		}
		scanf("%d", &device);
		for (int i = 1; i <= device; i++) {
			string device_name, plug;
			cin >> device_name >> plug;
			int id_1 = maps[plug];
			int id_2 = cnt;
			maps[device_name] = cnt++;
			addEdge(source, id_2, 1, 0);
			addEdge(id_2, id_1, 1, 0);
		}
		scanf("%d", &adapter);
		for (int i = 1; i <= adapter; i++) {
			string name_1, name_2;
			cin >> name_1 >> name_2;
			if (!maps[name_1]) {
				plug.push_back(cnt);
				maps[name_1] = cnt++;
			}
			if (!maps[name_2]) {
				plug.push_back(cnt);
				maps[name_2] = cnt++;
			}
			int id_1 = maps[name_1];
			int id_2 = maps[name_2];
			addEdge(id_1, id_2, INF, 0);
		}
		destination = cnt++;
		for (int i = 0; i < plug.size(); i++) {
			addEdge(plug[i], destination, value[plug[i]], 0);
		}
		int ans;
		ans = dinic();
		printf("%d\n", device - ans);
		first = 0;
	}
	return 0;
}