#include <cstdio>
#include <string.h>


double dp[10][20];
int vis[10][20];

char name[20][20];

int pro[20][20];

void search(int n, int people) {
	if (vis[n][people]) {
		return ;
	}
	vis[n][people] = 1;
	if (n == 1) {
		dp[n][people] = pro[people][people ^ 1] * 1.0 / 100;
		return ;
	}
	if (n == 4) {
		search(n - 1, people);
		if (people > 8) {
			for (int i = 0; i < 8; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		else if (people < 8) {
			for (int i = 8; i < 16; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		return ;
	}
	if (n == 3) {
		search(n - 1, people);
		if (people < 4) {
			for (int i = 4; i < 8; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		else if (people < 8) {
			for (int i = 0; i < 4; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		else if (people < 12) {
			for (int i = 12; i < 15; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		else {
			for (int i = 8; i < 12; i++) {
				search(n - 1, i);
				dp[n][people] = dp[n][people] + pro[people][i] * 1.0 / 100 * dp[n - 1][i] * dp[n - 1][people];
			}
		}
		return ;
	}
	if (n == 2) {
		search(n - 1, people);
		if (people < 4) {
			if (people >= 2) {
				search(n - 1, 0);
				search(n - 1, 1);
				dp[n][people] = dp[n][people] + pro[people][0] * 1.0 / 100 * dp[n - 1][0] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][1] * 1.0 / 100* dp[n - 1][1] * dp[n - 1][people];
			}
			else {
				search(n - 1, 2);
				search(n - 1, 3);
				dp[n][people] = dp[n][people] + pro[people][2] * 1.0 / 100* dp[n - 1][2] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][3] * 1.0 / 100* dp[n - 1][3] * dp[n - 1][people];
			}
		}
		else if (people < 8) {
			if (people >= 6) {
				search(n - 1, 4);
				search(n - 1, 5);
				dp[n][people] = dp[n][people] + pro[people][4] * 1.0 / 100 * dp[n - 1][4] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][5] * 1.0 / 100 * dp[n - 1][5] * dp[n - 1][people];
			}
			else {
				search(n - 1, 6);
				search(n - 1, 7);
				dp[n][people] = dp[n][people] + pro[people][6] * 1.0 / 100 * dp[n - 1][6] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][7] * 1.0 / 100 * dp[n - 1][7] * dp[n - 1][people];
			}

		}
		else if (people < 12) {
			if (people >= 10) {
				search(n - 1, 8);
				search(n - 1, 9);
				dp[n][people] = dp[n][people] + pro[people][8] * 1.0 / 100 * dp[n - 1][8] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][9] * 1.0 / 100 * dp[n - 1][9] * dp[n - 1][people];
			}
			else {
				search(n - 1, 10);
				search(n - 1, 11);
				dp[n][people] = dp[n][people] + pro[people][10] * 1.0 / 100 * dp[n - 1][10] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][11] * 1.0 / 100 * dp[n - 1][11] * dp[n - 1][people];
			}

		}
		else {
			if (people >= 14) {
				search(n - 1, 12);
				search(n - 1, 13);
				dp[n][people] = dp[n][people] + pro[people][12] * 1.0 / 100 * dp[n - 1][12] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][13] * 1.0 / 100 * dp[n - 1][13] * dp[n - 1][people];
			}
			else {
				search(n - 1, 14);
				search(n - 1, 15);
				dp[n][people] = dp[n][people] + pro[people][14] * 1.0 / 100 * dp[n - 1][14] * dp[n - 1][people];
				dp[n][people] = dp[n][people] + pro[people][15] * 1.0 / 100 * dp[n - 1][15] * dp[n - 1][people];
			}
		}
	}
}

int main() {
	memset(dp, 0, sizeof(dp));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < 16; i++) {
		scanf("%s", name[i]);
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			scanf("%d", &pro[i][j]);
		}
	}
	for (int i = 0; i < 16; i++) {
		search(4, i);
	}
	for (int i = 0; i < 16; i++) {
		printf("%-10s p=%.2lf%%\n", name[i], dp[4][i]);
	}
	return 0; 
}