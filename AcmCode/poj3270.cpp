#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_NUMBER = 10007;
vector<int> cycle[MAX_NUMBER];
int vis[MAX_NUMBER], input[MAX_NUMBER], temp[MAX_NUMBER];
int ans, n;

int search(int number) {
    int low = 1;
    int high = n;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (temp[mid] == number) {
            return mid;
        }
        else if (temp[mid] > number) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1;
}
int main() {

    while (scanf("%d", &n) != EOF) {
        int k = 0;
        memset(vis, 0, sizeof(vis));
        ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &input[i]);
            temp[i] = input[i];
        }
        sort(temp + 1, temp + 1 + n);
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                int cnt_loc = i;
                cycle[k].clear();
                cycle[k].push_back(i);
                vis[i] = 1;
                while (1) {
                    int next_number = search(input[cnt_loc]);
                    if (vis[next_number]) {
                        k++;
                        break;
                    }
                    cycle[k].push_back(next_number);
                    vis[next_number] = 1;
                    cnt_loc = next_number;
                }
            }
        }
        for (int i = 0; i < k; i++) {
            if (cycle[i].size() != 1) {
                int min_number = temp[cycle[i][0]];
                int sums = 0;
                for (int j = 0; j < cycle[i].size(); j++) {
                    sums += temp[cycle[i][j]];
                    if (temp[cycle[i][j]] < min_number) {
                        min_number = temp[cycle[i][j]];
                    }
                }
                int n = cycle[i].size();
                if ((n - 3) * min_number < (n + 1) * temp[1]) {
                    ans = ans + (n - 1) * min_number + sums - min_number;
                }
                else {
                    ans = ans + (n + 1) * temp[1] + sums + min_number;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
