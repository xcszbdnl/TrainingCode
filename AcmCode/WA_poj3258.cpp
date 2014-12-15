#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAX_NUMBER = 50005;
const int MAX_LENTH = 1000000006;

int rock_coordinate[MAX_NUMBER];
int rock_number;
int remove_number;
struct Rock{
    int number_of_rock;
    int rock_distance;
    int removed;
    
};
struct Rock rock[MAX_NUMBER];


int main() {
    freopen("input.txt", "r", stdin);
    int distance;
    while (scanf("%d%d%d", &distance, &rock_number, &remove_number) != EOF) {
        for (int i = 0; i < rock_number; i++) {
            scanf("%d", &rock_coordinate[i]);
        }
        sort(rock_coordinate, rock_coordinate + rock_number);
        for (int i = 0; i <= rock_number; i++) {
            if (i == rock_number) {
                rock[i].rock_distance = distance - rock_coordinate[i - 1];
                rock[i].number_of_rock = i;
            }
            else if (!i) {
                rock[i].rock_distance = rock_coordinate[i];
                rock[i].number_of_rock = i;
            }
            
            else {
                rock[i].rock_distance = rock_coordinate[i] - rock_coordinate[i - 1];
                rock[i].number_of_rock = i;
            }
            rock[i].removed = 0;
        }
        for (int i = 1; i <= remove_number; i++) {
            int min = MAX_LENTH;
            int min_number;
            for (int j = 0; j <= rock_number; j++) {
                if (!rock[j].removed && rock[j].rock_distance < min) {
                    min = rock[j].rock_distance;
                    min_number = rock[j].number_of_rock;
                }
            }
            if (!min_number) {
                rock[min_number].removed = 1;
                rock[min_number + 1].rock_distance += rock[min_number].rock_distance;
            }
            else if (min_number == rock_number) {
                rock[min_number - 1].removed = 1;
                rock[rock_number].rock_distance += rock[rock_number - 1].rock_distance;
            }
            else {
                if (rock[min_number + 1].rock_distance < rock[min_number - 1].rock_distance) {
                    rock[min_number].removed = 1;
                    rock[min_number + 1].rock_distance += rock[min_number].rock_distance;
                }
                else {
                    rock[min_number - 1].removed = 1;
                    rock[min_number].rock_distance += rock[min_number - 1].rock_distance;
                }
            }
        }
        int min_number = MAX_LENTH;
        for (int i = 0; i <= rock_number; i++) {
            if (!rock[i].removed && rock[i].rock_distance < min_number) {
                min_number = rock[i].rock_distance;
            }
        }
        cout << min_number << endl;
    }
}
