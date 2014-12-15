#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 505


int map[MAX_NUMBER][MAX_NUMBER];
int state[MAX_NUMBER];
int previous[MAX_NUMBER];
int n, k;

int find(int start) {
    int i;
    for (i = 1; i <= n; i++) {
        if (map[start][i] && !state[i]) {
            state[i] = 1;
            if (!previous[i] || find(previous[i])) {
                previous[i] = start;
                return 1;
            }
        }
    }
    return 0;
}


int main() {

    int i;
    int row, column, ans = 0;
    scanf("%d%d", &n, &k);
    for (i = 0; i < k; i++) {
        scanf("%d%d", &row, &column);
        map[row][column] = 1;
                               
    }
    for (i = 1; i <= n; i++) {
        memset(state, 0, sizeof(state));
        if (find(i)) {
            ans++;
        }
    }
    printf("%d\n", ans);
}
