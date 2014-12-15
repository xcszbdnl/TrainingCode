#include <cstdio>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int value;
	int cost;
};

const int MAX_NUMBER = 100020;
const int INF = 10000000;
vector<int> path[MAX_NUMBER];
struct Node node_1[MAX_NUMBER], node_2[MAX_NUMBER];
int vis[MAX_NUMBER], block_number[MAX_NUMBER];
int lucky[MAX_NUMBER];
int point_number, edge_number, block_index, lucky_number, node_number, bag_number;

void dfs(int cnt_point) {
	block_number[block_index]++;
	vis[cnt_point] = 1;
	for (int i = 0; i < path[cnt_point].size(); i++) {
		int next_point = path[cnt_point][i];
		if (!vis[next_point]) {
			dfs(next_point);
		}
	}
}

void getLucky() {
	int front = 0;
	int rear = 2;
	lucky[front] = 4;
	lucky[front + 1] = 7;
	while (front < rear) {
		int cnt_number = lucky[front];
		int next_number = cnt_number * 10 + 4;
		if (next_number < MAX_NUMBER) {
			lucky[rear++] = next_number;
		}
		next_number = cnt_number * 10 + 7;
		if (next_number < MAX_NUMBER) {
			lucky[rear++] = next_number;
		}
		front++;
	}
	lucky_number = rear - 1;
	sort(lucky, lucky + lucky_number);
}

int main() {
	memset(vis, 0, sizeof(vis));
	memset(block_number, 0, sizeof(block_number));
	scanf("%d%d", &point_number, &edge_number);
	for (int i = 1; i <= edge_number; i++) {
		int start, end;
		scanf("%d%d", &start, &end);
		if (start != end) {
			path[start].push_back(end);
			path[end].push_back(start);
		}
	}
	block_index = 0;
	for (int i = 1; i <= point_number; i++) {
		if (!vis[i]) {
			block_index++;
			dfs(i);
		}
	}
	getLucky();
	sort(block_number + 1, block_number + block_index + 1);
	int node_number = 0;
	int sums = block_number[1];
	node_1[0].cost = 1;
	node_1[0].value = block_number[1];
	for (int i = 2; i <= block_index; i++) {
		if (block_number[i] == block_number[i - 1]) {
			node_1[node_number].cost++;
		}
		else {
			node_number++;
			node_1[node_number].cost = 1;
		}
		sums += block_number[i];
		node_1[node_number].value = block_number[i];
	}
	bag_number = 0;
	for (int i = 0; i <= node_number; i++) {
		int k = 1;
		int temp_cost = node_1[i].cost;
		while (k < temp_cost) {
			bag_number++;
			node_2[bag_number].cost = k;
			node_2[bag_number].value = k * node_1[i].value;
			temp_cost -= k;
			k = k * 2;
		}
		if (temp_cost != 0) {
			bag_number++;
			node_2[bag_number].cost = temp_cost;
			node_2[bag_number].value = temp_cost * node_1[i].value;
		}
	}
	for (int i = 1; i <= sums; i++) {
		vis[i] = INF;
	}
	vis[0] = 0;
	for (int i = 1; i <= bag_number; i++) {
		for (int j = sums; j >= node_2[i].value; j--) {
			if (vis[j - node_2[i].value] + node_2[i].cost <= vis[j]) {
				vis[j] = vis[j - node_2[i].value] + node_2[i].cost;
			}
		}
	}
	int min_ans = MAX_NUMBER;
	for (int i = 0; i <= lucky_number && lucky[i] <= sums; i++) {
		if (vis[lucky[i]] != INF) {
			if (min_ans > vis[lucky[i]]) {
				min_ans = vis[lucky[i]];
			}
		}
	}
	if (min_ans == MAX_NUMBER) {
		printf("-1\n");
	}
	else {
		printf("%d\n", min_ans - 1);
	}
	return 0;
}