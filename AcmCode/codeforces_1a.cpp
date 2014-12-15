#include <cstdio>
#include <iostream>

using namespace std;

int m,n,a;

int main() {
	scanf("%d%d%d", &m, &n, &a);
	long long row, column;
	if (n % a == 0) {
		row = n / a;
	}
	else {
		row = n / a + 1;
	}
	if (m % a == 0) {
		column = m / a;
	}
	else {
		column = m / a + 1;
	}
	long long ans = row * column;
	cout << ans << endl;
	return 0;
}