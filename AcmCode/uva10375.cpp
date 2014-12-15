#include <cstdio>
#include <string.h>

int p, q, s, r;
double ans;

int main() {
	while (scanf("%d%d%d%d", &p, &q, &r, &s) != EOF) {
		ans = 1;
		if (s >= q) {
			for (int i = 0; i < q; i++) {
				ans = ans * (p - i) / (r - i);
			}
			for (int i = 1; i <= s - q; i++) {
				ans = ans * (q + i) / (r - (q + i - 1));
			}
		}
		else {
			for (int i = 0; i < s; i++) {
				ans = ans * (p - i) / (r - i);
			}
			for (int i = 1; i <= q - s; i++) {
				ans = ans * (p - (s + i - 1)) / (s + i);
			}
		}
		printf("%.5lf\n", ans);
	}
	return 0;
}