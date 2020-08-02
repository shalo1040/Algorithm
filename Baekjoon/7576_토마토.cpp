// [7576] 토마토 : https://www.acmicpc.net/problem/7576
#include <cstdio>
#include <queue>
using namespace std;

//m: 상자의 가로 칸 개수
//n: 상자의 세로 칸 개수
int m, n;
int map[1001][1001];
//{행, 열}
queue<pair<int, int>> q;

int dirX[] = {0, 0, -1, +1};
int dirY[] = {-1, +1, 0, 0};

bool check() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(map[i][j] == 0) return false;
		}
	}
	return true;
}
void bfs() {
	//ans: 토마토가 모두 익는 데 걸리는 시간
	int ans = -1;
	//하루동안 size개 만큼 익는다.
	int size = q.size();
	while(!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nextRow = row + dirY[i];
			int nextCol = col + dirX[i];
			if(nextCol>=0 && nextCol<m && nextRow>=0 && nextRow<n) {
				if(map[nextRow][nextCol] != -1 && map[nextRow][nextCol] != 2) {
				    //방문했음을 의미. visit 배열로 메모리를 중복해 사용하지 않기 위함
		            map[nextRow][nextCol] = 2;	
					q.push({nextRow, nextCol});
				}
			}
		}
		//하루동안 익은 토마토를 모두 확인했으면 다시 큐의 크기를 대입하고 시간+1
		if(--size == 0) { size = q.size(); ans++; }
	}
	//0인 칸이 존재하면 -1 출력, 그렇지 않으면 시간 출력
	if(check()) printf("%d", ans);
	else printf("-1");
}
int main() {
	scanf("%d %d", &m, &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if(map[i][j]==1) { map[i][j] = 2; q.push({i, j}); }
		}
	}
	bfs();
	return 0;
}