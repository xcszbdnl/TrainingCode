#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
const int maxn = 1008;

int vis[maxn];
int prime[maxn], prime_num;
int n;
vector<int> ans;
map<int, int> maps;
void getPrime() {
  memset(vis, 0, sizeof(vis));
  for (int i = 2; i <= sqrt(maxn + 0.5); i++) {
    if (!vis[i]) {
      for (int j = i + i; j < maxn; j += i) {
        vis[j] = 1;
      }
    }
  }
  prime_num = 0;
  for (int i = 2; i < maxn; i++) {
    if (!vis[i]) {
      prime[++prime_num] = i;
    }
  }
}
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  getPrime();
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ans.push_back(i);
      continue;
    }
    int k = i;
    for (int j = 1; j <= prime_num; j++) {
      if (k % prime[j] == 0) {
        int cnt_num = 0;
        int temp = 1;
        while (k % prime[j] == 0) {
          cnt_num++;
          k /= prime[j];
          temp *= prime[j];
        }
        if (cnt_num > 1 && !maps[temp]) {
          maps[temp] = 1;
          ans.push_back(temp);
        }
      }
    }
  }
  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  return 0;
}
