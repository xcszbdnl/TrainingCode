#include <cstdio>
#include <string.h>
#include <vector>

const int MAX_NUMBER = 21;
const int INF = 1000000;
int maps[MAX_NUMBER][MAX_NUMBER];
int edge_number;

void floyd() {
	for (int k = 1; k < MAX_NUMBER; k++) {
		for (int i = 1; i < MAX_NUMBER; i++) {
			for (int j = 1; j < MAX_NUMBER; j++) {
				if (maps[i][j] > maps[i][k] + maps[k][j]) {
					maps[i][j] = maps[i][k] + maps[k][j];
				}
			}
		}
	}
}
int main() {
	int case_number = 1;
	int first = 1;
	while (scanf("%d", &edge_number) != EOF) {
		for (int i = 1; i < MAX_NUMBER; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j < MAX_NUMBER; j++) {
				maps[i][j] = maps[j][i] = INF;
			}
		}
		for (int i = 1; i <= edge_number; i++) {
			int end;
			scanf("%d", &end);
			maps[1][end] = maps[end][1] = 1;
		}
		for (int i = 2; i <= 19; i++) {
			scanf("%d", &edge_number);
			for (int j = 1; j <= edge_number; j++) {
				int end;
				scanf("%d", &end);
				maps[i][end] = maps[end][i] = 1;
			}
		}
		floyd();
		int pair;
		printf("Test Set #%d\n", case_number);
		case_number++;
		scanf("%d", &pair);
		for (int i = 1; i <= pair; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			printf("%2d to %2d: %d\n", start, end, maps[start][end]);
		}
		printf("\n");
	}
	return 0;
}