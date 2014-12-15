#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1 << 20;
int n, r;
double buy_p[30];
double ai_b_p[30];
double ans[30];
double p_b;

bool check(int state) {
    int r_number = 0;
    for (int i = 0; i < n; i++) {
        if (state & (1 << i)) {
            r_number++;
        }
    }
    if (r_number == r) {
        return true;
    }
    else {
        return false;
    }
}

int main() {

    int case_number = 1;
    while (scanf("%d%d", &n, &r) != 0) {
        if (!n && !r) {
            break;
        }
        for (int i = 0; i < n; i++) {
            scanf("%lf", &buy_p[i]);
        }
        memset(ai_b_p, 0, sizeof(ai_b_p));
        p_b = 0;
        for (int i = 0; i < (1 << n); i++) {
            if (check(i)) {
                double temp_b = 1;
                for (int j = 0; j < n; j++) {
                    if (i & (1 << j)) {
                        temp_b *= buy_p[j];
                    }
                    else {
                        temp_b *= (1 - buy_p[j]);
                    }
                }
                for (int j = 0; j < n; j++) {
                    if (i & (1 << j)) {
                        ai_b_p[j] += temp_b;
                    }
                }
                p_b += temp_b;
            }
        }
        for (int i = 0; i < n; i++) {
            ans[i] = ai_b_p[i] / p_b;
        }
        printf("Case %d:\n", case_number);
        case_number++;
        for (int i = 0; i < n; i++) {
            printf("%.6lf\n", ans[i]);
        }
    }
    return 0;
}
