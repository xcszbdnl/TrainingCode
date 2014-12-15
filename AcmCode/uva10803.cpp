#include <cstdio>
#include <string.h>
#include <cmath>

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 105;
const double INF = 1000000000.0;
const double eps = 1e-6;
struct Point {
	int x;
	int y;
};
double maps[MAX_NUMBER][MAX_NUMBER];
struct Point point[MAX_NUMBER];
int point_number;

double getDist(int i, int j) {
	int x = point[i].x - point[j].x;
	x = x * x;
	int y = point[i].y - point[j].y;
	y = y * y;
	return sqrt(x + y + eps);
}

void floyd() {
	for (int k = 1; k <= point_number; k++) {
		for (int i = 1; i <= point_number; i++) {
			for (int j = 1; j <= point_number; j++) {
				if (maps[i][j] > maps[i][k] + maps[k][j]) {
					maps[i][j] = maps[i][k] + maps[k][j];
				}
			}
		}
	}
}

int main() {
	int test_case;
	int case_number = 1;
	scanf("%d", &test_case);
	int first = 1;
	while (test_case--) {
		//if (!first) {
		//	printf("\n");
		//}
		scanf("%d", &point_number);
		for (int i = 1; i <= point_number; i++) {
			scanf("%d%d", &point[i].x, &point[i].y);
		}
		for (int i = 1; i <= point_number; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j <= point_number; j++) {
				maps[i][j] = maps[j][i] = INF;
			}
		}
		for (int i = 1; i <= point_number; i++) {
			for (int j = i + 1; j <= point_number; j++) {
				double temp = getDist(i, j);
				if ((temp - 10.0) > eps) {
					continue;
				}
				maps[i][j] = maps[j][i] = temp;
			}
		}
		double max_number = 0;
		int flag = 0;
		floyd();
		for (int i = 1; i <= point_number; i++) {
			for (int j = i + 1; j <= point_number; j++) {
				if (maps[i][j] == INF) {
					flag = 1;
					break;
				}
				else {
					max_number = max(max_number, maps[i][j]);
				}
			}
		}
		printf("Case #%d:\n", case_number);
		case_number++;
		if (flag) {
			printf("Send Kurdy\n");
		}
		else {
			printf("%.4lf\n", max_number);
		}
		first = 0;
		printf("\n");
	}
	return 0;
}