#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 102

int map[MAX_NUMBER][MAX_NUMBER];
struct Robots {
    int x;
    int y;
    int direction;
};

struct Robots robot[MAX_NUMBER];
int A, B;

void turnLeft(int instruction_robot, int times) {
    int i;
    for (i = 0; i < times; i++) {
        robot[instruction_robot].direction--;
        if (robot[instruction_robot].direction < 0) {
            robot[instruction_robot].direction = 3;
        }
    }
}

void turnRight(int instruction_robot, int times) {
    int i;
    for (i = 0; i < times; i++) {
        robot[instruction_robot].direction = (robot[instruction_robot].direction + 1) % 4;
    }
}

int foward(int instruction_robot, int times) {
    int i;
    switch(robot[instruction_robot].direction) {
    case 0:
        for (i = 0; i < times; i++) {
            map[robot[instruction_robot].x][robot[instruction_robot].y] = 0;
            robot[instruction_robot].y++;
            if (map[robot[instruction_robot].x][robot[instruction_robot].y] != 0) {
                printf("Robot %d crashes into robot %d\n", instruction_robot, map[robot[instruction_robot].x][robot[instruction_robot].y]);
                return 0;
            }
            if (robot[instruction_robot].y == B + 1) {
                printf("Robot %d crashes into the wall\n", instruction_robot);
                return 0;
            }
            map[robot[instruction_robot].x][robot[instruction_robot].y] = instruction_robot;
        }
        return 1;
    case 1:
        map[robot[instruction_robot].x][robot[instruction_robot].y] = 0;        
        for (i = 0; i < times; i++) {
            robot[instruction_robot].x++;
            if (map[robot[instruction_robot].x][robot[instruction_robot].y] != 0) {
                printf("Robot %d crashes into robot %d\n", instruction_robot, map[robot[instruction_robot].x][robot[instruction_robot].y]);
                return 0;
            }
            if (robot[instruction_robot].x == A + 1) {
                printf("Robot %d crashes into the wall\n", instruction_robot);
                return 0;
            }
        }
        map[robot[instruction_robot].x][robot[instruction_robot].y] = instruction_robot;        
        return 1;
    case 2:
        map[robot[instruction_robot].x][robot[instruction_robot].y] = 0;        
        for (i = 0; i < times; i++) {
            robot[instruction_robot].y--;
            if (map[robot[instruction_robot].x][robot[instruction_robot].y] != 0) {
                printf("Robot %d crashes into robot %d\n", instruction_robot, map[robot[instruction_robot].x][robot[instruction_robot].y]);
                return 0;
            }
            if (robot[instruction_robot].y == 0 ) {
                printf("Robot %d crashes into the wall\n", instruction_robot);
                return 0;
            }
        }
        map[robot[instruction_robot].x][robot[instruction_robot].y] = instruction_robot;        
        return 1;
    case 3:
        map[robot[instruction_robot].x][robot[instruction_robot].y] = 0;        
        for (i = 0; i < times; i++) {
            robot[instruction_robot].x--;
            if (map[robot[instruction_robot].x][robot[instruction_robot].y] != 0) {
                printf("Robot %d crashes into robot %d\n", instruction_robot, map[robot[instruction_robot].x][robot[instruction_robot].y]);
                return 0;
            }
            if (robot[instruction_robot].x == 0 ) {
                printf("Robot %d crashes into the wall\n", instruction_robot);
                return 0;
            }
        }
        map[robot[instruction_robot].x][robot[instruction_robot].y] = instruction_robot;        
        return 1;
    }
}
int process(int instruction_robot, char instruction, int times) {
    int flag = 1;
    switch(instruction) {
    case 'L':
        turnLeft(instruction_robot, times);
        break;
    case 'R':
        turnRight(instruction_robot, times);
        break;
    case 'F':
        flag = foward(instruction_robot, times);
        break;
    }
    return flag;
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, robot_number, instruction_number;
    int test_case, instruction_robot, times, flag;
    char direction, instruction;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(map, 0, sizeof(map));
        flag = 1;
        scanf("%d%d", &A, &B);
        scanf("%d%d", &robot_number, &instruction_number);
        for (i = 1; i <= robot_number; i++) {
            scanf("%d %d %c", &robot[i].x, &robot[i].y, &direction);
            switch(direction) {
            case 'N':
                robot[i].direction = 0;
                break;
            case 'E':
                robot[i].direction = 1;
                break;
            case 'S':
                robot[i].direction = 2;
                break;
            case 'W':
                robot[i].direction = 3;
                break;
            }
            map[robot[i].x][robot[i].y] = i;
        }
        for (i = 0; i < instruction_number && flag; i++) {
            scanf("%d %c %d", &instruction_robot, &instruction, &times);
            flag = process(instruction_robot, instruction, times);
        }
        while (i < instruction_number) {
            scanf("%d %c %d", &instruction_robot, &instruction, &times);
            i++;
        }
        if (flag) {
            printf("OK\n");
        }
    }
}
