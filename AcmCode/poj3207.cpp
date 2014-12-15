#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 100007;

struct Edge {
    int left, right;
};

struct Edge edge[MAX_NUMBER];
struct TwoSat {
    int n, c;
    bool mark[MAX_NUMBER * 2];
    vector<int> path[MAX_NUMBER * 2];
    int s[MAX_NUMBER * 2];

    bool dfs(int cnt_point) {
        if (mark[cnt_point ^ 1]) {
            return false;
        }
        if (mark[cnt_point]) {
            return true;
        }
        s[++c] = cnt_point;
        mark[cnt_point] = true;
        for (int i = 0; i < path[cnt_point].size(); i++) {
            if (!dfs(path[cnt_point][i])) {
                return false;
            }
        }
        return true;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i < 2 * n; i++) {
            path[i].clear();
        }
        memset(mark, 0, sizeof(mark));
    }
    void addClause(int x, int xval, int y, int yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        path[x ^ 1].push_back(y);
        path[y ^ 1].push_back(x);
    }
    bool solver() {
        for (int i = 0; i < 2 * n; i += 2) {
            if (!mark[i] && !mark[i + 1]) {
                c = 0;
                if (!dfs(i)) {
                    while(c > 0) {
                        mark[s[--c]] = 0;
                    }
                    if (!dfs(i + 1)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};


bool judgeCross(int i, int j) {
    if (edge[i].left > edge[j].left && edge[i].left < edge[j].right && edge[i].right > edge[j].right) {
        return 1;
    }
    if (edge[i].right > edge[j].left && edge[i].right < edge[j].right && edge[i].left < edge[j].left) {
        return 1;
    }
    return 0;
}
struct TwoSat two_sat;
int n, m;
int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
        }
        edge[i].left = x;
        edge[i].right = y;
    }
    two_sat.init(m);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (judgeCross(i, j)) {
                two_sat.addClause(i, 0, j, 0);
                two_sat.addClause(i, 1, j, 1);
            }
        }
    }
    if (two_sat.solver()) {
        printf("panda is telling the truth...\n");
    }
    else {
        printf("the evil panda is lying again\n");
    }
    return 0;
}
