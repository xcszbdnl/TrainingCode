#include <string.h>
#include <cstdio>
#include <vector>

using namespace std;

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 50;

int maps[MAX_NUMBER][MAX_NUMBER];
vector<int> path;
int point_number, max_point, edge_number;
void floyd() {
	for (int k = 0; k <= max_point; k++) {
		for (int i = 0; i <= max_point; i++) {
			for (int j = 0; j <= max_point; j++) {
				maps[i][j] += maps[i][k] * maps[k][j];
			}
		}
	}
}

int main() {
	int city_number = 0;
	while (scanf("%d", &edge_number) != EOF) {
		memset(maps, 0, sizeof(maps));
		max_point = 0;
		path.clear();
		for (int i = 1; i <= edge_number; i++) {
			int start, end;
			scanf("%d%d", &start, &end);
			maps[start][end] = 1;
			max_point = max(max_point, start);
			max_point = max(max_point, end);
		}
		floyd();
		printf("matrix for city %d\n", city_number);
		city_number++;
		for (int i = 0; i <= max_point; i++) {
			if (maps[i][i] != 0) {
				path.push_back(i);
			}
		}
		for (int i = 0; i <= max_point; i++) {
			if (maps[i][i]) {
				for (int j = 0; j <= max_point; j++) {
					for (int k = 0; k <= max_point; k++) {
						if (maps[j][i] && maps[i][k]) {
							maps[j][k] = -1;
						}
					}
				}
			}
		}
		for (int i = 0; i <= max_point; i++) {
			for (int j = 0; j <= max_point; j++) {
				if (!j) {
					printf("%d", maps[i][j]);
				}
				else {
					printf(" %d", maps[i][j]);
				}
			}
			printf("\n");
		}
	}
	return 0;
}