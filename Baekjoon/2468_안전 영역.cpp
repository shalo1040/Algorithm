// [2468] 안전 영역 : https://www.acmicpc.net/problem/2468
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int n, ans;
int map[101][101];
int visit[101][101];

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

void bfs(int level, int y, int x) {
	queue<pair<int, int>> q;
	q.push({y, x});
	visit[y][x] = 1;
	while(!q.empty()) {
		int yy = q.front().first;
		int xx = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nextY = yy + dirY[i];
			int nextX = xx + dirX[i];
			if(nextY>=0 && nextY<n && nextX>=0 && nextX<n) {
				if(map[nextY][nextX] > level && !visit[nextY][nextX]) {
					visit[nextY][nextX] = 1;
					q.push({nextY, nextX});
				}
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	}
	//높이가 l 이하인 곳은 모두 잠긴다.
	for(int l = 0; l <= 100; l++) {
		int count = 0;
		memset(visit, 0, sizeof(visit));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(map[i][j] > l && !visit[i][j]) {
					bfs(l, i, j);
					count++;
				}
			}
		}
		//모두 잠겼으면 반복문 빠져나온다.
		if(count == 0) break;
		//ans와 count 중 큰 수 택한다.
		ans = (ans > count) ? ans : count;
	}
	printf("%d", ans);
	return 0;
}