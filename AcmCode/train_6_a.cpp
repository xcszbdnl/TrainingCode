#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1000006;
#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) > (b)) ? (b) : (a)
struct Segment {
	int left;
	int right;
	int max_number;
	int min_number;
};

struct Segment segment[MAX_NUMBER * 4];
int max_ans[MAX_NUMBER], min_ans[MAX_NUMBER], input[MAX_NUMBER];
int number, slide_window;


void build(int left, int right, int order) {
	int mid = (left + right) >> 1;
	segment[order].left = left;
	segment[order].right = right;
	if (left == right) {
		segment[order].min_number = segment[order].max_number = input[left];
		return ;
	}
	build(left, mid, order * 2);
	build(mid + 1, right, order * 2 + 1);
	segment[order].max_number = max(segment[order * 2].max_number, segment[order * 2 + 1].max_number);
	segment[order].min_number = min(segment[order * 2].min_number, segment[order * 2 + 1].min_number);
}

int queryMax(int left, int right, int order) {
	int mid = (segment[order].left + segment[order].right) >> 1;
	if (segment[order].left >= left && segment[order].right <= right) {
		return segment[order].max_number;
	}
	if (mid >= right) {
		return queryMax(left, right, order * 2);
	}
	else if (left > mid) {
		return queryMax(left, right, order * 2 + 1);
	}
	else {
		int left_ans = queryMax(left, mid, order * 2);
		int right_ans = queryMax(mid + 1, right, order * 2 + 1);
		return max(left_ans, right_ans);
	}
}


int queryMin(int left, int right, int order) {
	int mid = (segment[order].left + segment[order].right) >> 1;
	if (segment[order].left >= left && segment[order].right <= right) {
		return segment[order].min_number;
	}
	if (mid >= right) {
		return queryMin(left, right, order * 2);
	}
	else if (left > mid) {
		return queryMin(left, right, order * 2 + 1);
	}
	else {
		int left_ans = queryMin(left, mid, order * 2);
		int right_ans = queryMin(mid + 1, right, order * 2 + 1);
		return min(left_ans, right_ans);
	}
}

int main() {
	scanf("%d%d", &number, &slide_window);
	for (int i = 1; i <= number; i++) {
		scanf("%d", &input[i]);
	}
	build(1, number, 1);
	for (int i = 1; i <= number - slide_window + 1; i++) {
		max_ans[i] = queryMax(i, i + slide_window - 1, 1);
		min_ans[i] = queryMin(i, i + slide_window - 1, 1);
	}
	for (int i = 1; i <= number - slide_window + 1; i++) {
		printf("%d", min_ans[i]);
		if (i == number - slide_window + 1) {
			printf("\n");
		}
		else {
			printf(" ");
		}
	}
	for (int i = 1; i <= number - slide_window + 1; i++) {
		printf("%d", max_ans[i]);
		if (i == number - slide_window + 1) {
			printf("\n");
		}
		else {
			printf(" ");
		}
	}
	return 0;
}