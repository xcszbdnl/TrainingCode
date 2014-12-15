#include <cstdio>
#include <string.h>
#include <cmath>

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_POINT = 770;
const int INF = 10000000;
const double eps = 1e-6;

struct Point {
	int x;
	int y;
};

struct Point point[MAX_POINT];
double maps[MAX_POINT][MAX_POINT];
double lowest[MAX_POINT], ans;
int vis[MAX_POINT];
int point_number, exist_number;

double getDistance(int i, int j) {
	int x = point[i].x - point[j].x;
	int y = point[i].y - point[j].y;
	return sqrt(x * x + y * y + eps);
}

void prim() {
	memset(vis, 0, sizeof(vis));
	memset(lowest, 0, sizeof(lowest));
	for (int i = 1; i <= point_number; i++) {
		lowest[i] = maps[1][i];
	}
	vis[1] = 1;
	ans = 0;
	for (int i = 1; i < point_number; i++) {
		double min_ans = INF;
		int cnt_point;
		for (int j = 1; j <= point_number; j++) {
			if (!vis[j] && lowest[j] < min_ans) {
				cnt_point = j;
				min_ans = lowest[j];
			}
		}
		ans += min_ans;
		vis[cnt_point] = 1;
		for (int j = 1; j <= point_number; j++) {
			if (!vis[j] && lowest[j] > maps[cnt_point][j]) {
				lowest[j] = maps[cnt_point][j];
			}
		}
	}
}

int main() {
	while (scanf("%d", &point_number) != EOF) {
		memset(maps, 0, sizeof(maps));
		for (int i = 1; i <= point_number; i++) {
			scanf("%d%d", &point[i].x, &point[i].y);
		}
		for (int i = 1; i <= point_number; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j <= point_number; j++) {
				maps[i][j] = maps[j][i] = getDistance(i, j);
			}
		}
		scanf("%d", &exist_number);
		for (int i = 1; i <= exist_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			maps[start][end] = maps[end][start] = 0;
		}
		prim();
		printf("%.2lf\n", ans);
	}
	return 0;
}
