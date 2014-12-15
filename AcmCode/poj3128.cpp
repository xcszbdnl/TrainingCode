#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 30;

char input[MAX_NUMBER];
int number[MAX_NUMBER];
int vis[MAX_NUMBER];

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(vis, 0, sizeof(vis));
        memset(number, 0, sizeof(number));
        scanf("%s", input);
        for (int i = 0; i < strlen(input); i++) {
            int cycle_length = 1;
            vis[i] = 1;
            int cnt_number = i;
            while (1) {
                cnt_number = input[cnt_number] - 'A';
                if (vis[cnt_number]) {
                    break;
                }
                cycle_length++;
                vis[cnt_number] = 1;
            }
            number[cycle_length]++;
            //printf("%d ", cycle_length);
        }
        int flag = 0;
        for (int i = 2; i <= 26; i += 2) {
            if (number[i] % 2 == 1) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
        }
    }
    return 0;
}
