// [6593] 상범 빌딩 : https://www.acmicpc.net/problem/6593
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef struct {
	int floor, y, x, cnt;
} Pos;

const int MAX = 31;
int L, R, C;
Pos user;
char map[MAX][MAX][MAX];

int dir[][3] = { {0,0,1}, {0,0,-1}, {0,1,0}, {0,-1,0}, {1,0,0}, {-1,0,0} };

int solve() {
	bool visit[L][R][C];
	memset(visit, false, sizeof(visit));
	queue<Pos> q;
	q.push(user);
	visit[user.floor][user.y][user.x] = true;
	while(!q.empty()) {
		int floor = q.front().floor;
		int y = q.front().y;
		int x = q.front().x;
		int cnt = q.front().cnt;
		q.pop();
		if(map[floor][y][x] == 'E') return cnt;
		for(int i = 0; i < 6; i++) {
			int nfloor = floor + dir[i][0];
			int ny = y + dir[i][1];
			int nx = x + dir[i][2];
			if(nfloor<0 || nfloor>=L || ny<0 || ny>=R || nx<0 || nx>=C) continue;
			if(!visit[nfloor][ny][nx] && map[nfloor][ny][nx] != '#') {
				visit[nfloor][ny][nx] = true;
				q.push({nfloor, ny, nx, cnt+1});
			}
		}
	}
	return -1;
}
int main() {
	while(1) {
		scanf("%d %d %d", &L, &R, &C);
		if(!L && !R && !C) break;
		user.floor = -1;
		for(int i = 0; i < L; i++) {
			for(int j = 0; j < R; j++) {
				scanf("%s", &map[i][j]);
				//아직 시작점을 발견하지 못했으면 S 찾기
				if(user.floor == -1) {
					for(int k = 0; k < C; k++) {
						if(map[i][j][k] == 'S') {
							user.floor = i;
							user.y = j;
							user.x = k;
							user.cnt = 0;
							map[i][j][k] = '.';
						}
					}
				}
			}
		}
		int ans = solve();
		(ans < 0) ? printf("Trapped!\n") : printf("Escaped in %d minute(s).\n", ans);
	}
	return 0;
}