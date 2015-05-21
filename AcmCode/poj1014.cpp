#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200007;

int dp[maxn];
int a[maxn], sums, v;


void completePack(int cost, int weight) {
  for (int i = cost; i  <= v; i++) {
    dp[i] = max(dp[i], dp[i - cost] + weight);
  }
}

void zeroPack(int cost, int weight) {
  for (int i = v; i >= cost; i--) {
    dp[i] = max(dp[i], dp[i - cost] + weight);
  }
}
void multiPack(int cost, int weight, int times) {
  if (cost * times >= v) {
    completePack(cost, weight);
  }
  else {
    int k = 1;
    while (k < times) {
      zeroPack(cost * k, weight * k);
      times -= k;
      k *= 2;
    }
    zeroPack(cost * times, weight * times);
  }
}


int main() {
  //freopen("in.txt", "r", stdin);
  int test_case = 1;
  int first = 1;
  while (scanf("%d", &a[1]) != EOF) {
    sums = a[1];
    for (int i = 2; i <= 6; i++) {
      scanf("%d", &a[i]);
      sums += a[i] * i;
    }
    if (sums == 0) {
      break;
    }
    if (!first) {
      printf("\n");
    }
    memset(dp, 0, sizeof(dp));
    printf("Collection #%d:\n", test_case++);
    if (sums % 2) {
      printf("Can't be divided.\n");
      continue;
    }
    v = sums / 2;
    for (int i = 1; i <= 6; i++) {
      multiPack(i, i, a[i]);
    }
    if (dp[sums / 2] != sums / 2) {
      printf("Can't be divided.\n");
    }
    else {
      printf("Can be divided.\n");
    }
    first = 0;
  }
  return 0;
}
