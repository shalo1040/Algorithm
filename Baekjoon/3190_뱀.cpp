// [3190] 뱀 : https://www.acmicpc.net/problem/3190
#include <cstdio>
#include <deque>
using namespace std;

/*
n: 보드 세로, 가로 크기
apples: 사과의 개수
moves: 이동 명령 수
ans: 게임 종료까지 걸리는 시간
*/
int n, apples, moves, ans;
int map[101][101];
//front: 뱀의 꼬리, back: 뱀의 머리
//{y, x}
deque<pair<int, int>> snake;

enum Direction {up, down, left, right};
int direction = right;	//0초부터 (1,1)에서 오른쪽을 보고 시작
bool flag = false;		//게임이 중간에 종료되었는지 여부 나타냄

bool solve(int sec, char dir) {
	//주어진 시간동안 1초씩 전진
	while(sec--) {
		//뱀의 머리 좌표
		int ny = snake.back().first, nx = snake.back().second;
		//현재 방향에 따라 다음에 뱀이 도착할 칸의 좌표 설정
		switch(direction) {
			case up:
				ny -= 1; break;
			case down:
				ny += 1; break;
			case left:
				nx -= 1; break;
			case right:
				nx += 1; break;
		}
		//다음 칸이 보드의 범위를 벗어나거나 자기 자신(2)이라면 중간에 종료되었다고 flag를 변경하고 false 리턴
		if(ny<1 || ny>n || nx<1 || nx>n || map[ny][nx] == 2) { ans++; flag = true; return false; }
		//다음 칸에 사과가 없고 비어있으면
		if(!map[ny][nx]) {
			//덱에서 꼬리의 좌표를 꺼내고
			int tailY = snake.front().first;
			int tailX = snake.front().second;
			snake.pop_front();
			//빈 칸으로 만들어준다.
			map[tailY][tailX] = 0;
		}
		//전진한 자리는 뱀이 있다는 표시로 2를 넣어주고
		map[ny][nx] = 2;
		//덱에 푸시
		snake.push_back({ny, nx});
		ans++;
	}
	//현재 방향에 따라 다음 방향 변경
	switch(direction) {
		case up:
			direction = (dir == 'L') ? left : right; break;
		case down:
			direction = (dir == 'L') ? right : left; break;
		case left:
			direction = (dir == 'L') ? down : up; break;
		case right:
			direction = (dir == 'L') ? up : down; break;
	}
	return true;
}
int main() {
	scanf("%d %d", &n, &apples);
	for(int i = 0; i < apples; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		map[y][x] = 1;
	}
	//0초에 (1,1)에서 시작하므로 2를 넣어준다.
	map[1][1] = 2;
	snake.push_front({1, 1});
	scanf("%d", &moves);
	for(int i = 0; i < moves; i++) {
		int sec; char dir;
		scanf("%d %c", &sec, &dir);
		if(!solve(sec-ans, dir)) break;
	}
	//입력된 정보만큼 이동 후 아직 게임이 끝나지 않았으면 게임이 종료될때까지 solve() 실행
	if(!flag) solve(n+1, 'L');
	printf("%d", ans);
	return 0;
}