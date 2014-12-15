#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 15006;
struct Point {
	double x;
	int people;
};

struct Point point[MAX_NUMBER];
double sums;
int city_number;

bool cmp(struct Point a, struct Point b) {
	return a.x < b.x;
}

int main() {
	scanf("%d", &city_number);
	sums = 0;
	for (int i = 1; i <= city_number; i++) {
		scanf("%lf%d", &point[i].x, &point[i].people);
		sums += point[i].people;
	}
	sort(point + 1, point + 1 + city_number, cmp);
	int k = 0;
	double cnt_sums = 0;
	while (cnt_sums < sums / 2) {
		k++;
		cnt_sums += point[k].people;
	}
	printf("%.5lf\n", point[k].x);
	return 0;
}