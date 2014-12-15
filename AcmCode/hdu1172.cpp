#include <cstdio>
#include <string.h>

struct Require {
	char number[5];
	int correct;
	int location;
};

const int MAX_NUMBER = 105;
struct Require require[MAX_NUMBER];
int require_number;

int check(int cnt_number) {
	char string_number[4];
	for (int i = 3; i >= 0; i--) {
		string_number[i] = cnt_number % 10 + '0';
		cnt_number /= 10;
	}
	int vis[4];
	int match[4];
	for (int i = 1; i <= require_number; i++) {
		int temp_correct = 0;
		int temp_location = 0;
		memset(vis, 0, sizeof(vis));
		memset(match, 0, sizeof(match));
		for (int j = 0; j < 4; j++) {
			if (string_number[j] == require[i].number[j]) {
				vis[j] = 1;
				match[j] = 1;
				temp_correct++;
				temp_location++;
			}
		}
		for (int j = 0; j < 4; j++) {
			if (!match[j]) {
				for (int k = 0; k < 4; k++) {
					if (!vis[k] && string_number[k] == require[i].number[j]) {
						vis[k] = 1;
						match[j] = 1;
						temp_correct++;
						break;
					}
				}
			}
		}
		if (temp_correct != require[i].correct || temp_location != require[i].location) {
			return 0;
		}
	}
	return 1;
}

int main() {
	while (scanf("%d", &require_number) != EOF) {
		if (!require_number) {
			break;
		}
		for (int i = 1; i <= require_number; i++) {
			scanf("%s%d%d", require[i].number, &require[i].correct, &require[i].location);
		}
		int ans = -1;
		for (int i = 1000; i <= 9999; i++) {
			if (check(i)) {
				if (ans != -1) {
					ans = -1;
					break;
				}
				else {
					ans = i;
				}
			}
		}
		if (ans == -1) {
			printf("Not sure\n");
		}
		else {
			printf("%d\n", ans);
		}
	}
	return 0;
}
