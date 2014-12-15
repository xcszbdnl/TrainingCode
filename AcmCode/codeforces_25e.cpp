#include <cstdio>
#include <iostream>
#include <string.h>

const int MAX_NUMBER = 100005;
const int INF = 10000000;

char string_1[MAX_NUMBER];
char string_2[MAX_NUMBER];
char string_3[MAX_NUMBER];

int main() {
	scanf("%s%s%s", string_1, string_2, string_3);
	int length_1 = strlen(string_1);
	int length_2 = strlen(string_2);
	int length_3 = strlen(string_3);
	int ans = INF;
	int temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_1 && i < length_2; i++) {
		if (string_2[i] == string_1[length_1 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_2 && i < length_3; i++) {
		if (string_3[i] == string_2[length_2 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_1 && i < length_3; i++) {
		if (string_3[i] == string_1[length_1 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_2 && i < length_3; i++) {
		if (string_2[i] == string_3[length_3 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_1 && i < length_2; i++) {
		if (string_1[i] == string_2[length_2 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_1 && i < length_3; i++) {
		if (string_3[i] == string_1[length_1 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_3 && i < length_2; i++) {
		if (string_3[i] == string_2[length_2 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_1 && i < length_3; i++) {
		if (string_1[i] == string_3[length_3 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_3 && i < length_2; i++) {
		if (string_2[i] == string_3[length_3 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_1 && i < length_2; i++) {
		if (string_1[i] == string_2[length_2 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	temp = length_1 + length_2 + length_3;
	for (int i = 0; i < length_3 && i < length_1; i++) {
		if (string_1[i] == string_3[length_3 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < length_1 && i < length_2; i++) {
		if (string_2[i] == string_1[length_1 - i - 1]) {
			temp--;
		}
		else {
			break;
		}
	}
	if (temp < ans) {
		ans = temp;
	}
	printf("%d\n", ans);
	return 0;
}