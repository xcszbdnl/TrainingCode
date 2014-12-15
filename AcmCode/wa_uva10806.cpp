#include <cstdio>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_NUMBER = 10003;
const int INF = 10000000;
const int MAX_POINT = 10001;

struct Edge {
	int start, end, dist;
};

struct HeapNode {
	int dist, start;
	bool operator < (const struct HeapNode &a) const {
		return a.dist < dist;
	}
};

struct Edge edge[MAX_NUMBER];
int pre[MAX_POINT];
int used[MAX_POINT];

struct Dijkstra {
	int point_number, edge_number;
	vector<Edge> edges;
	vector<int> g[MAX_POINT];
	
	bool done[MAX_POINT];
	int d[MAX_POINT];

	void init(int n) {
		point_number = n;
		for (int i = 1; i <= point_number; i++) {
			g[i].clear();
		}
		edges.clear();
	}

	void addEdge(int start, int end, int dist) {
		struct Edge cnt_edge;
		cnt_edge.start = start;
		cnt_edge.end = end;
		cnt_edge.dist = dist;
		edges.push_back(cnt_edge);
		edge_number = edges.size();
		g[start].push_back(edge_number);
	}

	void dijkstra() {
		priority_queue<HeapNode> q;
		memset(done, 0, sizeof(done));
		for (int i = 1; i <= point_number; i++) {
			d[i] = INF;
		}
		d[1] = 0;
		struct HeapNode cnt_node;
		cnt_node.dist = 0;
		cnt_node.start = 1;
		q.push(cnt_node);
		while (!q.empty()) {
			cnt_node = q.top();
			int cnt = cnt_node.start;
			q.pop();
			if (done[cnt]) {
				continue;
			}
			done[cnt] = 1;
			for (int i = 0; i < g[cnt].size(); i++) {
				struct Edge cnt_edge = edges[g[cnt][i] - 1];
				if (d[cnt_edge.end] > d[cnt] + cnt_edge.dist) {
					d[cnt_edge.end] = d[cnt] + cnt_edge.dist;
					pre[cnt_edge.end] = g[cnt][i];
					struct HeapNode temp;
					temp.start = cnt_edge.end;
					temp.dist = d[cnt_edge.end];
					q.push(temp);
				}
			}
			
		}

	}
};

struct Dijkstra solver;

int main() {
	int point_number, edge_number;
	while (scanf("%d", &point_number) != EOF) {
		if (!point_number) {
			break;
		}
		solver.init(point_number);
		memset(used, 0, sizeof(used));
		scanf("%d", &edge_number);
		for (int i = 1; i <= 2 * edge_number; i += 2) {
			int start, end, time;
			scanf("%d%d%D", &start, &end, &time);
			edge[i].start = start;
			edge[i].end = end;
			edge[i].dist = time;
			edge[i + 1].start = end;
			edge[i + 1].end = start;
			edge[i + 1].dist = time;
			solver.addEdge(start, end, time);
			solver.addEdge(end, start, time);
		}
		solver.dijkstra();
		int ans_1;
		if (solver.d[point_number] == INF) {
			printf("Back to jail\n");
			continue;
		}
		else {
			ans_1 = solver.d[point_number];
		}
		int cnt_point = point_number;
		int used_number = 0;
		while (cnt_point != 1) {
			used[++used_number] = pre[cnt_point];
			cnt_point = edge[pre[cnt_point]].start;
		}
		sort(used + 1, used + 1 + used_number);
		int cnt_number = 1;
		solver.init(point_number);
		for (int i = 1; i <= 2 * edge_number; i += 2) {
			if ((i == used[cnt_number]) || (i + 1 == used[cnt_number])) {
				cnt_number++;
			}
			else {
				solver.addEdge(edge[i].start, edge[i].end, edge[i].dist);
				solver.addEdge(edge[i + 1].start, edge[i + 1].end, edge[i + 1].dist);
			}
		}
		solver.dijkstra();
		if (solver.d[point_number] == INF) {
			printf("Back to jail\n");
		}
		else {
			int ans_2 = solver.d[point_number];
			printf("%d\n", ans_1 + ans_2);
		}
	}
	return 0;
}