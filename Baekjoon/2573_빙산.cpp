// [2573] 빙산 : https://www.acmicpc.net/problem/2573
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

//n: 행, m: 열
int n, m;
int map[301][301];
int visit[301][301];

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

void bfs(int y, int x) {
	queue<pair<int, int>> q;
	q.push({y, x});
	visit[y][x] = 1;
	while(!q.empty()) {
		int yy = q.front().first;
		int xx = q.front().second;
	    q.pop();
		for(int i = 0; i < 4; i++) {
			int nY = yy + dirY[i];
			int nX = xx + dirX[i];
			if(nY>=0 && nY<n && nX>=0 && nX<m) {
				if(map[nY][nX] > 0 && !visit[nY][nX]) {
					visit[nY][nX] = 1;
					q.push({nY, nX});
				}
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	}
	//y: year
	int y = 1;
	while(1) {
		vector<int*> p;
		for(int i = 1; i < n-1; i++) {
			for(int j = 1; j < m-1; j++) {
				if(map[i][j] > 0) {
					//동서남북이 0이면 1씩 감소
					for(int k = 0; k < 4; k++) {
						int nY = i+dirY[k];
						int nX = j+dirX[k];
						if(nY>=0 && nY<n && nX>=0 && nX<m) {
							if(map[nY][nX] == 0) --map[i][j];
						}
					}
					//map[i][j]가 0이 되면 다른 빙하에서도 1만큼 더 감소할 수 있어 -1로 바꿔준다.
					//바다의 칸 수만큼 뺀 결과가 음수값인 것도 포인터 배열에 넣어 나중에 0으로 바꿔준다.
					if(map[i][j] <= 0) {
						map[i][j] = -1;
						p.push_back(&map[i][j]);
					}
				}
			}
		}
		for(int i = 0; i < p.size(); i++)
			*p[i] = 0;
		//cnt로 영역의 개수를 센다.
		memset(visit, 0, sizeof(visit));
		int cnt = 0;
		for(int i = 1; i < n-1; i++) {
			for(int j = 1; j < m-1; j++) {
				if(map[i][j] > 0 && !visit[i][j]) {
					bfs(i, j);
					cnt++;
				}
			}
		}
		//영역의 개수가 2 이상이면 year 출력하고 프로그램 종료
		if(cnt > 1) { printf("%d", y); break; }
		//영역의 개수가 0이면 빙산이 모두 녹을 때까지 영역 분리가 안된 것이므로 0 출력하고 종료
		if(cnt == 0) { printf("0"); break; }
		y++;
	}
	return 0;
}