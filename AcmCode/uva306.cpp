#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 204;

int value[MAX_NUMBER], vis[MAX_NUMBER];
int length[MAX_NUMBER];
int n;
char input[MAX_NUMBER];
char ans[MAX_NUMBER];

int main() {

    int first = 0;
    while (scanf("%d", &n) != EOF) {
        if (!n) {
            break;
        }
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &value[i]);
        }
        int total = n;
        while (total) {
            int i = 1;
            while (vis[i]) {
                i++;
            }
            int begin = i;
            int cnt_length = 0;
            while (1) {
                cnt_length++;
                vis[i] = 1;
                i = value[i];
                if (i == begin) {
                    break;
                }
            }
            i = begin;
            while (1) {
                length[i] = cnt_length;
                i = value[i];
                if (i == begin) {
                    break;
                }
            }
            total -= cnt_length;
        }
        int k;
        while (scanf("%d", &k) != EOF) {
            if (!k) {
                break;
            }
            getchar();
            gets(input);
            if (strlen(input) != n) {
                for (int i = strlen(input); i < n; i++) {
                    input[i] = ' ';
                }
            }
            input[n] = '\0';
            for (int i = 0; i < n; i++) {
                int cnt_number = k % (length[i + 1]);
                int next = i + 1;
                for (int j = 1; j <= cnt_number; j++) {
                    next = value[next];
                }
                ans[next - 1] = input[i];
            }
            ans[n] = '\0';
            printf("%s\n", ans);
        }
        printf("\n");
        first = 1;
    }
    return 0;
}
