#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 20050;
int vis[MAX_NUMBER];
int k_advertisements, jogger_number;
int adver_number;
struct node {
    int start;
    int end;
};
node Node[MAX_NUMBER];
bool cmp(struct node a,struct node b) {
    if (a.end < b.end) {
        return true;
    }
    else
        return false;
}
void solve() {
    for (int i = 0; i < jogger_number; i++) {
        int ad_must_see = k_advertisements;
        if (Node[i].end - Node[i].start + 1 <= k_advertisements) {
            for (int j = Node[i].start; j <= Node[i].end; j++) {
                if (vis[j] != 1) {
                    vis[j] = 1;
                    adver_number++;
                }
            }
        }
        else {
            for (int j = Node[i].start; j <= Node[i].end; j++) {
                if (vis[j] == 1) {
                    ad_must_see--;
                }
            }
            for (int j = Node[i].end; j >= Node[i].start && ad_must_see > 0; j--) {
                if (vis[j] != 1) {
                    vis[j] = 1;
                    ad_must_see--;
                    adver_number++;
                }
            }
        }
    }
}
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        cin.get();
        memset(vis,0,sizeof(vis));
        adver_number = 0;
        cin >> k_advertisements >> jogger_number;
        for (int i = 0; i < jogger_number; i++) {
            int start, end;
            cin >> start >> end;
            start += 10000;
            end += 10000;
            if (start > end) {
                Node[i].end = start;
                Node[i].start = end;
            }
            else {
                Node[i].end = end;
                Node[i].start = start;
            }
        }
        sort(Node,Node + jogger_number,cmp);
        solve();
        cout << adver_number << endl;
        for (int i = Node[0].start; i <= Node[jogger_number - 1].end; i++) {
            if (vis[i] == 1) {
                cout << i - 10000 << endl;
            }
        }
        if (test_case) {
            cout << endl;
        }
    }
}
