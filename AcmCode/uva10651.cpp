#include <iostream>
#include <string.h>
#include <cstdio>


using namespace std;
#define MAX_NUMBER 12
#define MAX_STATE (1 << 12)

char state[MAX_NUMBER];
int dp[MAX_STATE];

int test(int cnt_state) {
  for (int i = 0; i < MAX_NUMBER - 2; i++) {
		if (cnt_state & (1 << i)) {
			if ((cnt_state & (1 << (i + 1))) && !(cnt_state & (1 << (i + 2)))) {
				return 0;
			}
		}
		else {
			if ((cnt_state & (1 << (i + 1))) && (cnt_state & (1 << (i + 2)))) {
				return 0;
			}
		}
	}
	return 1;
}

void search(int cnt_state) {
	if (dp[cnt_state] != -1) {
		return ;
	}
	int next_number = 12;
	for (int i = 0; i < MAX_NUMBER - 2; i++) {
		if (cnt_state & (1 << i)) {
			if ((cnt_state & (1 << (i + 1))) && !(cnt_state & (1 << (i + 2)))) {
				int next_state = cnt_state ^ (1 << i) ^ (1 << (i + 1)) | (1 << (i + 2));
				search(next_state);
				if (next_number > dp[next_state]) {
					next_number = dp[next_state];
				}
			}
		}
		else {
			if ((cnt_state & (1 << (i + 1))) && (cnt_state & (1 << (i + 2)))) {
				int next_state = cnt_state ^ (1 << (i + 1)) ^ (1 << (i + 2)) | (1 << i);
				search(next_state);
				if (next_number > dp[next_state]) {
					next_number = dp[next_state];
				}
			}
		}
	}
	dp[cnt_state] = next_number;
}
int getNum(int cnt_state) {
	int zero_number = 0;
	for (int i = 0; i < MAX_NUMBER; i++) {
		if ((1 << i) & cnt_state) {
			zero_number++;
		}
	}
	return zero_number;
}

int main() {
	int test_case;
	scanf("%d", &test_case);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < MAX_STATE; i++) {
		if (test(i)) {
			dp[i] = getNum(i);
		}
	}
	while (test_case--) {
		scanf("%s", state);
		int state_number = 0;
		for (int i = 0; i < MAX_NUMBER; i++) {
			if (state[i] == 'o') {
				state_number = state_number | (1 << i);
			}
		}
		search(state_number);
		printf("%d\n", dp[state_number]);
	}
	return 0;
}
