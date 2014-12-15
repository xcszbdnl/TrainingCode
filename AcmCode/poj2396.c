#include <stdio.h>
#include <string.h>


#define MAX_POINT 250
#define INF 100000000
#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) < (b)) ? (a) : (b)

int flow[MAX_POINT][MAX_POINT], high[MAX_POINT][MAX_POINT], low[MAX_POINT][MAX_POINT], cap[MAX_POINT][MAX_POINT];
int row_sum[MAX_POINT], column_sum[MAX_POINT], queue[MAX_POINT], in[MAX_POINT], out[MAX_POINT], distance[MAX_POINT];
int row, column, source, destination, super_source, super_destination, point_number;


void init() {
    memset(flow, 0, sizeof(flow));
    memset(high, 0, sizeof(high));
    memset(low, 0, sizeof(low));
    memset(cap, 0, sizeof(cap));
    memset(row_sum, 0, sizeof(row_sum));
    memset(column_sum, 0, sizeof(column_sum));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(distance, 0, sizeof(distance));
}

void bfs(int s, int t, ) {
    int i;
    for (i = 0 ; i < point_number; i++) {
        distance[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
}
void solve(int s, int t, int num) {
    int i, j;
    super_source = num;
    super_destination = num + 1;
    for (i = 0; i < num; i++) {
        for (j = 0; j < num; j++) {
            cap[i][j] = high[i][j] - low[i][j];
            in[j] += low[i][j];
            out[i] += low[i][j];
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int test_case, i, j, constraint_number, row_1, column_1, symbol, number;
    scanf("%d", &test_case);
    while (test_case--) {
        init();
        scanf("%d%d", &row, &column);
        for (i = 1; i <= row; i++) {
            scanf("%d", &row_sum[i]);
        }
        for (i = 1; i <= column; i++) {
            scanf("%d", &column_sum[i]);
        }
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column; j++) {
                high[i][j + row] = INF;
            }
        }
        scanf("%d", &constraint_number);
        for (i = 1; i <= constraint_number; i++) {
            scanf("%d %d %c %d", &row_1, &column_1, &symbol, &number);
            if (row_1 == 0 && column_1 != 0) {
                if (symbol == '=') {
                    for (i = 1; i <= row; i++) {
                        low[i][column_1 + row] = high[i][column_1 + row] = number;
                    }
                }
                else if (symbol == '>') {
                    for (i = 1; i <= row; i++) {
                        low[i][column_1 + row] = max(low[i][column_1 + row], number + 1);
                    }
                }
                else if (symbol == '<') {
                    for (i = 1; i <= row; i++) {
                        high[i][column_1 + row] = min(high[i][column_1 + row], number - 1);
                    }
                }
            }
            else if (row_1 != 0 && column_1 == 0) {
                if (symbol == '=') {
                    for (i = 1; i <= column; i++) {
                        low[row_1][i + row] = high[row_1][i + row] = number;
                    }
                }
                else if (symbol == '>') {
                    for (i = 1; i <= column; i++) {
                        low[row_1][i + row] = max(low[row_1][i + row], number + 1);
                    }
                }
                else if (symbol == '<') {
                    for (i = 1; i <= column; i++) {
                        high[row_1][i + row] = min(high[row_1][i + row], number - 1);
                    }
                }
            }
            else {
                if (symbol == '=') {
                    low[row_1][column_1 + row] = high[row_1][column_1 + row] = number;
                }
                else if (symbol == '>') {
                    low[row_1][column_1 + row] = max(low[row_1][column_1 + row], number + 1);
                }
                else {
                    high[row_1][column_1 + row] = min(high[row_1][column_1 + row], number - 1);
                }
            }
        }
        for (i = 1; i <= row; i++) {
            low[source][i] = high[source][i] = row_sum[i];
        }
        for (i = 1; i <= column; i++) {
            low[i + row][destination] = high[i + row][destination] = column_sum[i];
        }
        source  = 0;
        destination = row + column + 1;
        solve(source, destination, destination + 1);
    }
}
