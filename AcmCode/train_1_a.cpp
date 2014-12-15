#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1005;

int dp[MAX_NUMBER], input[MAX_NUMBER], increase[MAX_NUMBER];
int stack[MAX_NUMBER];
int number;

int main() {

    int max_number = 0;
    scanf("%d", &number);
    for (int i = 1; i <= number; i++) {
        scanf("%d", &input[i]);
    }
    int top = 0;
    stack[top] = -1;
    for (int i = 1; i <= number; i++) {
        if (input[i] > stack[top]) {
            stack[++top] = input[i];
        }
        else {
            int low = 1;
            int high = top;
            while (low <= high) {
                int mid = (low + high) >> 1;
                if (stack[mid] < input[i]) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            stack[low] = input[i];
        }
        increase[i] = top;
        if (max_number < increase[i]) {
            max_number = increase[i];
        }
    }
    printf("%d\n", max_number);
}

           

       
