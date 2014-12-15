#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>


using namespace std;
const int MAX_NUMBER = 100;

struct Chess {
    int type;
    int row;
    int column;
};

struct Chess white_chess[MAX_NUMBER];
struct Chess black_chess[MAX_NUMBER];
char number_chess[5] = {'K', 'Q', 'R', 'B', 'N'};

bool cmp1(struct Chess a, struct Chess b) {
    if (a.type != b.type) {
        return a.type < b.type;
    }
    else if (a.row != b.row) {
        return a.row < b.row;
    }
    else {
        return a.column < b.column;
    }
}

bool cmp2(struct Chess a, struct Chess b) {
    if (a.type != b.type) {
        return a.type < b.type;
    }
    else if (a.row != b.row) {
        return a.row > b.row;
    }
    else {
        return a.column < b.column;
    }
}

int main() {

    int i, j;
    char input_line[MAX_NUMBER];
    int lenth, black_chess_number, white_chess_number;
    black_chess_number = white_chess_number = 0;
    for (i = 8; i >= 1; i--) {
        scanf("%s", input_line);
        scanf("%s", input_line);
        lenth = strlen(input_line);
        for (j = 0; j < lenth; j++) {
            if (input_line[j] >= 'a' && input_line[j] <= 'z') {
                switch(input_line[j]) {
                case 'k':
                    black_chess[black_chess_number].type = 0;
                    break;
                case 'q':
                    black_chess[black_chess_number].type = 1;
                    break;
                case 'r':
                    black_chess[black_chess_number].type = 2;
                    break;
                case 'b':
                    black_chess[black_chess_number].type = 3;
                    break;
                case 'n':
                    black_chess[black_chess_number].type = 4;
                    break;
                case 'p':
                    black_chess[black_chess_number].type = 5;
                    break;
                }
                black_chess[black_chess_number].row = i;
                black_chess[black_chess_number].column = (j / 4);
                black_chess_number++;
            }
            else if (input_line[j] >= 'A' && input_line[j] <= 'Z') {
                switch(input_line[j]) {
                case 'K':
                    white_chess[white_chess_number].type = 0;
                    break;
                case 'Q':
                    white_chess[white_chess_number].type = 1;
                    break;
                case 'R':
                    white_chess[white_chess_number].type = 2;
                    break;
                case 'B':
                    white_chess[white_chess_number].type = 3;
                    break;
                case 'N':
                    white_chess[white_chess_number].type = 4;
                    break;
                case 'P':
                    white_chess[white_chess_number].type = 5;
                    break;
                }
                white_chess[white_chess_number].row = i;
                white_chess[white_chess_number].column = (j / 4);
                white_chess_number++;
            }
        }
    }
    sort(white_chess, white_chess + white_chess_number, cmp1);
    sort(black_chess, black_chess + black_chess_number, cmp2);
    printf("White: ");
    for (i = 0; i < white_chess_number; i++) {
        if (i) {
            printf(",");
        }
        if (white_chess[i].type != 5) {
            printf("%c%c%d", number_chess[white_chess[i].type], white_chess[i].column + 'a', white_chess[i].row);
        }
        else {
            printf("%c%d", white_chess[i].column + 'a', white_chess[i].row);
        }
    }
    printf("\nBlack: ");
    for (i = 0; i < black_chess_number; i++) {
        if (i) {
            printf(",");
        }
        if (black_chess[i].type != 5) {
            printf("%c%c%d", number_chess[black_chess[i].type], black_chess[i].column + 'a', black_chess[i].row);
        }
        else {
            printf("%c%d", black_chess[i].column + 'a', black_chess[i].row);
        }
    }
    printf("\n");
    return 0;
}

