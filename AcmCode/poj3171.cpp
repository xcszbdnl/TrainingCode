#include <cstdio>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;

struct Cow {
	int start;
	int end;
	int cost;
};

struct Segment {
	int left;
	int right;
	long long min_number;
};
#define min(a,b) ((a) > (b)) ? (b) : (a)

const int MAX_NUMBER = 87000;
const int MAX_COW = 10005;
const long long INF = 5000000006;

struct Cow cows[MAX_COW];
struct Segment segment[MAX_NUMBER * 4];
long long dp[MAX_NUMBER];
int start_time, end_time, cow_number;

bool cmp(struct Cow a, struct Cow b) {
	return a.end < b.end;
}

void build(int order, int left, int right) {
	segment[order].left = left;
	segment[order].right = right;
	if (left == right) {
		segment[order].min_number = dp[left];
		return ;
	}
	int mid = (left + right) >> 1;
	build(order * 2, left, mid);
	build(order * 2 + 1, mid + 1, right);
	segment[order].min_number = min(segment[order * 2].min_number, segment[order * 2 + 1].min_number);
}

void update(int order, int left, int right, long long value) {
	int mid = (segment[order].left + segment[order].right) >> 1;
	if (segment[order].left >= left && segment[order].right <= right) {
		segment[order].min_number = min(segment[order].min_number, value);
		return ;
	}
	if (right <= mid) {
		update(order * 2, left, right, value);
	}
	else if (left > mid) {
		update(order * 2 + 1, left, right, value);
	}
	else {
		update(order * 2, left, mid, value);
		update(order * 2 + 1, mid + 1, right, value);
	}
	segment[order].min_number = min(segment[order * 2].min_number, segment[order * 2 + 1].min_number);
}

long long query(int order, int left, int right) {
	int mid = (segment[order].left + segment[order].right) >> 1;
	if (segment[order].left >= left && segment[order].right <= right) {
		return segment[order].min_number;
	}
	if (right <= mid) {
		return query(order * 2, left, right);
	}
	else if (left > mid) {
		return query(order * 2 + 1, left, right);
	}
	else {
		long long left_ans = query(order * 2, left, mid);
		long long right_ans = query(order * 2 + 1, mid + 1, right);
		return min(left_ans, right_ans);
	}
}

int main() {
	scanf("%d%d%d", &cow_number, &start_time, &end_time);
	start_time += 2;
	end_time += 2;
	for (int i = 1; i <= cow_number; i++) {
		scanf("%d%d%d", &cows[i].start, &cows[i].end, &cows[i].cost);
		cows[i].start += 2;
		cows[i].end += 2;
	}
	sort(cows + 1, cows + 1 + cow_number, cmp);
	for (int i = 1; i <= end_time; i++) {
		dp[i] = INF;
	}
	dp[start_time - 1] = 0;
	build(1, 1, end_time);
	for (int i = 1; i <= cow_number; i++) {
		long long ans = query(1, cows[i].start - 1, cows[i].end - 1);
		dp[cows[i].end] = ans + cows[i].cost;
		update(1, cows[i].end, cows[i].end, dp[cows[i].end]);
	}
	if (dp[end_time] >= INF) {
		cout << -1 << endl;
	}
	else {
		cout << dp[end_time] << endl;
	}
	return 0;
}