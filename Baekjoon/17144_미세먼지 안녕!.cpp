//[17144] 미세먼지 안녕! : https://www.acmicpc.net/problem/17144
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef struct {
    int y, x;
} Pos;

int h, w, time;
vector<vector<int>> map;
vector<Pos> dust;
vector<int> cleaner;

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//미세먼지 확산
void spreadDust() {
    vector<vector<int>> tmp;
    for(int i = 0; i < h; i++)
        tmp.push_back(map[i]);
	queue<Pos> q;
	for(int i = 0; i < dust.size(); i++)
		q.push({dust[i].y, dust[i].x});
	while(!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		q.pop();
		int spreadCnt = 0;
		for(int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];
			if(tmp[y][x] < 5) continue;
			if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
			if(map[ny][nx] == -1) continue;
			map[ny][nx] += tmp[y][x] / 5;
			dust.push_back({ny, nx});
			spreadCnt++;
		}
		map[y][x] -= (tmp[y][x] / 5) * spreadCnt;
	}
}
//공기청정기 작동
void wind() {
    dust.clear();
	//반시계 방향으로 순환
	for(int i = cleaner[0]-1; i > 0; i--)
		map[i][0] = map[i-1][0];
	for(int i = 0; i < w-1; i++)
		map[0][i] = map[0][i+1];
	for(int i = 0; i < cleaner[0]; i++)
		map[i][w-1] = map[i+1][w-1];
	for(int i = w-1; i > 1; i--)
		map[cleaner[0]][i] = map[cleaner[0]][i-1];
	map[cleaner[0]][1] = 0;
	//시계 방향으로 순환
	for(int i = cleaner[1]+1; i < h-1; i++)
		map[i][0] = map[i+1][0];
	for(int i = 0; i < w-1; i++)
		map[h-1][i] = map[h-1][i+1];
	for(int i = h-1; i > cleaner[1]; i--)
		map[i][w-1] = map[i-1][w-1];
	for(int i = w-1; i > 1; i--)
		map[cleaner[1]][i] = map[cleaner[1]][i-1];
	map[cleaner[1]][1] = 0;
	//미세먼지 dust에 넣는다.
	for(int i = 0; i < h; i++) {
	    for(int j = 0; j < w; j++) {
	        if(map[i][j] > 0) dust.push_back({i, j});
	    }
	}
}
void solve() {
	while(time--) {
		spreadDust();
		wind();
	}
}
int main() {
	scanf("%d %d %d", &h, &w, &time);
	for(int i = 0; i < h; i++) {
		vector<int> v;
		for(int j = 0; j < w; j++) {
			int input;
			scanf("%d", &input);
			v.push_back(input);
			if(input < 0)
				cleaner.push_back(i);
			else if(input)
				dust.push_back({i, j});
		}
		map.push_back(v);
	}
	if(cleaner[0] > cleaner[1]) {
		int tmp = cleaner[0];
		cleaner[0] = cleaner[1];
		cleaner[1] = tmp;
	}
	solve();
	int ans = 0;
	for(int i = 0; i < dust.size(); i++)
		ans += map[dust[i].y][dust[i].x];
	printf("%d", ans);
	return 0;
}