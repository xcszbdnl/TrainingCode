#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 3007;

struct TwoSat {
    int n, c;
    int mark[MAX_NUMBER * 2], s[MAX_NUMBER];
    vector<int> path[MAX_NUMBER * 2];

    void init(int n) {
        this->n = n;
        for (int i = 0; i <= 2 * n; i++) {
            path[i].clear();
        }
        memset(mark, 0, sizeof(mark));
    }
    void addClause(int x, int xval, int y, int yval) {
        x = 2 * x + xval;
        y = 2 * y + yval;
        path[x ^ 1].push_back(y);
        path[y ^ 1].push_back(x);
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i += 2) {
            if (!mark[i] && !mark[i ^ 1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c > 0) {
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

    bool dfs(int i) {
        if (mark[i ^ 1]) {
            return false;
        }
        if (mark[i]) {
            return true;
        }
        s[c++] = i;
        mark[i] = true;
        for (int j = 0; j < path[i].size(); j++) {
            int next_point = path[i][j];
            if (!dfs(next_point)) {
                return false;
            }
        }
        return true;
    }
};

const int INF = 100000007;
struct Plane {
    int time[3];
};


int n;
struct TwoSat two_sat;
struct Plane plane[MAX_NUMBER];

int abs(int x) {
    return x < 0 ? -x : x;
}
bool test(int number) {
    two_sat.init(n);
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < 2; a++) {
            for (int j = i + 1; j < n; j++) {
                for (int b = 0; b < 2; b++) {
                    if (abs(plane[i].time[a] - plane[j].time[b]) < number) {
                        two_sat.addClause(i, a ^ 1, j, b ^ 1);
                    }
                }
            }
        }
    }
    return two_sat.solve();
}
int main() {

    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &plane[i].time[0], &plane[i].time[1]);
        }
        int low = 1;
        int high = INF;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (test(mid)) {
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
