// [2583] 영역 구하기 : https://www.acmicpc.net/problem/2583
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int w, h, rectangle;
vector<int> size;
vector<vector<bool>> map, visit;

int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void solve(int startY, int startX) {
	int cnt = 1;
	queue<pair<int, int>> q;
	q.push({startY, startX});
	visit[startY][startX] = true;
	while(!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];
			if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
			if(visit[ny][nx] || map[ny][nx]) continue;
			//이어져 있는 빈 영역이면 push, 면적+1
			q.push({ny, nx});
			visit[ny][nx] = true;
			cnt++;
		}
	}
	size.push_back(cnt);	//영역별 면적 저장하는 size에 cnt 넣는다.
}
int main() {
	scanf("%d %d %d", &h, &w, &rectangle);
	map = vector<vector<bool>>(h+1, vector<bool>(w+1,false));
	visit = vector<vector<bool>>(h, vector<bool>(w,false));
	for(int i = 0; i < rectangle; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		for(int a = x1; a < x2; a++) {
			for(int b = y1; b < y2; b++)
				map[b][a] = true;		//직사각형 표시
		}
	}
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			if(!map[i][j] && !visit[i][j])
				solve(i, j);
		}
	}
	printf("%d\n", size.size());
	sort(size.begin(), size.end());
	for(int s : size) 
		printf("%d ", s);
	return 0;
}