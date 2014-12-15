#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;
const int maxn = 1007;


vector<int> divisor[maxn];
int f[maxn], g[maxn];

void getAllDivisor() {
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j <= sqrt(maxn * 1.0); j++) {
            if (i % j == 0) {
                if (j != i / j) {
                    divisor[i].push_back(j);
                    divisor[i].push_back(i / j);
                }
                else {
                    divisor[i].push_back(j);
                }
            }
        }
        sort(divisor[i].begin(), divisor[i].end());
    }
}



int main() {
    freopen("in.txt", "r", stdin);
    for (int i = 2; i < 2007; i++) {
        if (2007 % i == 0) {
            printf("fuck %d\n", i);
        }
    }
    int n;
    scanf("%d", &n);
    return 0;

}
