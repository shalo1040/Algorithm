// [7579] 토마토 : https://www.acmicpc.net/problem/7569
#include <cstdio>
#include <queue>
using namespace std;

//m: 상자의 가로 칸 수
//n: 상자의 세로 칸 수
//h: 상자의 수
int m, n, h;
//토마토가 존재하는지 여부
bool isTomato = false;
int map[101][101][101];
//{단계, {행, 열}}
queue<pair<int, pair<int, int>>> q;

int dirX[] = {0, 0, 0, 0, 1, -1};
int dirY[] = {0, 0, 1, -1, 0, 0};
int dirZ[] = {1, -1, 0, 0, 0, 0};

bool check() {
	for(int d = 0; d < h; d++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(!map[d][i][j]) return false;
				if(map[d][i][j] == 1) isTomato = true;
			}
		}
	}
	return true;
}
void bfs() {
	int ans = -1;
	int size = q.size();
	while(!q.empty()) {
		int height = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;
		q.pop();
		for(int i = 0; i < 6; i++) {
			int nextH = height + dirZ[i];
			int nextY = y + dirY[i];
			int nextX = x + dirX[i];
			if(nextH>=0 && nextH<h && nextY>=0 && nextY<n && nextX>=0 && nextX<m) {
				if(!map[nextH][nextY][nextX]) {
					map[nextH][nextY][nextX]++;
					q.push({nextH, {nextY, nextX}});
				}
			}
		}
		if(--size == 0) { size = q.size(); ans++; }
	}
	if(check()) printf("%d", ans);
	else printf("-1");
}
int main() {
	scanf("%d %d %d", &m, &n, &h);
	for(int d = 0; d < h; d++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				scanf("%d", &map[d][i][j]);
				if(map[d][i][j]==1) q.push({d, {i, j}});
			}
		}
	}
	if(check()) {
	    if(isTomato) printf("0");
	    else printf("-1");
	} else bfs();
	return 0;
}