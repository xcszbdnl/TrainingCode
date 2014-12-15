#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;

map<string, int> maps;

int main() {
//    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    while (n--) {
        string cnt;
        cin >> cnt;
        int flag = 0;
        if (!maps[cnt]) {
            maps[cnt] = 1;
            flag = 1;
        }
        else {
            maps[cnt]++;
        }
        if (flag) {
            cout << "OK" << endl;
        }
        else {
            char number[20];
            int temp = maps[cnt] - 1;
            int i = 0;
//            cout << temp << endl;
            while (temp) {
                number[i] = temp % 10 + '0';
                temp /= 10;
                i++;
            }
            number[i] = '\0';
//            cout << number << endl;
            int len = strlen(number);
            int j;
            for (i = 0, j = len - 1; i <= j; i++, j--) {
                char temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
            string index(number);
            string ans = cnt + index;
            cout << ans << endl;
        }
    }
    return 0;
}

