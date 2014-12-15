#include <cstdio>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int MAX_NUMBER = 200;
const double INF = 10000000;
const double eps = 1e-7;
int number[MAX_NUMBER];
int order[MAX_NUMBER];

struct Edge {
	int start;
	int end;
	double time;
	double cost;
	double dist;
	Edge(int start, int end, double time, double cost) {
		this->start = start;
		this->end = end;
		this->time = time;
		this->cost = cost;
	}
};

struct BellmanFord {
	int point_number;
	int edge_number;
	vector<int> g[MAX_NUMBER];
	vector<Edge> edges;
	int father[MAX_NUMBER];
	int vis[MAX_NUMBER];
	double d[MAX_NUMBER];
	int cnt[MAX_NUMBER];

	void init(int point_number) {
		this->point_number = point_number;
		for (int i = 1; i <= point_number; i++) {
			g[i].clear();
		}
		edges.clear();
	}
	void addEdge(int start, int end, double time, double cost) {
		struct Edge cnt_edge = Edge(start, end, time, cost);
		edges.push_back(cnt_edge);
		edge_number = edges.size();
		g[start].push_back(edge_number - 1);
	}
	int negativeCycle() {
		queue<int> q;
		memset(vis, 0, sizeof(vis));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= point_number; i++) {
			d[i] = INF;
		}
		d[1] = 0;
		vis[1] = 1;
		q.push(1);
		while (!q.empty()) {
			int cnt_point = q.front();
			q.pop();
			vis[cnt_point] = 0;
			for (int i = 0; i < g[cnt_point].size(); i++) {
				struct Edge cnt_edge = edges[g[cnt_point][i]];
				if (d[cnt_edge.end] > d[cnt_point] + cnt_edge.dist) {
					d[cnt_edge.end] = d[cnt_point] + cnt_edge.dist;
					father[cnt_edge.end] = cnt_point;
					if (!vis[cnt_edge.end]) {
						vis[cnt_edge.end] = 1;
						q.push(cnt_edge.end);
						if (++cnt[cnt_edge.end] > point_number) {
							return cnt_edge.end;
						}
					}
				}
			}
		}
		return 0;
	}
};

struct BellmanFord solver;

int test(double ans) {
	for (int i = 0; i < solver.edges.size(); i++) {
		solver.edges[i].dist = solver.edges[i].time * ans - solver.edges[i].cost;
	}
	int ret = solver.negativeCycle();
	return ret;
}

int main() {
	int point_number, edge_number;
	scanf("%d%d", &point_number, &edge_number);
	solver.init(point_number);
	for (int i = 1; i <= edge_number; i++) {
		int start, end;
		double time, cost;
		scanf("%d%d%lf%lf", &start, &end, &cost, &time);
		solver.addEdge(start, end, time, cost);
	}
	double low = 0;
	double high = INF;
	int ans;
	while (high - low > eps) {
		double mid = (high + low) / 2;
		int temp = test(mid);
		if (temp) {
			low = mid;
			ans = temp;
		}
		else {
			high = mid;
		}
	}
	ans = test(low);
	if (!ans) {
		printf("0\n");
		return 0;
	}
	memset(number, 0, sizeof(number));
	int ans_number = 0;
	while (number[ans] <= 1) {
		number[ans]++;
		if (number[ans] >= 2) {
			++ans_number;
			order[ans_number] = ans;
		}
		ans = solver.father[ans];
	}
	printf("%d\n", ans_number);
	for (int i = ans_number; i >= 1; i--) {
		if (i == ans_number) {
			printf("%d", order[i]);
		}
		else {
			printf(" %d", order[i]);			
		}
	}
	printf("\n");
	return 0;
}