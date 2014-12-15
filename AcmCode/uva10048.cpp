#include <cstdio>
#include <string.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 105;
const int INF = 10000000;
int max_dist[MAX_NUMBER][MAX_NUMBER];
int point_number, edge_number, query_number;

void floyd() {
	for (int k = 1; k <= point_number; k++) {
		for (int i = 1; i <= point_number; i++) {
			for (int j = 1; j <= point_number; j++) {
				max_dist[i][j] = min(max_dist[i][j], max(max_dist[i][k], max_dist[k][j]));
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
			max_dist[i][i] = 0;
			for (int j = i + 1; j <= point_number; j++) {
				max_dist[i][j] = max_dist[j][i] = INF;
			}
		}
		for (int i = 1; i <= edge_number; i++) {
			int start, end, value;
			scanf("%d%d%d", &start, &end, &value);
			max_dist[start][end] = max_dist[end][start] = value;

		}
		floyd();
		printf("Case #%d\n", case_number);
		case_number++;
		for (int i = 1; i <= query_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			if (max_dist[start][end] == INF) {
				printf("no path\n");
			}
			else {
				printf("%d\n", max_dist[start][end]);
			}
		}
		first = 0;
	}
	return 0;
}