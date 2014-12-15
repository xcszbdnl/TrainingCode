#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 207;

int input[MAX_NUMBER], vis[MAX_NUMBER];
char message[MAX_NUMBER], ans[MAX_NUMBER];
vector<int> cycle[MAX_NUMBER];
int n, times, cycle_number;

void getCycle() {
    memset(vis, 0, sizeof(vis));
    cycle_number = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int next_number = i;
            cycle[cycle_number].push_back(i);
            vis[i] = 1;
            while (1) {
                next_number = input[next_number];
                if (vis[next_number]) {
                    cycle_number++;
                    break;
                }
                cycle[cycle_number].push_back(next_number);
                vis[next_number] = 1;
            }
        }
    }
}
int main() {

    int first = 1;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }
        cycle[0].clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &input[i]);
            cycle[i].clear();
        }
        getCycle();
        while (scanf("%d", &times) != EOF) {
            if (times == 0) {
                break;
            }
            getchar();
            gets(message);
            int length = strlen(message);
            for (int i = length; i < n; i++) {
                message[i] = ' ';
            }
            message[n] = '\0';
            length = strlen(message);
            //puts(message);
            ans[length] = '\0';
            for (int i = 0; i < cycle_number; i++) {
                int cycle_length = cycle[i].size();
                int k_times = times % cycle_length;
                for (int j = 0; j < cycle[i].size(); j++) {
                    //printf("%d:%d ", i, cycle[i][j]);
                    int cnt = cycle[i][(j + k_times) % cycle_length] - 1;
                    //printf("cnt:%d loc:%d ", cnt, (j + k_times) % cycle_length);
                    ans[cnt] = message[cycle[i][j] - 1];
                }
            }
            printf("%s\n", ans);
        }
        printf("\n");
    }
    return 0;
}
