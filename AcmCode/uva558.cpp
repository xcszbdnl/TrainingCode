#include <string.h>
#include <cstdio>

const int MAX_NUMBER = 2006;
const int INF = 100000000;
struct Edge {
	int start;
	int end;
	int value;
};

struct Edge edge[MAX_NUMBER];
int distance[MAX_NUMBER];
int point_number, edge_number, cnt_edge;

void addEdge(int start, int end, int value) {
	edge[edge_number].start = start;
	edge[edge_number].end = end;
	edge[edge_number].value = value;
	edge_number++;
}

int bellmanFord() {
	for (int i = 0; i < point_number; i++) {
		distance[i] = INF;
	}
	distance[0] = 0;
	for (int i = 1; i < point_number; i++) {
		int flag = 0;
		for (int m = 0; m < edge_number; m++) {
			int start, end;
			start = edge[m].start;
			end = edge[m].end;
			if (distance[start] != INF && distance[end] > distance[start] + edge[m].value) {
				distance[end] = distance[start] + edge[m].value;
				flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
	for (int m = 0; m < edge_number; m++) {
		int start, end;
		start = edge[m].start;
		end = edge[m].end;
		if (distance[start] != INF && distance[end] > distance[start] + edge[m].value) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		edge_number = 0;
		scanf("%d%d", &point_number, &cnt_edge);
		for (int i = 1; i <= cnt_edge; i++) {
			int start, end, value;
			scanf("%d%d%d", &start, &end, &value);
			addEdge(start, end, value);
		}
		int flag = bellmanFord();
		if (!flag) {
			printf("possible\n");
		}
		else {
			printf("not possible\n");
		}
	}
	return 0;
}