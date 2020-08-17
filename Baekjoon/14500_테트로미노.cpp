// [14500] 테트로미노 : https://www.acmicpc.net/problem/14500
#include <cstdio>

//h: 높이, w: 너비, ans: 최대값
int h, w, ans;
int map[501][501];

//서로 인접한 4개 블록으로 만들 수 있는 테트로미노 19 개
//현재 좌표인 (0,0)은 제외한 3개의 좌표만 적음
int shape[19][3][2] = {
	//ㅡ 모양
	{{0,1}, {0,2}, {0,3}},
	//ㅣ 모양
	{{1,0}, {2,0}, {3,0}},
	//정사각형
	{{0,1}, {1,0}, {1,1}},
	//ㅗ 모양
	{{0,1}, {0,2}, {-1,1}},
	{{0,1}, {0,2}, {1,1}},
	{{1,0}, {2,0}, {1,1}},
	{{1,0}, {2,0}, {1,-1}}
	//뒤집은 L 모양
	{{1,0}, {2,0}, {2,-1}},
	{{1,0}, {1,1}, {1,2}},
	{{0,1}, {1,0}, {2,0}},
	{{0,1}, {0,2}, {1,2}},
	//L 모양
	{{1,0}, {2,0}, {2,1}},
	{{0,1}, {0,2}, {1,0}},
	{{0,1}, {1,1}, {2,1}},
	{{0,1}, {0,2}, {-1,2}},
	//z 모양
	{{0,1}, {-1,1}, {-1,2}},
	{{1,0}, {1,1}, {2,1}},
	//뒤집은 z 모양
	{{0,1}, {1,1}, {1,2}},
	{{1,0}, {1,-1}, {2,-1}},
};

void solve() {
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			for(int k = 0; k < 19; k++) {
				int sum = map[i][j];
				bool flag = true;
				for(int l = 0; l < 3; l++) {
					int y = i + shape[k][l][0];
					int x = j + shape[k][l][1];
					if(y<0 || y>=h || x<0 || x>=w) { flag = false; break; }
					sum += map[y][x];
				}
				if(flag && ans < sum) ans = sum;
			}
		}
	}
}
int main() {
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++)
			scanf("%d", &map[i][j]);
	}
	solve();
	printf("%d", ans);
	return 0;
}

/*
완전탐색 말고 dfs를 이용해서 푸는 방법도 있다.
dfs는 인접한 칸만 갈 수 있기 때문에 ㅓ,ㅏ,ㅗ,ㅜ는 만들지 못한다.
따라서 이 네 개의 모양에 대해서는 위에서와 같이 완전탐색을 해야한다.
시간과 메모리는 완전탐색보다 dfs가 더 많이 나왔다.

int dfs(int y, int x, int count) {
	if(count == 4) return map[y][x];
	int sum = 0;
	for(int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];
		if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
		if(!visit[ny][nx]) {
			visit[ny][nx] = true;
			sum = max(sum, map[y][x] + dfs(ny, nx, count+1));
			visit[ny][nx] = false;
		}
	}
	return sum;
}
int findOthers(int y, int x) {
	int sum = 0;
	//ㅗ
	if(y>0 && y<h && x>0 && x<w-1)
		sum = max(sum, map[y][x] + map[y][x-1] + map[y][x+1] + map[y-1][x]);
	//ㅜ
	if(y>=0 && y<h-1 && x>0 && x<w-1)
		sum = max(sum, map[y][x] + map[y][x-1] + map[y][x+1] + map[y+1][x]);
	//ㅏ
	if(y>0 && y<h-1 && x>=0 && x<w-1)
		sum = max(sum, map[y][x] + map[y-1][x] + map[y+1][x] + map[y][x+1]);
	//ㅓ
	if(y>0 && y<h-1 && x>0 && x<w)
		sum = max(sum, map[y][x] + map[y-1][x] + map[y+1][x] + map[y][x-1]);
	return sum;
}
int main() {
	...
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			visit[i][j] = true;
			ans = max(ans, dfs(i, j, 1));
			ans = max(ans, findOthers(i, j));
			visit[i][j] = false;
		}
	}
	printf("%d", ans);
	return 0;
}
*/