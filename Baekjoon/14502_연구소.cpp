// [14502] 연구소 : https://www.acmicpc.net/problem/14502
#include <cstdio>
#include <queue>
using namespace std;

/*
w, h: width, height
idx: virus 배열의 인덱스
walls: 벽의 개수
ans: 최대 빈칸의 개수
*/
int w, h, idx, walls, ans;
int map[8][8], virus[10][2];

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

void bfs() {
	// (빈칸의 수) = (전체 칸의 수) - (벽의 개수) - (새로 만든 벽의 개수) - (바이러스가 퍼진 칸의 수)
    int cnt = w*h - walls - 3;
    int tmp[h][w];
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            tmp[i][j] = map[i][j];
    }
	queue<pair<int, int>> q;
	for(int i = 0; i < idx; i++)
		q.push({virus[i][0], virus[i][1]});
	while(!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		cnt--;		//바이러스가 퍼진 칸이므로 빈칸의 수-1
		for(int i = 0; i < 4; i++) {
			int ny = y + dirY[i];
			int nx = x + dirX[i];
			if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
			if(tmp[ny][nx] == 0) {
				tmp[ny][nx] = 2;	//값 변경으로 visit 유무 효과
				q.push({ny, nx});
			}
		}
	}
	ans = (ans > cnt) ? ans : cnt;
}
//빈칸 중에서 3 칸을 고른 뒤 bfs() 실행
//중복된 조합은 건너뛰기 위해 이전에 만들어준 벽의 x, y 좌표를 매개변수로 전달
void makeWalls(int y, int x, int cnt) {
	if(cnt == 3) { bfs(); return; }
	for(int i = y; i < h; i++) {
		for(int j = x; j < w; j++) {
			if(map[i][j] == 0) {
				map[i][j] = 1;
				makeWalls(i, j, cnt + 1);
				map[i][j] = 0;
			}
		}
		x = 0;	//다음 행부터는 x열이 아닌 0열에서 시작
	}
}
int main() {
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			scanf("%d", &map[i][j]);
			if(map[i][j] == 1) walls++;
			else if(map[i][j] == 2) {
				virus[idx][0] = i;
				virus[idx++][1] = j;				
			}
		}
	}
	//(0, 0)부터 세울 3개의 벽 위치 탐색 시작
	makeWalls(0, 0, 0);
	printf("%d", ans);
	return 0;
}