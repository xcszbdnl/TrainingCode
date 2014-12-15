#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 15

char map[MAX_NUMBER][MAX_NUMBER];
int map_step[MAX_NUMBER][MAX_NUMBER];
int arrived_location[MAX_NUMBER][MAX_NUMBER];
int rows, columns, start_column;

int main() {

    int i, j, cnt_row, cnt_column, previous_step;
    char input_line[MAX_NUMBER];
    while (scanf("%d%d%d", &rows, &columns, &start_column) != EOF) {
        if (!rows && !columns && !start_column) {
            break;
        }
        memset(arrived_location, 0, sizeof(arrived_location));
        memset(map_step, 0, sizeof(map_step));
        for (i = 1; i <= rows; i++) {
            scanf("%s", input_line);
            for (j = 0; j < columns; j++) {
                map[i][j + 1] = input_line[j];
            }
        }
        cnt_row = 1, cnt_column = start_column;
        previous_step = 1;
        map_step[cnt_row][cnt_column] = previous_step;
        while (1) {
            arrived_location[cnt_row][cnt_column] = 1;
            switch(map[cnt_row][cnt_column]) {
            case 'N':
                cnt_row--;
                break;
            case 'E':
                cnt_column++;
                break;
            case 'S':
                cnt_row++;
                break;
            case 'W':
                cnt_column--;
                break;
            }
            if (cnt_row == 0 || cnt_row == rows + 1 || cnt_column == 0 || cnt_column == columns + 1) {
                printf("%d step(s) to exit\n", previous_step);
                break;
            }
            if (arrived_location[cnt_row][cnt_column] != 0) {
                printf("%d step(s) before a loop of %d step(s)\n", map_step[cnt_row][cnt_column] - 1, previous_step - map_step[cnt_row][cnt_column] + 1);
                break;
            }
            map_step[cnt_row][cnt_column] = previous_step + 1;
            previous_step = map_step[cnt_row][cnt_column];
        }
    }
}
