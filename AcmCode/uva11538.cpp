#include <string.h>
#include <iostream>
#include <cstdio>

using namespace std;
long long ans;
long long row, column;

int main() {
	while (scanf("%lld%lld", &row, &column) != EOF) {
		if (!row && !column) {
			break;
		}
		if (row > column) {
			int temp = row;
			row = column;
			column = temp;
		}
		ans = row * column * (column - 1);
		ans += column * row * (row - 1);
		ans += 2 * row * (row - 1) * (3 * column - row - 1) / 3;
		cout << ans << endl;
	}
	return 0;
}