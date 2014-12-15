#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 50
#define MAX_TEAM 20

int team[MAX_TEAM][5];
int number_of_people[MAX_TEAM];
int person_team[MAX_NUMBER];
int student_number, pairs;
int student_1, student_2;
int team_number;


int main() {

    int i, j, temp, flag = 0;
    scanf("%d%d", &student_number, &pairs);
    team_number = 1;
    memset(team, 0, sizeof(team));
    memset(person_team, 0, sizeof(person_team));
    memset(number_of_people, 0, sizeof(number_of_people));
    for (i = 0; i < pairs; i++) {
        scanf("%d%d", &student_1, &student_2);
        if (person_team[student_1] == 0 && person_team[student_2] == 0) {
            team[team_number][1] = student_1;
            team[team_number][2] = student_2;
            person_team[student_1] = team_number;
            person_team[student_2] = team_number;
            number_of_people[team_number] = 2;
            team_number++;
        }
        else {
            if (person_team[student_1] == person_team[student_2]) {
                continue;
            }
            if (person_team[student_1] != 0 && person_team[student_2] != 0) {
                flag = 1;
                break;
            }
            if (person_team[student_1] != 0) {
                if (number_of_people[person_team[student_1]] == 3) {
                    flag = 1;
                    break;
                }
                else {
                    number_of_people[person_team[student_1]]++;
                    team[person_team[student_1]][3] = student_2;
                    person_team[student_2] = person_team[student_1];
                }
            }
            else {
                if (number_of_people[person_team[student_2]] == 3) {
                    flag = 1;
                    break;
                }
                else {
                    number_of_people[person_team[student_2]]++;
                    team[person_team[student_2]][3] = student_1;
                    person_team[student_1] = person_team[student_2];
                }
            }
        }
    }
    if (flag) {
        printf("-1\n");
        return 0;
    }
    for (i = 1; i <= student_number; i++) {
        if (person_team[i] == 0) {
            for (j = 1; j <= team_number; j++) {
                if (number_of_people[j] < 3) {
                    number_of_people[j]++;
                    team[j][number_of_people[j]] = i;
                    break;
                }
            }
            if (j > team_number) {
                team_number++;
                team[team_number][1] = i;
                number_of_people[team_number] = 1;
            }
        }
    }
    for (i = 1; i <= student_number / 3; i++) {
        printf("%d %d %d\n", team[i][1], team[i][2], team[i][3]);
    }
    return 0;
}
