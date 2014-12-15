#include <cstdio>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 150005;

long long length, shift;
int vis[MAX_NUMBER];
char input[MAX_NUMBER];

long long getMin(string cnt_str) {
	int i, j, k, value;
	i = 0;
	j = 1;
	k = 0;
	while (i < length && j < length && k < length) {
		value = cnt_str[(i + k) % length] - cnt_str[(j + k) % length];
		if (!value) {
			k++;
		}
		else if (value < 0) {
			i = i + k + 1;
			k = 0;
		}
		else {
			j = j + k + 1;
			k = 0;
		}
		if (i == j) {
			j++;
		}
	}
	return i < j ? i : j;
}

int main() {
	scanf("%I64d%I64d%s", &length, &shift, input);
	shift = shift % length;
	string ans = "";
	int cnt = 0;
	for (int i = 0; i < length; i++) {
		if (!vis[i]) {
			string cnt_temp;
			int cnt_number = 0;
			cnt++;
			int cnt_loc = i;
			while (vis[cnt_loc] != cnt) {
				vis[cnt_loc] = cnt;
				cnt_temp += input[cnt_loc];
				cnt_loc = (cnt_loc + shift) % length;
				cnt_number++;
			}
			cnt_temp = cnt_temp + cnt_temp;
			cnt_loc = getMin(cnt_temp);
			string temp_ans = cnt_temp.substr(cnt_loc, length);
			temp_ans = temp_ans + cnt_temp.substr(0, cnt_loc);
			if (ans == "" || ans < temp_ans) {
				ans = temp_ans;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
