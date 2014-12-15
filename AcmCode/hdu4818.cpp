#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int maxn = 107;
using namespace std;

double matrix[maxn][maxn];
int n, m, equ, var;
vector<int> path[maxn];
int main() {
    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(matrix, 0, sizeof(matrix));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d", &a, &b);
            path[a].push_back(b);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < path[i].size(); j++) {
                matrix[path[i][j]] = 1.0 / path[i].size();
            }
        }
        for (int i = 1; i <= n; i++) {
            matrix[i][i] = -1;
        }
    }
}
