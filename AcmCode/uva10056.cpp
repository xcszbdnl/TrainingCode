#include <cstdio>
#include <string.h>
#include <cmath>

const double eps = 1e-6;

double p, ans;
int n, to_win;

void search(int cnt, double pro) {
	if (pro < eps) {
		return ;
	}
	int people;
	if (cnt % n == 0) {
		people = n;
	}
	else {
		people = cnt % n;
	}
	if (people == to_win) {
		ans += pro * p;
	}
	search(cnt + 1, pro * (1 - p));
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		ans = 0;
		scanf("%d%lf%d", &n, &p, &to_win);
		if (p == 0) {
			ans = 0;
		}
		else {
			search(1, 1);
		}
		printf("%.4lf\n", ans);
	}
	return 0;
}