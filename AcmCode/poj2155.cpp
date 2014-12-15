#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

int tree[MAX_NUMBER][MAX_NUMBER];
int row, query_number, ans;

int lowbit(int cnt_number) {
	return cnt_number & (-cnt_number);
}

void update(int x, int y) {
	for (int i = x; i <= row; i += lowbit(i)) {
		for (int j = y; j <= row; j += lowbit(j)) {
			tree[i][j] += 1;
		}
	}
}

int query(int x, int y) {
	int sums = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {
			sums += tree[i][j];
		}
	}
	return sums;
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(tree, 0, sizeof(tree));
		scanf("%d%d", &row, &query_number);
		for (int i = 1; i <= query_number; i++) {
			char operation[10];
			scanf("%s", operation);
			if (operation[0] == 'C') {
				int x_1, y_1, x_2, y_2;
				scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
				update(x_1, y_1);
				update(x_2 + 1, y_1);
				update(x_1, y_2 + 1);
				update(x_2 + 1, y_2 + 1);
			}
			else {
				int x_1, y_1;
				scanf("%d%d", &x_1, &y_1);
				ans = query(x_1, y_1);
				printf("%d\n", ans % 2);
			}
		}
		if (test_case) {
			printf("\n");
		}
	}
	return 0;
}