#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 100
#define MAX_LENTH 130
#define INF 100000

int king_move[][2] = {-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
int knights_move[][2] = {-1,-2,-2,-1,-2,1,-1,2,1,-2,2,-1,2,1,1,2};

int king_map[MAX_NUMBER][MAX_NUMBER];
int knights_map[MAX_NUMBER][MAX_NUMBER];


void init() {
    int i, j;
    int row, column, next_row, next_column, location;
    for (i = 0; i < MAX_NUMBER; i++) {
        for (j = 0; j < MAX_NUMBER; j++) {
            king_map[i][j] = knights_map[i][j] = INF;
            if (i == j) {
                king_map[i][j] = knights_map[i][j] = 0;
            }
        }
    }
    for (i = 0; i < 64; i++) {
        row = i / 8;
        column = i % 8;
        for (j = 0; j < 8; j++) {
            next_row = row + king_move[j][0];
            next_column = column + king_move[j][1];
            location = next_row * 8 + next_column;
            if ((next_row < 8 && next_row >= 0) && (next_column < 8 && next_column >= 0)) {
                king_map[i][location] = 1;
            }
            next_row = row + knights_move[j][0];
            next_column = column + knights_move[j][1];
            location = next_row * 8 + next_column;
            if ((next_row < 8 && next_row >= 0) && (next_column < 8 && next_column >= 0)) {
                knights_map[i][location] = 1;
            }
        }
    }
}

void floyd() {
    int i, j, k;
    for (k = 0; k < MAX_NUMBER; k++) {
        for (i = 0; i < MAX_NUMBER; i++) {
            for (j = 0; j < MAX_NUMBER; j++) {
                if (king_map[i][j] > king_map[i][k] + king_map[k][j]) {
                    king_map[i][j] = king_map[i][k] + king_map[k][j];
                }
                if (knights_map[i][j] > knights_map[i][k] + knights_map[k][j]) {
                    knights_map[i][j] = knights_map[i][k] + knights_map[k][j];
                }
            }
        }
    }
}

int main() {

    char board[MAX_LENTH];
    int locations[MAX_NUMBER];
    int i, j, lenth, chess_number, final_location, mid_location, min_step, sum_step;
    init();
    floyd();
    scanf("%s", board);
    lenth = strlen(board);
    if (lenth == 2) {
        printf("0\n");
        return 0;
    }
    else {
        chess_number = 0;
        for (i = 0; board[i]; i += 2) {
            locations[chess_number++] = (board[i] - 'A') + (board[i + 1] - '1') * 8;
        }
        min_step = INF;
        for (final_location = 0; final_location < MAX_NUMBER; final_location++) {
            for (mid_location = 0; mid_location < MAX_NUMBER; mid_location++) {
                for (i = 1; i < chess_number; i++) {
                    sum_step = 0;
                    for (j = 1; j < chess_number; j++) {
                        sum_step += knights_map[locations[j]][final_location];
                    }
                    sum_step += king_map[locations[0]][mid_location];
                    sum_step += knights_map[locations[i]][mid_location] + knights_map[mid_location][final_location];
                    sum_step -= knights_map[locations[i]][final_location];
                    if (sum_step < min_step) {
                        min_step = sum_step;
                    }
                }
            }
        }
        printf("%d\n", min_step);
    }
    return 0;
}
