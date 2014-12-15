#include <cstdio>
#include <string.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 1000;
const int INF = 1000000000;

int distance[MAX_NUMBER], maps[MAX_NUMBER][MAX_NUMBER];
int queue[MAX_NUMBER * 100], vis[MAX_NUMBER], time[MAX_NUMBER], arrive_floor[10][MAX_NUMBER];
int floor[10];
int max_floor, elevator_number, target;
char input[MAX_NUMBER * MAX_NUMBER];

void spfa() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= max_floor; i++) {
		distance[i] = INF;
	}
	for (int i = 0; i < elevator_number; i++) {
		distance[i * 100] = 0;
	}
	int front = 0;
	int rear = 1;
	vis[0] = 1;
	queue[front] = 0;
	while (front < rear) {
		int cnt_point = queue[front];
		for (int i = 0; i <= max_floor; i++) {
			if (i != cnt_point && maps[cnt_point][i] != INF) {
				if (distance[i] > distance[cnt_point] + maps[cnt_point][i]) {
					distance[i] = distance[cnt_point] + maps[cnt_point][i];
					if (!vis[i]) {
						queue[rear] = i;
						rear++;
						vis[i] = 1;
					}
				}
			}
		}
		vis[cnt_point] = 0;
		front++;
	}
}

int main() {
	while (scanf("%d%d", &elevator_number, &target) != EOF) {
		memset(floor, 0, sizeof(floor));
		for (int i = 0; i < MAX_NUMBER; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j < MAX_NUMBER; j++) {
				maps[i][j] = maps[j][i] = INF;
			}
		}
		for (int i = 0; i < elevator_number; i++) {
			scanf("%d", &time[i]);
		}
		max_floor = 0;
		getchar();
		for (int i = 0; i < elevator_number; i++) {
			gets(input);
			int length = strlen(input);
			input[length] = ' ';
			input[length + 1] = '\0';
			int number = 0;
			int floor_number = 0;
			for (int j = 0; input[j]; j++) {
				if (input[j] == ' ') {
					arrive_floor[i][floor_number++] = number;
					max_floor = max(max_floor, number);
					number = 0;
				}
				else {
					number = number * 10 + input[j] - '0';
				}
			}
			for (int j = 0; j < floor_number; j++) {
				for (int k = j + 1; k < floor_number; k++) {
					int floor_1 = arrive_floor[i][k] + 100 * i;
					int floor_2 = arrive_floor[i][j] + 100 * i;
					int cnt_time = (floor_1 - floor_2) * time[i];
					if (maps[floor_1][floor_2] > cnt_time) {
						maps[floor_1][floor_2] = maps[floor_2][floor_1] = cnt_time;
					}
				}
			}
			floor[i] = floor_number;
		}
		max_floor = max_floor + elevator_number * 100;
		for (int i = 0; i < elevator_number; i++) {
			for (int j = i + 1; j < elevator_number; j++) {
				for (int k = 0; k < floor[i]; k++) {
					for (int s = 0; s < floor[j]; s++) {
						if (arrive_floor[i][k] == arrive_floor[j][s]) {
							int floor_1 = arrive_floor[i][k] + 100 * i;
							int floor_2 = arrive_floor[j][s] + 100 * j;
							maps[floor_1][floor_2] = maps[floor_2][floor_1] = 60;
						}
						else if (arrive_floor[j][s] > arrive_floor[i][k]) {
							break;
						}
					}
				}
			}
		}
		spfa();
		int min_ans = INF;
		for (int i = 0; i < elevator_number; i++) {
			if (distance[i * 100 + target] < min_ans) {
				min_ans = distance[i * 100 + target];
			}
		}
		if (min_ans == INF) {
			printf("IMPOSSIBLE\n");
		}
		else {
			printf("%d\n", min_ans);
		}
	}
	return 0;
}