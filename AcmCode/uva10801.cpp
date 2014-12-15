#include <cstdio>
#include <string.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 105;
const int INF = 100000000;

int maps[MAX_NUMBER][MAX_NUMBER], distance[MAX_NUMBER], vis[MAX_NUMBER];
int time[MAX_NUMBER], floor[MAX_NUMBER], floor_number;
int elevator_number, target, max_floor;

void build(int cnt_elevator, int number) {
	for (int i = 0; i < number; i++) {
		for (int j = i + 1; j < number; j++) {
			int floor_1 = floor[i];
			int floor_2 = floor[j];
			int cnt_time = (floor_2 - floor_1) * time[cnt_elevator];
			if (maps[floor_1][floor_2] > cnt_time) {
				maps[floor_1][floor_2] = maps[floor_2][floor_1] = cnt_time;
			}
		}
	}
}

int dij() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= max_floor; i++) {
		distance[i] = INF;
	}
	distance[0] = 0;
	for (int i = 0; i <= max_floor; i++) {
		int min_ans = INF;
		int cnt_floor;
		for (int j = 0; j <= max_floor; j++) {
			if (!vis[j] && min_ans > distance[j]) {
				min_ans = distance[j];
				cnt_floor = j;
			}
		}
		if (min_ans == INF) {
			break;
		}
		vis[cnt_floor] = 1;
		for (int j = 0; j <= max_floor; j++) {
			if (!vis[j] && distance[j] > distance[cnt_floor] + maps[cnt_floor][j] + 60) {
				distance[j] = distance[cnt_floor] + maps[cnt_floor][j] + 60;
			}
		}
	}
	return distance[target];
}
int main() {
	while (scanf("%d%d", &elevator_number, &target) != EOF) {
		for (int i = 0; i < MAX_NUMBER; i++) {
			for (int j = i; j < MAX_NUMBER; j++) {
				maps[i][j] = maps[j][i] = INF;
			}
		}
		for (int i = 0; i < elevator_number; i++) {
			scanf("%d", &time[i]);
		}
		max_floor = 0;
		for (int i = 0; i < elevator_number; i++) {
			floor_number = 0;
			while (1) {
				int cnt_floor;
				char c;
				scanf("%d", &cnt_floor);
				max_floor = max(cnt_floor, max_floor);
				floor[floor_number++] = cnt_floor;
				c = getchar();
				if (c == '\n' || c == '\0') {
					break;
				}
			}
			build(i, floor_number);
		}
		int ans = dij();
		if (ans == INF) {
			printf("IMPOSSIBLE\n");
		}
		else {
			if (target != 0) {
				printf("%d\n", ans - 60);
			}
			else {
				printf("0\n");
			}
		}
	}
	return 0;
}