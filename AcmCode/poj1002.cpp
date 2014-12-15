#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_NUMBER = 100007;

struct Phone {
    int p;
    int times;
};
struct Phone phone[MAX_NUMBER];
string input[MAX_NUMBER];
int head[MAX_NUMBER], next[MAX_NUMBER];
int number, phone_number;

bool cmp(struct Phone a, struct Phone b) {
    return a.p < b.p;
}

char getDigit(char cnt_char) {
    if (cnt_char <= 'P') {
        return (cnt_char - 'A') / 3 + 2;
    }
    else {
        cnt_char--;
        return (cnt_char - 'A') / 3 + 2;
    }
}
int getPhone(string cnt_string) {
    int cnt_phone = 0;
    for (int i = 0; i < cnt_string.size(); i++) {
        int cnt_digit;
        if (cnt_string[i] >= '0' && cnt_string[i] <= '9') {
            cnt_digit = cnt_string[i] - '0';
        }
        else if (cnt_string[i] == '-') {
            continue;
        }
        else {
            cnt_digit = getDigit(cnt_string[i]);
        }
        cnt_phone = cnt_phone * 10 + cnt_digit;
    }
    return cnt_phone;
}

int hash(int cnt_phone) {
    return cnt_phone % MAX_NUMBER;
    
}
int hasPhone(int cnt_phone) {
    int hash_number = hash(cnt_phone);
    for (int first = head[hash_number]; first != -1; first = next[first]) {
        if (phone[first].p == cnt_phone) {
            return first;
        }
    }
    phone_number++;
    phone[phone_number].p = cnt_phone;
    phone[phone_number].times = 1;
    next[phone_number] = head[hash_number];
    head[hash_number] = phone_number;
    return -1;
}
int main() {

    scanf("%d", &number);
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    phone_number = 0;
    for (int i = 1; i <= number; i++) {
        cin >> input[i];
        int temp = getPhone(input[i]);
        int k = hasPhone(temp);
        if (k != -1) {
            phone[k].times++;
        }
    }
    sort(phone + 1, phone + 1 + phone_number, cmp);
    int flag = 0;
    for (int i = 1; i <= phone_number; i++) {
        if (phone[i].times < 2) {
            continue;
        }
        flag = 1;
        printf("%03d-%04d %d\n", phone[i].p / 10000, phone[i].p % 10000, phone[i].times);
    }
    if (!flag) {
        cout << "No duplicates." << endl;
    }
    return 0;
}
