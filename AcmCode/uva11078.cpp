#include <iostream>
#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1000006;
int value[MAX_NUMBER];
int people;

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d", &people);
		for (int i = 1; i <= people; i++) {
			scanf("%d", &value[i]);
		}
		int max_ans = value[1] - value[2];
		int left_max = value[1];
		for (int i = 2; i <= people; i++) {
			if (left_max - value[i] > max_ans) {
				max_ans = left_max - value[i];
			}
			if (left_max < value[i]) {
				left_max = value[i];
			}
		}
		printf("%d\n", max_ans);
	}
	return 0;
}