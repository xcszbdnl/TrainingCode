/*
ID: 123
PROG: ride
LANG: C++
*/

#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 100;


char str_1[MAX_NUMBER];
char str_2[MAX_NUMBER];


int main() {
    FILE *fin  = fopen("ri.in", "r");
    FILE *fout = fopen ("test.out", "w");
    int a, b;
    fscanf (fin, "%d %d", &a, &b);	/* the two input integers */
    fprintf (fout, "%d\n", a+b);
    scanf("%s%s", str_1, str_2);
    int ans_1, ans_2;
    ans_1 = 0;
    for (int i = 0; str_1[i]; i++) {
        int temp = str_1[i] - 'A' + 1;
        ans_1 = (ans_1 * temp) % 47;
    }
    ans_2 = 0;
    for (int i = 0; str_2[i]; i++) {
        int temp = str_2[i] - 'A' + 1;
        ans_2 = (ans_2 * temp) % 47;
    }
    if (ans_1 == ans_2) {
        printf("GO\n");
    }
    else {
        printf("STAY\n");
    }
    return 0;
}
