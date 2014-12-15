#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 105;
const int INF = 10000000;

int maps[MAX_NUMBER][MAX_NUMBER];
int point_number, edge_number, query_number;

void floyd() {
	for (int k = 1; k <= point_number; k++) {
		for (int i = 1; i <= point_number; i++) {
			for (int j = 1; j <= point_number; j++) {
				if (k != i && k != j && i != j) {
					if (maps[i][j] < maps[i][k]) {
						maps[i][j] = maps[i][k];
					}
					if (maps[i][j] < maps[k][j]) {
						maps[i][j] = maps[k][j];
					}
				}
			}
		}
	}
}

int main() {
	int case_number = 1;
	int first = 1;
	while (scanf("%d%d%d", &point_number, &edge_number, &query_number) != EOF) {
		if (!point_number && !edge_number && !query_number) {
			break;
		}
		if (!first) {
			printf("\n");
		}
		for (int i = 1; i <= point_number; i++) {
			maps[i][i] = 0;
			for (int j = i + 1; j <= point_number; j++) {
				maps[i][j] = maps[j][i] = -1;
			}
		}
		for (int i = 1; i <= edge_number; i++) {
			int start, end, value;
			scanf("%d%d%d", &start, &end, &value);
			maps[start][end] = maps[end][start] = value; 
		}
		floyd();
		for (int i = 1; i <= query_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			if (maps[start][end] == -1) {
				printf("no path\n");
			}
			else {
				printf("%d\n", maps[start][end]);
			}
		}
		first = 0;
	}
	return 0;
}