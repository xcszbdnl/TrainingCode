#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;
const int maxn = 306;


int maps[maxn][maxn];
int n, a[maxn], vis[maxn], ans[maxn];
vector<int> num, loc;

void dfs(int cnt) {
  for (int i = 1; i <= n; i++) {
    if (maps[cnt][i] && !vis[i]) {
      num.push_back(a[i]);
      loc.push_back(i);
      vis[i] = 1;
      dfs(i);
    }
  }
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  memset(maps, 0, sizeof(maps));
  for (int i = 1; i <= n; i++) {
    char temp[300];
    scanf("%s", temp);
    for (int j = 0; j < n; j++) {
      if (temp[j] == '0') {
        maps[i][j + 1] = 0;
      }
      else {
        maps[i][j + 1] = 1; 
      }
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      loc.clear();
      num.clear();
      loc.push_back(i);
      num.push_back(a[i]);
      vis[i] = 1;
      dfs(i);
      sort(num.begin(), num.end());
      sort(loc.begin(), loc.end());
      for (int i = 0; i < num.size(); i++) {
        ans[loc[i]] = num[i];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
}

