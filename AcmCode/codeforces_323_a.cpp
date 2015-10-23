#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 507;
long long maps[maxn][maxn];
long long value[maxn];
long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  freopen("in.txt", "r", stdin);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    value[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> maps[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      
    }
  }
}
