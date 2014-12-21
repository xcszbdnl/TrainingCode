#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;
const int maxn = 50;

map<string, int> maps;
int k;
struct T {
  int x[4];
};

T t[maxn];
int name_count, vis[maxn], dp[maxn][2], path[maxn][maxn];


int bitCount(int s) {
  int ret = 0;
  for (int i = 0; i < 20; i++) {
    if (s & (1 << i)) {
      ret++;
    }
  }
  return ret;
}
int main() {
  //freopen("../in.txt", "r", stdin);
  scanf("%d", &k);
  name_count = 0;
  for (int i = 0; i < k; i++) {
    for (int j = 1; j <= 3; j++) {
      string cnt;
      cin >> cnt;
      if (!maps.count(cnt)) {
        maps[cnt] = ++name_count;
      }
      t[i].x[j] = maps[cnt];
    }
  }
  memset(path, 0, sizeof(path));
  for (int i = 0; i < k; i++) {
    for (int j = i + 1; j < k; j++) {
      int flag = 0;
      for (int m = 1; m <= 3 && !flag; m++) {
        for (int s = 1; s <= 3 && !flag; s++) {
          if (t[i].x[m] == t[j].x[s]) {
            flag = 1;
            break;
          }
        }
      }
      if (flag) {
        path[i][j] = path[j][i] = 1;
      }
    }
  }
  memset(dp, 0, sizeof(dp));
  int ans = 0;
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i < (1 << k); i++) {
    int flag = 0;
    for (int j = 0; j < k && !flag; j++) {
      if (i & (1 << j)) {
        for (int s = 0; s < k && !flag; s++) {
          if (i & (1 << s) && path[j][s]) {
            flag = 1;
            break;
          }
        }
      }
    }
    if (!flag) {
      int temp = bitCount(i);
      ans = max(ans, temp);
    }
  }
  printf("%d\n", ans);
}
