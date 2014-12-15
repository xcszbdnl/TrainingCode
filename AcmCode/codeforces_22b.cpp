#include <cstdio>
#include <cstring>

#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 30;
const int INF = 1000007;


char maps[MAX_NUMBER][MAX_NUMBER];
int up[MAX_NUMBER][MAX_NUMBER];
int left[MAX_NUMBER][MAX_NUMBER];
int right[MAX_NUMBER][MAX_NUMBER];
int row, column;

int main() {

    scanf("%d%d", &row, &column);
    memset(maps, 0, sizeof(maps));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    for (int i = 1; i <= row; i++) {
        scanf("%s", maps[i] + 1);
    }
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= column; j++) {
            right[i][j] = INF;
        }
    }
    for (int i = 1; i <= row; i++) {
        int lo = 0;
        for (int j = 1; j <= column; j++) {
            if (maps[i][j] == '1') {
                lo = j;
                up[i][j] = 0;
                left[i][j] = 0;
            }
            else {
                up[i][j] = up[i - 1][j] + 1;
                left[i][j] = max(lo + 1, left[i - 1][j]);
            }
        }
        lo = column + 1;
        for (int j = column; j >= 1; j--) {
            if (maps[i][j] == '1') {
                lo = j;
                right[i][j] = INF;
            }
            else {
                right[i][j] = min(lo - 1, right[i - 1][j]);
            }
        }
    }
    int max_ans = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= column; j++) {
            if (maps[i][j] == '0') {
                int length = up[i][j];
                int width = right[i][j] - left[i][j] + 1;
                if ((length + width) * 2 > max_ans) {
                    max_ans = (length + width) * 2;
                }
            }
        }
    }
    printf("%d\n", max_ans);
    return 0;
}
