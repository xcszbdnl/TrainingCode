#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 105;
const int INF = 10000005;

int maps[MAX_NUMBER][MAX_NUMBER];
int lowest[MAX_NUMBER], vis[MAX_NUMBER];
int point_number, ans;

void prim() {
	ans = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= point_number; i++) {
		lowest[i] = maps[1][i];
	}
	vis[1] = 1;
	for (int i = 1; i < point_number; i++) {
		int cnt_point;
		int min_ans = INF;
		for (int j = 1; j <= point_number; j++) {
			if (!vis[j] && lowest[j] < min_ans) {
				min_ans = lowest[j];
				cnt_point = j;
			}
		}
		vis[cnt_point] = 1;
		ans += min_ans;
		for (int j = 1; j <= point_number; j++) {
			if (!vis[j] && maps[cnt_point][j] < lowest[j]) {
				lowest[j] = maps[cnt_point][j];
			}
		}
	}
}

int main() {
	while (scanf("%d", &point_number) != EOF) {
		if (!point_number) {
			break;
		}
		for (int i = 1; i <= point_number * (point_number - 1) / 2; i++) {
			int start, end, value, is_build;
			scanf("%d%d%d%d", &start, &end, &value, &is_build);
			if (is_build) {
				maps[start][end] = maps[end][start] = 0;
			}
			else {
				maps[start][end] = maps[end][start] = value;
			}
		}
		prim();
		printf("%d\n", ans);
	}
	return 0;
}