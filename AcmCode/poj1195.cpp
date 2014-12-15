#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1050;

int tree[MAX_NUMBER][MAX_NUMBER];
int row;

int lowbit(int cnt_number) {
	return cnt_number & (-cnt_number);
}

void update(int x, int y, int value) {
	for (int i = x; i <= row; i += lowbit(i)) {
		for (int j = y; j <= row; j += lowbit(j)) {
			tree[i][j] += value;
			if (tree[i][j] < 0) {
				tree[i][j] = 0;
			}
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
	int operation;
	while (scanf("%d", &operation) != EOF) {
		if (operation == 0) {
			memset(tree, 0, sizeof(tree));
			scanf("%d", &row);
		}
		if (operation == 3) {
			break;
		}
		if (operation == 1) {
			int x, y, value;
			scanf("%d%d%d", &x, &y, &value);
			x++;
			y++;
			update(x, y, value);
		}
		if (operation == 2) {
			int x_1, y_1, x_2, y_2;
			scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
			x_1++;
			y_1++;
			x_2++;
			y_2++;
			int ans = query(x_2, y_2);
			if (x_1 - 1 >= 1 && y_1 - 1 >= 1) {
				int ans_2 = query(x_1 - 1, y_1 - 1);
				ans += ans_2;
			}
			if (y_1 - 1 >= 1) {
				int ans_2 = query(x_2, y_1 - 1);
				ans -= ans_2;
			}
			if (x_1 - 1 >= 1) {
				int ans_2 = query(x_1 - 1, y_2);
				ans -= ans_2;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}