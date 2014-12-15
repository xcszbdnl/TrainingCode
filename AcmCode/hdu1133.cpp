#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 105;

long long chose[MAX_NUMBER];
long long com[MAX_NUMBER][MAX_NUMBER];
long long cata[MAX_NUMBER];

int m, n;

void getChose() {
	chose[0] = 1;
	for (int i = 1; i < MAX_NUMBER; i++) {
		chose[i] = chose[i - 1] * i;
	}
}

void getCom() {
	memset(com, 0, sizeof(com));
	for (int i = 0; i < MAX_NUMBER; i++) {
		for (int j = 0; j <= i; j++) {
			if (!j || i == j) {
				com[i][j] = 1;
			}
			else {
				com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
			}
		}
	}
}

void getCata() {
	cata[0] = 1;
	for (int i = 1; i < MAX_NUMBER; i++) {
		cata[i] = cata[i - 1] * (4 * i - 2) / (i + 1);
	}
}

int main() {
	getChose();
	getCom();
	getCata();
	int case_number = 1;
	while (scanf("%d%d", &m, &n) != EOF) {
		if (!m && !n) {
			break;
		}
		printf("Test #%d:\n", case_number);
		case_number++;
		if (m == n) {
			long long ans = cata[m] * chose[m] * chose[m];
			cout << ans << endl;
		}
		else if (m > n) {
			long long ans;
			if (n == 0) {
				ans = chose[m];
			}
			else {
				ans = cata[n] * chose[n] * chose[n] * com[m][n] * chose[m - n + 1];
			}
			cout << ans << endl;
		}
		else {
			long long ans;
			if (m == 0) {
				ans = chose[n];
			}
			else {
				ans = cata[m] * chose[m] * chose[m] * com[n][m] * chose[n - m];
			}
			cout << ans << endl;
		}
	}
	return 0;
}