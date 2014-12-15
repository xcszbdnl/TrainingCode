#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_POINT = 100006;
vector<int> path[MAX_POINT];
int vis[MAX_POINT], depth[MAX_POINT];
int point_number, query_number, depth_point, max_depth;

void dfs(int cnt_point) {
	if (depth[cnt_point] > max_depth) {
		max_depth = depth[cnt_point];
		depth_point = cnt_point;
	}
	for (int i = 0; i < path[cnt_point].size(); i++) {
		int next_point = path[cnt_point][i];
		if (!vis[next_point]) {
			depth[next_point] = depth[cnt_point] + 1;
			vis[next_point] = 1;
			dfs(next_point);
		}
	}
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d%d", &point_number, &query_number);
		for (int i = 1; i <= point_number; i++) {
			path[i].clear();
		}
		for (int i = 1; i < point_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			path[start].push_back(end);
			path[end].push_back(start);
		}
		max_depth = 0;
		memset(depth, 0, sizeof(depth));
		memset(vis, 0, sizeof(vis));
		dfs(1);
		max_depth = 0;
		memset(vis, 0, sizeof(vis));
		memset(depth, 0, sizeof(depth));
		dfs(depth_point);
		int max_number = max_depth;
		int k;
		for (int i = 1; i <= query_number; i++) {
			scanf("%d", &k);
			if (k <= max_number + 1) {
				printf("%d\n", k - 1);
			}
			else {
				printf("%d\n", (k - max_number - 1) * 2 + max_number);
			}
		}
	}
	return 0;
}