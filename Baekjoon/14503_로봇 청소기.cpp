// [14503] 로봇 청소기 : https://www.acmicpc.net/problem/14503
#include <cstdio>
#include <queue>
using namespace std;

//n: 세로 크기, m: 가로 크기
int n, m;
int map[51][51];
//y: 로봇의 위치로부터 북쪽으로 떨어진 칸의 개수
//x: 로봇의 위치로부터 서쪽으로 떨어진 칸의 개수
//d: 로봇이 바라보고 있는 방향
int y, x, d;
enum Direction {north, east, south, west};

//현재 로봇이 바라보고 있는 방향 d에 따른 왼쪽 방향 및 좌표 정의
void searchLeft(int y, int x, int d, int* newDir, int* forwardY, int* forwardX, int* backY, int* backX) {
	switch(d) {
		case north:
			*newDir = west;
			*forwardX = x-1; *backY = y+1;
			break;
		case east:
			*newDir = north;
			*forwardY = y-1; *backX = x-1;
			break;
		case south:
			*newDir = east;
			*forwardX = x+1; *backY = y-1;
			break;
		case west:
			*newDir = south;
			*forwardY = y+1; *backX = x+1;
			break;
	}
}
int solve() {
	int ans = 0;
	int visit[n][m] = {0};
	queue<pair<pair<int, int>, int>> q;
	q.push({{y, x}, d});
	//1. 현재 위치 청소
	visit[y][x] = 1;
	ans++;
	while(!q.empty()) {
		y = q.front().first.first;
		x = q.front().first.second;
		d = q.front().second;
		q.pop();
		//1번 현재 위치 청소는 큐에 넣을 때 실행
		//2. 현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		//왼쪽
		int newDir = d, forwardY = y, forwardX = x, backY = y, backX = x;
		searchLeft(y, x, d, &newDir, &forwardY, &forwardX, &backY, &backX);
		//왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
		if(!map[forwardY][forwardX] && !visit[forwardY][forwardX]) {
			q.push({{forwardY, forwardX}, newDir});
			//1. 전진한 위치 청소
			visit[forwardY][forwardX] = 1;
			ans++;
		} else {
		    //네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
		    if((map[y+1][x] || visit[y+1][x]) && (map[y][x-1] || visit[y][x-1]) && (map[y-1][x] || visit[y-1][x]) && (map[y][x+1] || visit[y][x+1])) {
    			//네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
    			if(map[backY][backX]) return ans;
    			q.push({{backY, backX}, d});
		    }
	    	//왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
			else if(map[forwardY][forwardX] || visit[forwardY][forwardX])
		        q.push({{y, x}, newDir});
		}
	}
	return ans;
}
int main() {
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &y, &x, &d);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	}
	printf("%d", solve());
	return 0;
}