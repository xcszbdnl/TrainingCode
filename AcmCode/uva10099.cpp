#include <cstdio>
#include <string.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 105;
int maps[MAX_NUMBER][MAX_NUMBER];
int point_number, edge_number;

void floyd() {
	for (int k = 1; k <= point_number; k++) {
		for (int i = 1; i <= point_number; i++) {
			for (int j = 1; j <= point_number; j++) {
				maps[i][j] = max(maps[i][j], min(maps[i][k], maps[k][j]));
			}
		}
	}
}

int main() {
	int case_number = 1;
	int first = 1;
	while (scanf("%d%d", &point_number, &edge_number) != EOF) {
		memset(maps, 0, sizeof(maps));
		if (!point_number && !edge_number) {
			break;
		}
		for (int i = 1; i <= edge_number; i++) {
			int start, end, value;
			scanf("%d%d%d", &start, &end, &value);
			maps[start][end] = maps[end][start] = value;
		}
		floyd();
		int start, end, people;
		scanf("%d%d%d", &start, &end, &people);
		printf("Scenario #%d\n", case_number);
		case_number++;
		int ans = people / (maps[start][end] - 1);
		if (people % (maps[start][end] -1) != 0) {
			ans++;
		}
		printf("Minimum Number of Trips = %d\n", ans);
		printf("\n");
	}
	return 0;
}