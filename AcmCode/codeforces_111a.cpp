#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 100020;

long long value[MAX_NUMBER];
long long n, x, y;

int main() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) {
		value[i] = 1;
	}
	value[n] = y - (n - 1);
	if ((value[n] >= 0) && (value[n] * value[n]) >= (x - (n - 1))) {
		for (int i = 1; i <= n; i++) {
			cout << value[i] << endl;
		}
	}
	else {
		cout << "-1" << endl;
	}
	return 0;
}