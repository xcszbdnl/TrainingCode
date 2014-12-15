#include <cstdio>
#include <string.h>

int row, column;

int main() {
	scanf("%d%d", &row, &column);
	long long ans = row * column;
	if ((ans % 2) == 0) {
		printf("%d\n", ans / 2);
	}
	else {
		printf("%d\n", (ans - 1) / 2);
	}
	return 0;
}
