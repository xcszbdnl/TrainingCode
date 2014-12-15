#include <cstdio>
#include <cstring>


const int MAX_NUMBER = 1000007;

int stack[MAX_NUMBER];
int top;
int dp[MAX_NUMBER];
char input[MAX_NUMBER];
void pop() {
    top--;
}
int getTop() {
    return stack[top];
}
int isEmpty() {
    return top == 0 ? 1 : 0;
}
void push(int number) {
    stack[++top] = number;
}

int main() {

    scanf("%s", input);
    int length = strlen(input);
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < length; i++) {
        if (input[i] == '(') {
            push(i);
        }
        else {
            if (isEmpty()) {
                dp[i] = -1;
            }
            else {
                dp[i] = getTop();
                pop();
                if (dp[dp[i] - 1] != -1) {
                    dp[i] = dp[dp[i] - 1];
                }
            }
        }
    }
    int flag = 0;
    int ans = 0;
    int ans_number = 0;
    for (int i = 0; i < length; i++) {
        if (dp[i] != -1) {
            if ((i - dp[i] + 1) > ans) {
                flag = 1;
                ans = i - dp[i] + 1;
                ans_number = 1;
            }
            else if ((i - dp[i] + 1) == ans) {
                ans_number++;
            }
        }
    }
    if (flag) {
        printf("%d %d\n", ans, ans_number);
    }
    else {
        printf("0 1\n");
    }
    return 0;
}
