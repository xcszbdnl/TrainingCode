#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 305;
struct Point {
	int x,y;
};

struct Point point[MAX_NUMBER];
double cross(Point a, Point b) {
	return a.x * b.y * 1.0 - a.y * b.x * 1.0;
}

double getArea(int i, int j, int k, int m) {
	double area = 0;
	area += cross(point[i], point[j]);
	area += cross(point[j], point[k]);
	area += cross(point[k], point[m]);
	area += cross(point[m], point[i]);
	area /= 2;
	return area < 0 ? -area : area;
}

int main() {
	int number;
	scanf("%d", &number);
	for (int i = 1; i <= number; i++) {
		scanf("%d%d", &point[i].x, &point[i].y);
	}
	double ans = 0.0;
	for (int i = 1; i <= number; i++) {
		for (int j = i + 1; j <= number; j++) {
			for (int k = j + 1; k <= number; k++) {
				for (int m = k + 1; m <= number; m++) {
					double temp = getArea(i, j, k, m);
					if (temp > ans) {
						ans = temp;
					}
				}
			}
		}
	}
	printf("%.9lf\n", ans);
	return 0;
}