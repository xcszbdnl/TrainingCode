#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 1000006;

bool vis[MAX_NUMBER + 2];
int prim[MAX_NUMBER / 10];
double dp[MAX_NUMBER];
int prim_number;

void getAllPrim() {
	memset(vis, 0, sizeof(vis));
	int m = (int)sqrt(MAX_NUMBER + 1e-6);
	for (int i = 2; i <= m; i++) {
		if (!vis[i]) {
			for (int j = i * i; j <= MAX_NUMBER; j += i) {
				vis[j] = 1;
			}
		}
	}
	prim_number = 0;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		if (!vis[i]) {
			prim[++prim_number] = i;
		}
	}
}

void search(int cnt_number) {
	if (vis[cnt_number]) {
		return ;
	}
	int p = 0;
	int g = 0;
	double ans = 0;
	for (int i = 1; i <= prim_number && prim[i] <= cnt_number; i++) {
		p++;
		if (cnt_number % prim[i] == 0) {
			g++;
			search(cnt_number / prim[i]);
			ans = ans + dp[cnt_number / prim[i]];
		}
	}
	ans = (ans + p) / g;
	dp[cnt_number] = ans;
	vis[cnt_number] = 1;
}

int main() {
	int test_case;
	int case_number = 1;
	scanf("%d", &test_case);
	getAllPrim();
	memset(vis, 0, sizeof(vis));
	dp[1] = 0;
	vis[1] = 1;
	while (test_case--) {
		int number;
		scanf("%d", &number);
		if (vis[number]) {
			printf("Case %d: %.10lf\n", case_number, dp[number]);
		}
		else {
			search(number);
			printf("Case %d: %.10lf\n", case_number, dp[number]);
		}
		case_number++;
	}
	return 0;
}