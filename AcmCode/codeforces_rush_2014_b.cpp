#include <cstdio>
#include <cstring>

const int maxn = 2007;

char maps[maxn][maxn];
int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char step_name[] = "DURL";
int n, m, k;

int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n ;i++) {
        scanf("%s", maps[i]);
    }
    for (int i = 0; i < m; i++) {
        int ans = 0;
        for (int j = 1; j < n; j++) {
            int cnt_x = j;
            int cnt_y = i;
            for (int k = 0; k < 4; k++) {
                int next_x = cnt_x + j * steps[k][0];
                int next_y = cnt_y + j * steps[k][1];
                if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m) {
                    if (maps[next_x][next_y] == step_name[k]) {
                        ans++;
                    }
                }
            }
        }
        printf("%d ", ans);
    }
    printf("\n");
}
