#include <iostream>
#include <string.h>
#include <cstdio>
#include <map>
#include <vector>

#define MAX_NUMBER 203
#define max(a,b) ((a) > (b)) ? (a) : (b)
using namespace std;

vector<int> tree[MAX_NUMBER];
int dp[MAX_NUMBER][2];
int point_number;

int search(int root, int invited) {
    if (dp[root][invited] != -1) {
        return dp[root][invited];
    }
    if (invited) {
        int sums = 1;
        for (int i = 0; i < tree[root].size(); i++) {
            int son = tree[root][i];
            sums += search(son, 0);
        }
        dp[root][invited] = sums;
        return sums;
    }
    else {
        int sums = 0;
        for (int i = 0; i < tree[root].size(); i++) {
            int son = tree[root][i];
            sums += max(search(son, 1), search(son, 0));
        }
        dp[root][invited] = sums;
        return sums;
    }
}

int check() {
    for (int i = 1; i <= point_number; i++) {
        if (dp[i][0] >= dp[i][1]) {
            for (int j = 0; j < tree[i].size(); j++) {
                int son = tree[i][j];
                if (dp[son][1] == dp[son][0]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}


int main() {

    while (scanf("%d", &point_number) != EOF) {
        if (point_number == 0) {
            break;
        }
        map<string, int> maps;
        maps.clear();
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= point_number; i++) {
            tree[i].clear();
        }
        string names;
        cin >> names;
        int number = 1;
        maps[names] = number++;
        for (int i = 1; i < point_number; i++) {
            string employee, boss;
            cin >> employee >> boss;
            if (!maps[employee]) {
                maps[employee] = number++;
            }
            if (!maps[boss]) {
                maps[boss] = number++;
            }
            tree[maps[boss]].push_back(maps[employee]);
        }
        for (int i = 1; i <= point_number; i++) {
            if (tree[i].size() == 0) {
                dp[i][0] = 0;
                dp[i][1] = 1;
            }
        }
        search(1, 0);
        search(1, 1);
        if (dp[1][1] == dp[1][0]) {
            cout << dp[1][0] << " No" << endl;
        }
        else {
            int ans = max(dp[1][1], dp[1][0]);
            cout << ans;
            if (check()) {
                cout << " Yes" << endl;
            }
            else {
                cout << " No" << endl;
            }
        }
    }
    return 0;
}
