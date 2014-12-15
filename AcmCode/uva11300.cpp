#include <cstdio>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 1000006;

unsigned long long value[MAX_NUMBER];
unsigned long long coin[MAX_NUMBER];
unsigned long long sums;
int total_people;

int main() {
	while (scanf("%d", &total_people) != EOF) {
		sums = 0;
		for (int i = 1; i <= total_people; i++) {
			cin >> value[i];
			sums += value[i];
		}
		unsigned long long average = sums / total_people;
		unsigned long long pre_sum = 0;
		coin[0] = 0;
		for (int i = 1; i < total_people; i++) {
			coin[i] =   pre_sum + value[i] - i * average;
			pre_sum += value[i];
		}
		sort(coin, coin + total_people);
		unsigned long long mid_number = coin[total_people / 2];
		for (int i = 0; i < total_people; i++) {
			if (mid_number > coin[i]) {
				sums = sums + mid_number - coin[i];
			}
			else {
				sums = sums + coin[i] - mid_number;
			}
		}
		cout << sums << endl;
	}
	return 0;
}