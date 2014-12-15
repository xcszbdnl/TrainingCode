#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;
const int MAX_NUMBER = 4006;
vector<int> path[MAX_NUMBER];
int temp_ans[MAX_NUMBER], ans[MAX_NUMBER], vis[MAX_NUMBER];
int flag;
int city_number;

void dfs(int cnt_point, int number) {
	if (number > 4 * city_number) {
		flag = 1;
		return ;
	}
	for (int i = 0; i < path[cnt_point].size() && !flag; i++) {
		int next_point = path[cnt_point][i];
		if (!vis[next_point]) {
			vis[next_point] = 1;
			ans[number] = next_point;
			dfs(next_point, number + 1);
		}
	}
}

int main() {
	scanf("%d", &city_number);
	flag = 0;
	for (int i = 1; i <= city_number * 2; i++) {
		int start, end;
		scanf("%d%d", &start, &end);
		path[start].push_back(end);
		path[end].push_back(start);
	}
	for (int i = 1; i <= city_number; i++) {
		for (int j = 3; j >= 0; j--) {
			int point_1 = i * 4 - j;
			for (int k = point_1 + 1; k <= 4 * i; k++) {
				path[point_1].push_back(k);
				path[k].push_back(point_1);
			}
		}
	}
	vis[1] = 1;
	dfs(1,2);
	ans[1] = 1;
	if (flag) {
		printf("Yes\n%d", ans[1]);
		for (int i = 2; i <= city_number * 4; i++) {
			printf(" %d", ans[i]);
		}
		printf("\n");
	}
	else {
		printf("No\n");
	}
	return 0;
}