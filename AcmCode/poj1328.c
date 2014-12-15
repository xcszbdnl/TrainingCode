#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAX_NUMBER = 1005;

struct Location {
    double left;
    double right;
};

struct Location location[MAX_NUMBER];
int radius;
int number;

bool cmp(Location x, Location y) {
    if (x.left != y.left) {
        return x.left < y.left;
    }
    return x.right > y.right;
}

int main() {
    freopen("input.txt", "r", stdin);
    int j;
    int flag, case_number = 1;
    double range, x, y;
    while (cin >> number >> radius) {
        if (!number && !radius) {
            break;
        }
        int radar_number = 0;
        double radar_location;
        flag = 0;
        for (int i = 0; i < number; i++) {
            cin >> x >> y;
            if (y > radius || y < 0 || radius <= 0) {
                flag = 1;
            }
            else {
                range = radius * radius - y * y;
                location[i].left = x - sqrt(range);
                location[i].right = x + sqrt(range);
            }
        }
        if (flag) {
            cout << "Case " << case_number << ": -1" << endl;
            case_number++;
            continue;
        }
        sort(location, location + number, cmp);
        radar_location = location[0].right;
        radar_number++;
        for (int i = 1; i < number; i++) {
            if (location[i].left - radar_location > 10e-7) {
                radar_number++;
                radar_location = location[i].right;
            }
            else {
                if (location[i].right - radar_location < 10e-7) {
                    radar_location = location[i].right;
                }
            }
        }
        cout << "Case " << case_number << ": " << radar_number << endl;
        case_number++;
    }
}
