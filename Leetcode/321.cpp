#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:

    string choose(vector<int>& num, int tot_num) {
        string result = "";
        int pre_loc = 0;
        if (tot_num > num.size()) {
            return result;
        }
        for (int i = 0; i < tot_num; i++) {
            pre_loc = selectMax(num, pre_loc, num.size() - tot_num + i);
            result += num[pre_loc] + '0';
            pre_loc++;
        }
        return result;
    }

    int selectMax(vector<int> &num, int s, int e) {
        int max_num = -1;
        int idx = s;
        for (int i = s; i<= e; i++) {
            if (num[i] > max_num) {
                max_num = num[i];
                idx = i;
            }
        }
        return idx;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        string result = "";
        for (int i = 0; i <= k; i++) {
            string temp_1 = choose(nums1, i);
            string temp_2 = choose(nums2, k - i);
            if (temp_1.size() + temp_2.size() != k) {
                continue;
            }
//            cout << temp_1 << endl;
//            cout << temp_2 << endl;
//            cout << "--------" << endl;
            int p = 0, q = 0;
            string final_temp = "";
            while (p < temp_1.size() || q < temp_2.size()) {
                if (p < temp_1.size() && (q == temp_2.size() || temp_1[p] > temp_2[q])) {
                    final_temp += temp_1[p];
                    p++;
                }
                else if (p == temp_1.size() || temp_1[p] < temp_2[q]) {
                    final_temp += temp_2[q];
                    q++;
                }
                else {
                    int a = temp_1[p];
                    int b = temp_2[q];
                    int x = p;
                    int y = q;
                    int flag = 0;
                    while (x < temp_1.size() && y < temp_2.size()) {
                        if (temp_1[x] < temp_2[y]) {
                            flag = 1;
                            final_temp += b;
                            q++;
                            break;
                        }
                        else if (temp_1[x] > temp_2[y]) {
                            flag = 1;
                            final_temp += a;
                            p++;
                            break;
                        }
                        x++;
                        y++;
                    }
                    if (!flag) {
                        if (x < temp_1.size()) {
                            final_temp += a;
                            p++;
                        }
                        else {
                            final_temp += b;
                            q++;
                        }
                    }
                }
            }
            if (final_temp > result) {
                result = final_temp;
            }
        }
//        cout << result << endl;
        vector<int> v_result;
        for (int i = 0; i < result.size(); i++) {
            v_result.push_back(result[i] - '0');
        }
        return v_result;
    }
};


int main() {
    freopen("in.txt", "r", stdin);
    Solution a;
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> num1, num2;
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        num1.push_back(c);
    }
    for (int i = 0; i < m; i++) {
        int c;
        scanf("%d", &c);
        num2.push_back(c);
    }
    vector<int> temp = a.maxNumber(num1, num2, 7);
    for (int i = 0; i < temp.size(); i++) {
        cout << temp[i];
    }
    cout << endl;
    return 0;
}
