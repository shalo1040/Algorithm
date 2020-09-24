// [5427] 불 : https://www.acmicpc.net/problem/5427
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int T, w, h, ans = -1;
char map[1001][1001];
//{{y, x}, 이동횟수}
queue<pair<pair<int, int>, int>> user;
queue<pair<int, int>> fire;

int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void solve() {
	bool visit[h][w];
	memset(visit, false, sizeof(visit));
	while(1) {
		if(!user.size() && !fire.size()) break;
		int size = user.size();
		while(size--) {
			int y = user.front().first.first;
			int x = user.front().first.second;
			int cnt = user.front().second;
			user.pop();
			if(y<0 || y>=h || x<0 || x>=w) { ans = cnt; return; }
			if(map[y][x] == '*') continue;
			for(int i = 0; i < 4; i++) {
				int ny = y + dir[i][0];
				int nx = x + dir[i][1];
				if(ny<0 || ny>=h || nx<0 || nx>=w) {
				    user.push({{ny, nx}, cnt+1});
				    continue;
				}
				if(!visit[ny][nx] && map[ny][nx] == '.') {
					user.push({{ny, nx}, cnt+1});
					visit[ny][nx] = true;
				}
			}
		}
		size = fire.size();
		while(size--) {
			int y = fire.front().first;
			int x = fire.front().second;
			fire.pop();
			for(int i = 0; i < 4; i++) {
				int ny = y + dir[i][0];
				int nx = x + dir[i][1];
				if(ny<0 || ny>=h || nx<0 || nx>= w) continue;
				if(map[ny][nx] == '#' || map[ny][nx] == '*') continue;
				map[ny][nx] = '*';
				fire.push({ny, nx});
			}
		}
	}
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &w, &h);
		for(int i = 0; i < h; i++) {
			scanf("%s", &map[i][0]);
			for(int j = 0; j < w; j++) {
				switch(map[i][j]) {
					case '@':
						user.push({{i, j}, 0});
						map[i][j] = '.';
						break;
					case '*':
						fire.push({i, j});
						break;
				}
			}
		}
		solve();
		(ans < 0) ? printf("IMPOSSIBLE\n") : printf("%d\n", ans);
		//reset
		ans = -1;
		while(!user.empty()) user.pop();
		while(!fire.empty()) fire.pop();
	}
}