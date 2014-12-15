#include <cstdio>
#include <cstring>
#include <vector>

const int MAX_NUMBER = 2007;
using namespace std;

struct TwoSat {
    int n;
    vector<int> edge[MAX_NUMBER * 2];
    vector<int> mark[MAX_NUMBER * 2];
    int s[MAX_NUMBER * 2], c;

    bool dfs(int cnt_point) {
        if (mark[cnt_point ^ 1]) {
            return false;
        }
        if (mark[cnt_point]) {
            return true;
        }
        mark[cnt_point] = true;
        s[c++] = cnt_point;
        for (int i = 0; i < edge[cnt_point].size(); i++) {
            if (!dfs(edge[cnt_point][i])) {
                return false;
            }
        }
        return true;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i < 2 * n; i++) {
            edge[i].clear();
        }
        memset(mark, 0, sizeof(mark));
    }

    void add_clause(int x, int xval, int y, int yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        edge[x ^ 1].push_back(y);
        edge[y ^ 1].push_back(x);
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (!mark[i] && !mark[i ^ 1]) {
                if (!dfs(i)) {
                    while (c > 0) {
                        mark[s[--c]] = false;
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

struct TwoSat solver;

int main() {
    
}
