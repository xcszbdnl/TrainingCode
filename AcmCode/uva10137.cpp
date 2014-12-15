#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

double money[MAX_NUMBER];
double average, sums;
int people;

int main() {
	while (scanf("%d", &people) != EOF) {
		if (!people) {
			break;
		}
		sums = 0;
		for (int i = 1; i <= people; i++) {
			scanf("%lf", &money[i]);
			sums += money[i];
		}
		average = sums / people;
		double ans = 0;
		for (int i = 1; i <= people; i++) {
			if (money[i] < average) {
				ans += average - money[i];
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}