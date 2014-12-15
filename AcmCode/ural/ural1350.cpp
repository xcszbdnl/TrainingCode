#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 107;
map<string, int> maps;
vector<int> food[maxn];
int n, m, s_n;
string cnt_name;
int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i  = 1; i <= n; i++) {
        cin >> cnt_name;
        maps[cnt_name] = ++cnt;
    }
    scanf("%d", &s_n);
    int first_n;
    scanf("%d", &first_n);
    for (int i = 1; i <= first_n; i++) {
        cin >> cnt_name;
        food[1].push_back(maps[cnt_name]);
    }
    for (int i = 1; i <= s_n; i++) {
        int a;
        scanf("%d", &a);
        for (int j = 1; j <= a; j++) {
            cin >> cnt_name;
            food[i + 1].push_back(maps[cnt_name]);
        }
    }
    scanf("%d", &m);
    n = n - food[1].size();
    for (int i = 2; i <= s_n + 1; i++) {
        int temp = food[i].size();
        for (int j = 0; j < food[i].size(); j++) {
            int cnt = food[i][j];
            for (int k = 0; k < food[1].size(); k++) {
                if (cnt == food[1][k]) {
                    temp--;
                    break;
                }
            }
        }
        if (temp == 0) {
            printf("YES\n");
        }
        else if (n - m >= temp) {
            printf("MAYBE\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
