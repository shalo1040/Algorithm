// [16929] Two Dots : https://www.acmicpc.net/problem/16929
#include <cstdio>
#include <cstring>

//width, height
int w, h;
char map[51][51];
int visit[51][51];
bool flag = false;

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

//x, y: 현재 점의 좌표, px, py: 시작 점의 좌표, count: 연속된 점의 수
void solve(int y, int x, int py, int px, int count) {
    visit[y][x] = 1;
	for(int i = 0; i < 4; i++) {
		int ny = y + dirY[i];
		int nx = x + dirX[i];
		//다음 좌표가 시작 점과 같고 연속해서 4개 이상 방문했으면 flag = true
		if(ny == py && nx == px && count >= 4) { flag = true; return; }
		if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
		if(!visit[ny][nx] && map[ny][nx] == map[y][x])
			solve(ny, nx, py, px, count+1);
	}
}
int main() {
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; i++)
		scanf("%s", &map[i]);
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			memset(visit, 0, sizeof(visit));
			//모든 점에서 dfs 실행
			solve(i, j, i, j, 1);
			if(flag) {
				printf("Yes");
				return 0;
			}
		}
	}
	printf("No");
	return 0;
}