#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_NUMBER = 30005;
vector<int> path[MAX_NUMBER];
int value[MAX_NUMBER], vis[MAX_NUMBER];
int cnt;
int point_number, edge_number;

void dfs(int cnt_point) {
	value[cnt]++;
	for (int i = 0; i < path[cnt_point].size(); i++) {
		int next_point = path[cnt_point][i];
		if (!vis[next_point]) {
			vis[next_point] = 1;
			dfs(next_point);
		}
	}
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d%d", &point_number, &edge_number);
		memset(value, 0, sizeof(value));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= point_number; i++) {
			path[i].clear();
		}
		cnt = 0;
		for (int i = 1; i <= edge_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			path[start].push_back(end);
			path[end].push_back(start);
		}
		for (int i = 1; i <= point_number; i++) {
			if (!vis[i]) {
				cnt++;
				vis[i] = 1;
				dfs(i);
			}
		}
		int max_number = 0;
		for (int i = 1; i <= cnt; i++) {
			max_number = std::max(max_number, value[i]);
		}
		printf("%d\n", max_number);
	}
	return 0;
}