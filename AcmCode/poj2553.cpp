#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>


#define MAX_NUMBER 5005
#define min(a,b) ((a) > (b)) ? (b) : (a)

using namespace std;
vector<int> path[MAX_NUMBER];
stack<int> s;
int low[MAX_NUMBER], pre[MAX_NUMBER], block_number[MAX_NUMBER], degree[MAX_NUMBER], ans[MAX_NUMBER], zero_degree[MAX_NUMBER];
int dfs_index, block_index, point_number, pair_number;

void dfs(int cnt_point) {
	low[cnt_point] = pre[cnt_point] = ++dfs_index;
	s.push(cnt_point);
	for (int i = 0; i < path[cnt_point].size(); i++) {
		int next_point = path[cnt_point][i];
		if (!pre[next_point]) {
			dfs(next_point);
			low[cnt_point] = min(low[cnt_point], low[next_point]);
		}
		else if (!block_number[cnt_point]) {
			low[cnt_point] = min(low[cnt_point], pre[next_point]);
		}
	}
	if (low[cnt_point] == pre[cnt_point]) {
		block_index++;
		while (1) {
			int x = s.top();
			s.pop();
			block_number[x] = block_index;
			if (x == cnt_point) {
				break;
			}
		}
	}
}

void findBcc() {
	memset(low, 0, sizeof(low));
	memset(pre, 0, sizeof(pre));
	memset(block_number, 0, sizeof(block_number));
	dfs_index = block_index = 0;
	for (int i = 1; i <= point_number; i++) {
		if (!pre[i]) {
			dfs(i);
		}
	}
}


int main() {
	while (scanf("%d", &point_number) != EOF) {
		if (!point_number) {
			break;
		}
		for (int i = 1; i <= point_number; i++) {
			path[i].clear();
		}
		scanf("%d", &pair_number);
		for (int i = 1; i <= pair_number; i++) {
			int point_1, point_2;
			scanf("%d%d", &point_1, &point_2);
			path[point_1].push_back(point_2);
		}
		findBcc();
		memset(degree, 0, sizeof(degree));
		for (int i = 1; i <= point_number; i++) {
			for (int j = 0; j < path[i].size(); j++) {
				int next_point = path[i][j];
				if (block_number[i] != block_number[next_point]) {
					degree[block_number[i]]++;
				}
			}
		}
		int zero_number = 0;
		for (int i = 1; i <= block_index; i++) {
			if (degree[i] == 0) {
				zero_degree[zero_number++] = i;
			}
		}
		int ans_number = 0;
		for (int i = 1; i <= point_number; i++) {
			int find = 0;
			for (int j = 0; j < zero_number; j++) {
				if (block_number[i] == zero_degree[j]) {
					find = 1;
					break;
				}
			}
			if (find) {
				ans[ans_number++] = i;
			}
		}
		sort(ans, ans + ans_number);
		for (int i = 0; i < ans_number; i++) {
			if (!i) {
				printf("%d", ans[i]);
			}
			else {
				printf(" %d", ans[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
