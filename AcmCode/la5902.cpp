#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 200005;

int tree_array[MAX_NUMBER + 3], location[MAX_NUMBER];
int moive_number, watch_number;

int lowbit(int x) {
	return x & (-x);
}

void init() {
	for (int i = 1; i <= moive_number; i++) {
		location[i] = moive_number - i + 1;
	}
	for (int i = 1; i <= MAX_NUMBER; i++) {
		tree_array[i] = lowbit(i);
	}
}

int getSum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += tree_array[x];
		x -= lowbit(x);
	}
	return ans;
}

void update(int x, int d) {
	while (x <= MAX_NUMBER) {
		tree_array[x] += d;
		x += lowbit(x);
	}
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d%d", &moive_number, &watch_number);
		init();
		int top = moive_number;
		for (int i = 1; i <= watch_number; i++) {
			int watch_moive;
			scanf("%d", &watch_moive);
			int cnt_location = location[watch_moive];
			int ans = getSum(cnt_location);
			if (i == 1) {
				printf("%d", moive_number - ans);
			}
			else {
				printf(" %d", moive_number - ans);
			}
			update(cnt_location, -1);
			top++;
			location[watch_moive] = top;
		}
		printf("\n");
	}
	return 0;
}