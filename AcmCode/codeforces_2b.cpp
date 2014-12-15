#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

int matrix[MAX_NUMBER][MAX_NUMBER], init[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER], number[MAX_NUMBER][MAX_NUMBER], pre[MAX_NUMBER][MAX_NUMBER];
int row;
char ans[MAX_NUMBER];

void search(int cnt_x, int cnt_y) {
	if (dp[cnt_x][cnt_y] != -1) {
		return ;
	}
	if (cnt_x - 1 >= 1) {
		search(cnt_x - 1, cnt_y);
		dp[cnt_x][cnt_y] = dp[cnt_x - 1][cnt_y] + init[cnt_x][cnt_y];
		if ((matrix[cnt_x][cnt_y] * number[cnt_x - 1][cnt_y]) % 10 == 0) {
			number[cnt_x][cnt_y] = (matrix[cnt_x][cnt_y] * number[cnt_x - 1][cnt_y]) / 10;
			dp[cnt_x][cnt_y]++;
		}
		else {
			number[cnt_x][cnt_y] = (matrix[cnt_x][cnt_y] * number[cnt_x - 1][cnt_y]) % 10;
		}
		pre[cnt_x][cnt_y] = 1;
	}
	if (cnt_y - 1 >= 1) {
		search(cnt_x, cnt_y - 1);
		int temp = dp[cnt_x][cnt_y - 1] + init[cnt_x][cnt_y];
		if (matrix[cnt_x][cnt_y] * number[cnt_x][cnt_y - 1] == 10) {
			temp++;
		}
		if (temp < dp[cnt_x][cnt_y] || dp[cnt_x][cnt_y] == -1) {
			dp[cnt_x][cnt_y] = temp;
			if ((matrix[cnt_x][cnt_y] * number[cnt_x][cnt_y - 1]) % 10 == 0) {
				number[cnt_x][cnt_y] = (matrix[cnt_x][cnt_y] * number[cnt_x][cnt_y - 1]) / 10;
			}
			else {
				number[cnt_x][cnt_y] = (matrix[cnt_x][cnt_y] * number[cnt_x][cnt_y - 1]) % 10;
			}
			pre[cnt_x][cnt_y] = 0;
		}
	}
}

int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d", &row);
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= row; j++) {
			int x;
			scanf("%d", &x);
			while (x % 10 == 0) {
				init[i][j]++;
				x /= 10;
			}
			matrix[i][j] = x % 10;
		}
	}
	dp[1][1] = init[1][1];
	number[1][1] = matrix[1][1];
	search(row, row);
	printf("%d\n", dp[row][row]);
	ans[2 * row - 2] = '\0';
	int cnt_x = row;
	int cnt_y = row;
	for (int i = 2 * row - 3; i >= 0; i--) {
		if (pre[cnt_x][cnt_y] == 1) {
			cnt_x--;
			ans[i] = 'D';
		}
		else {
			cnt_y--;
			ans[i] = 'R';
		}
	}
	printf("%s", ans);
	return 0;
}