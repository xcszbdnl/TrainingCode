#include <string.h>
#include <cstdio>

const int MAX_NUMBER = 105;

int maps[MAX_NUMBER][MAX_NUMBER];
char input[MAX_NUMBER];
int step[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int row, column;

int main() {
	int case_number = 1;
	int first = 1;
	while (scanf("%d%d", &row, &column) != EOF) {
		if (!row && !column) {
			break;
		}
		if (!first) {
			printf("\n");
		}
		memset(maps, 0, sizeof(maps));
		for (int i = 1; i <= row; i++) {
			scanf("%s", input);
			for (int j = 0; input[j]; j++) {
				if (input[j] == '*') {
					maps[i][j + 1] = -1;
					for (int k = 0; k < 8; k++) {
						int next_x = i + step[k][0];
						int next_y = j + 1 + step[k][1];
						if (maps[next_x][next_y] != -1) {
							maps[next_x][next_y]++;
						}
					}
				}
			}
		}
		printf("Field #%d:\n", case_number);
		case_number++;
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= column; j++) {
				if (maps[i][j] == -1) {
					printf("*");
				}
				else {
					printf("%d", maps[i][j]);
				}
			}
			printf("\n");
		}
		first = 0;
	}
	return 0;
}