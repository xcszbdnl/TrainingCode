#include <cstdio>
#include <string.h>

long long value[20];
int n, k;

int main() {
	value[0] = 1;
	for (int i = 1; i <= 13; i++) {
		value[i] = value[i - 1] * i;
	}
	while (scanf("%d%d", &n, &k) != EOF) {
		long long ans = value[n];
		for (int i = 1; i <= k; i++) {
			int temp;
			scanf("%d", &temp);
			ans /= value[temp];
		}
		printf("%lld\n", ans);
	}
	return 0;
}