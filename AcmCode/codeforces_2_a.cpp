#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>

const int INF = 100000007;
using namespace std;
struct Person {
    string name;
    int score;
};
struct Person person[1007];
map<string, int> maps, maps2;
string cnt_name;
int cnt_score;
int main() {
//    freopen("input.txt", "r", stdin);
    maps.clear();
    string ans;
    int max_number = -INF;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cnt_name >> cnt_score;
        person[i].name = cnt_name;
        person[i].score = cnt_score;
        maps[cnt_name] += cnt_score;
    }
    for (map<string,int>::iterator it = maps.begin(); it != maps.end(); it++) {
        if (it->second > max_number) {
            max_number = it->second;
        }
    }
    maps2.clear();
    for (int i = 1; i <= n; i++) {
        cnt_name = person[i].name;
        cnt_score = person[i].score;
        maps2[cnt_name] += cnt_score;
        if (maps2[cnt_name] >= max_number && maps[cnt_name] == max_number) {
            ans = cnt_name;
            break;
        }
    }
    cout << ans << endl;
}
