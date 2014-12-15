#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 20;

double pro[MAX_NUMBER][6];
double ans[6];
int gift_number[6];
int people;


int main() {
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &people);
        for (int i = 0; i < 5; i++) {
            scanf("%d", &gift_number[i]);
        }
        for (int i = 1; i <= people; i++) {
            for (int j = 0; j < 5; j++) {
                scanf("%lf", &pro[i][j]);
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < (1 << people); j++) {
                if (check(j)) {
                    
                }
            }
        }
    }
}
