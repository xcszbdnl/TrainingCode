#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_NUMBER = 300007;
const int INF = 20007;

struct Point {
    int x, y;
};
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
struct TwoSat two_sat;
struct Point point[107];
int n;


bool cmp(struct Point a, struct Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    else {
        return a.x < b.x;
    }
}

int abs(int x) {
    return x > 0 ? x : -x;
}

bool judge(int x) {
    two_sat.init(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(point[j].x - point[i].x) < x && abs(point[j].y - point[i].y) < 2 * x) {
                if (abs(point[j].y - point[i].y) == x && point[j].x == point[i].x) {
                    continue;
                }
                else if (abs(point[j].y - point[i].y) >= x) {
                    two_sat.addClause(i, 1, j, 0);
                }
                else {
                    two_sat.addClause(i, 0, j, 0);
                    two_sat.addClause(i, 1, j, 1);
                    two_sat.addClause(i, 1, j, 0);                    
                }
            }
        }
    }
    if (two_sat.solver()) {
        return true;
    }
    return false;
}
int main() {
    freopen("input.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &point[i].x, &point[i].y);
        }
        sort(point, point + n, cmp);
        int low = 1;
        int high = 3;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (judge(mid)) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        printf("%d\n", high);
    }
    return 0;
}
