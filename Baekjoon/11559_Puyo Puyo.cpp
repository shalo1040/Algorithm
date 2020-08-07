// [11559] Puyo Puyo : https://www.acmicpc.net/problem/11559
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int ans;
char map[12][7];

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

//연속해서 4개 이상의 Puyo가 붙어 있다면 모두 없애준다.
void remove(int y, int x) {
	int v2[12][6];
	memset(v2, 0, sizeof(v2));
	queue<pair<int, int>> q;
	q.push({y, x});
	v2[y][x] = 1;
	while(!q.empty()) {
		int yy = q.front().first;
		int xx = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int ny = yy + dirY[i];
			int nx = xx + dirX[i];
			if(ny<0 || ny>=12 || nx<0 || nx>=6) continue;
			if(map[ny][nx] == map[yy][xx] && !v2[ny][nx]) {
				v2[ny][nx] = 1;
				q.push({ny, nx});
			}
		}
		map[yy][xx] = '.';		//Puyo 없애기
	}
}
int checkPuyo(int y, int x) {
    int count = 1;
    int v[12][6];
    memset(v, 0, sizeof(v));
    queue<pair<int, int>> q;
    q.push({y, x});
    v[y][x] = 1;
    while(!q.empty()) {
        int yy = q.front().first;
        int xx = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int ny = yy + dirY[i];
            int nx = xx + dirX[i];
            if(ny<0 || ny>=12 || nx<0 || nx>=6) continue;
            if(map[ny][nx] == map[yy][xx] && !v[ny][nx]) {
                v[ny][nx] = 1;
                q.push({ny, nx});
                count++;
            }
        }
    }
    return count;
}
//터진 Puyo가 존재하면 true 리턴
bool bfs() {
	bool flag = false;
	int visit[12][6];
	memset(visit, 0, sizeof(visit));
	queue<pair<int, int>> q;
	q.push({0, 0});
	visit[0][0] = 1;
	while(!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int ny = y + dirY[i];
			int nx = x + dirX[i];
			if(ny<0 || ny>=12 || nx<0 || nx>=6) continue;
			if(!visit[ny][nx]) {
			    visit[ny][nx] = 1;
			    //map[ny][nx]가 문자라면 상하좌우에 같은 색의 개수를 checkPuyo()로 세기
			    //같은 색이 4개 이상이면 모두 '.'으로 지우고 계속해서 bfs 수행
			    //그렇지 않으면 큐에 넣고 bfs 이어감
			    if(map[ny][nx] != '.') {
			        if(checkPuyo(ny, nx) >= 4) {
			            remove(ny, nx);
			            flag = true;
			            continue;
			        }
			    }
			    q.push({ny, nx});
			}
		}
	}
	return flag;
}
//중력에 의해 떨어지는 Puyo 위치 정하기
void nextStage() {
	for(int j = 0; j < 6; j++) {
	    int gap = 0;
		for(int i = 11; i >= 0; i--) {
			if(map[i][j] == '.') gap++;
			else if(gap) {
				for(int k = i; k >= 0; k--) {
					map[k+gap][j] = map[k][j];
					map[k][j] = '.';	//Puyo의 원래 자리에 '.'로 비어있음을 표시
				}
				//문자를 찾은 위치로부터 gap 크기 만큼의 공간에 또 다른 공백이 있을 수 있으므로 j열 처음부터 다시 탐색
				i = 12;
				gap = 0;
			}
		}
	}
}
int main() {
	for(int i = 0; i < 12; i++)
		scanf("%s", &map[i]);
	while(bfs()) {
		ans++;
		nextStage();
	}
	printf("%d", ans);
	return 0;
}