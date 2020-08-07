// [2174] 로봇 시뮬레이션 : https://www.acmicpc.net/problem/2174
#include <cstdio>
#define MAX 101

struct Robot {
	int x, y;	//로봇 위치
	char dir;	//로봇 방향(N,W,S,E)
	Robot() {};
	Robot(int x, int y, char d) { this->x = x; this->y = y; dir = d; };
};

/*
w: 가로 크기
h: 세로 크기
robots: 로봇의 수
commands: 명령의 수
*/
int w, h, robots, commands;
int map[MAX][MAX];	//로봇 번호 저장
Robot r[MAX];		//로봇 정보 저장

void turnLeft(char* dir) {
	switch(*dir){
		case 'N':
			*dir = 'W';
			break;
		case 'W':
			*dir = 'S';
			break;
		case 'S':
			*dir = 'E';
			break;
		case 'E':
			*dir = 'N';
			break;
	}
}
void turnRight(char* dir) {
	switch(*dir){
		case 'N':
			*dir = 'E';
			break;
		case 'W':
			*dir = 'N';
			break;
		case 'S':
			*dir = 'W';
			break;
		case 'E':
			*dir = 'S';
			break;
	}
}
void forward(int* x, int* y, char dir) {
	switch(dir) {
		case 'N':
			--(*y);
			break;
		case 'W':
			--(*x);
			break;
		case 'S':
			++(*y);
			break;
		case 'E':
			++(*x);
			break;
	}
}
bool solve(int robot, char command, int repeat) {
	int x = r[robot].x;
	int y = r[robot].y;
	char dir = r[robot].dir;
	while(repeat--) {
		switch(command) {
			case 'L':
				turnLeft(&dir);
				break;
			case 'R':
				turnRight(&dir);
				break;
			case 'F':
				map[y][x] = 0;	//로봇이 있던 자리는 0으로 변경
				forward(&x, &y, dir);
				// 주어진 땅 밖으로 벗어나는 경우
				if(x<1 || x>w || y<1 || y>h) {
					printf("Robot %d crashes into the wall", robot);
					return true;
				}
				// 다른 로봇과 충돌하는 경우
				if(map[y][x]) {
					printf("Robot %d crashes into robot %d", robot, map[y][x]);
					return true;
				}
				// 성공적으로 앞으로 움직이면 그 위치에 로봇의 번호 저장
				map[y][x] = robot;
				break;
		}
		//로봇 정보 갱신
		r[robot] = Robot(x, y, dir);
	}
	return false;
}
int main() {
	scanf("%d %d %d %d", &w, &h, &robots, &commands);
	for(int i = 0; i < robots; i++) {
		int x, y; char d;
		scanf("%d %d %c", &x, &y, &d);
		map[h-y+1][x] = i+1;
		r[i+1] = Robot(x, h-y+1, d);
	}
	while(commands--) {
		int robotNum, repeat; char command;
		scanf("%d %c %d", &robotNum, &command, &repeat);
		if(solve(robotNum, command, repeat)) return 0;
	}
	printf("OK");
	return 0;
}