// [13460] 구슬 탈출2 : https://www.acmicpc.net/problem/13460
#include <cstdio>
#include <queue>
using namespace std;

//h: 높이, w: 너비, ans: 디폴트로 -1
int h, w, ans = -1;
char map[10][11];

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

typedef struct {
	int redY, redX;		//빨간 구슬 위치
	int blueY, blueX;	//파란 구슬 위치
	int move;			//이동 횟수
} Marble;

void moveMarble(int& y, int& x, int i) {
	while(1) {
		y += dir[i][0];
		x += dir[i][1];
		// 벽이면 이동 반대 방향으로 한 칸 뒤로 간다.
		if(map[y][x] == '#') {
			y -= dir[i][0];
			x -= dir[i][1];
			return;
		}
		// 구멍이면 그대로 리턴
		else if(map[y][x] == 'O') return;
	}
}
//bfs
void solve(int y1, int x1, int y2, int x2) {
	int visit[10][10][10][10] = { 0, };
	queue<Marble> q;
	q.push({y1, x1, y2, x2, 0});
	visit[y1][x1][y2][x2] = 1;
	while(!q.empty()) {
		Marble m = q.front();
		q.pop();
		//10회를 초과해 시도하면 -1 출력
		if(m.move > 10) return;
		//빨간 구슬이 구멍에 들어가면 이동 횟수 출력
		if(map[m.redY][m.redX] == 'O') { ans = m.move; return; }
		for(int i = 0; i < 4; i++) {
			int ry = m.redY, rx = m.redX;
			int by = m.blueY, bx = m.blueX;
			//빨간 구슬과 파란 구슬을 이동시킨다.
			moveMarble(ry, rx, i);
			moveMarble(by, bx, i);
			//파란 구슬이 구멍에 들어가면 실패이므로 큐에 넣지 않는다.
			if(map[by][bx] == 'O') continue;
			//빨간 구슬과 파란 구슬이 겹쳐지면 이전 좌표를 비교해 한 칸 차이나게 둔다.
			if(ry==by && rx==bx) {
				switch(i) {
					case 0:
						(m.redX < m.blueX) ? rx-- : bx--; break;
					case 1:
						(m.redX < m.blueX) ? bx++ : rx++; break;
					case 2:
						(m.redY < m.blueY) ? ry-- : by--; break;
					case 3:
						(m.redY < m.blueY) ? by++ : ry++; break;
				}
			}
			//방문하지 않은 위치면 큐에 삽입
			if(!visit[ry][rx][by][bx]) {
				q.push({ry, rx, by, bx, m.move+1});
				visit[ry][rx][by][bx] = 1;
			}
		}
	}
}
int main() {
	scanf("%d %d", &h, &w);
	int ry, rx, by, bx;
	for(int i = 0; i < h; i++) {
		scanf("%s", &map[i]);
		for(int j = 0; j < w; j++) {
			if(map[i][j] == 'R') { ry = i; rx = j; }
			else if(map[i][j] == 'B') { by = i; bx = j; }
		}
	}
	solve(ry, rx, by, bx);
	printf("%d", ans);
	return 0;
}