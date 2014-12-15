#include <cstdio>
#include <cmath>
#include <string.h>

const int MAX_NUMBER = 105;
const double INF = 10000000000;

struct Point {
	double x;
	double y;
};

struct Point point[MAX_NUMBER];
double maps[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER];
double lowest[MAX_NUMBER];
int point_number;

double getDistance(int i, int j) {
	double x_square = point[i].x - point[j].x;
	double y_square = point[i].y - point[j].y;
	return sqrt(x_square * x_square + y_square * y_square);
}

double prim() {
	double ans = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= point_number; i++) {
		lowest[i] = maps[1][i];
	}
	vis[1] = 1;
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
	return ans;
}
int main() {
	int test_case;
	int first = 1;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d", &point_number);
		if (!first) {
			printf("\n");
		}
		for (int i = 1; i <= point_number; i++) {
			scanf("%lf%lf", &point[i].x, &point[i].y);
		}
		for (int i = 1; i <= point_number; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j <= point_number; j++) {
				maps[i][j] = maps[j][i] = getDistance(i, j);
			}
		}
		double sums = prim();
		printf("%.2lf\n", sums);
		first = 0;
	}
	return 0;
}