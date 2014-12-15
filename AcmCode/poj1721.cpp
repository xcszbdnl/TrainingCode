#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_NUMBER = 1007;

vector<int> cycle[MAX_NUMBER];
int value[MAX_NUMBER], ans[MAX_NUMBER], temp[MAX_NUMBER];
int cycle_number;
int s, n;

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &s) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &value[i]);
            cycle[i].clear();
        }
        while (s--) {
            ans[1] = 1;
            for (int i = 2; i <= n; i++) {
                ans[i] = value[ans[i - 1]];
                //printf("%d ", ans[i]);
            }
            temp[1] = 1;
            for (int i = 2; i <= n; i++) {
                if (i % 2 == 0) {
                    temp[i] = ans[i / 2 + (n + 1) / 2];
                }
                else {
                    temp[i] = ans[(i + 1) / 2];
                }
                //printf("%d ", temp[i]);
            }
            int cnt_number = 1;
            for (int i = 1; i < n; i++) {
                ans[cnt_number] = temp[i + 1];
                cnt_number = temp[i + 1];
            }
            ans[cnt_number] = 1;
            memcpy(value, ans, sizeof(ans));
        }
        for (int i = 1; i <= n; i++) {
            printf("%d\n", value[i]);
        }
    }
    return 0;
}
