// [15683] 감시 : https://www.acmicpc.net/problem/15683
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

//h, w: 맵의 높이, 너비
//y, x: cctv의 위치
int h, w, y, x, ans = 65;
int map[8][8];
bool visit[8][8];
vector<pair<int, int>> camera;	//카메라 좌표 저장
int camDir[8];	//카메라 방향 저장

int mini(int a, int b) { return (a < b) ? a : b; }
//카메라(y,x)로부터 오른쪽으로 감시할 수 있는 칸이면 visit을 true로 바꾼다
void changeRight() {
	for(int i = x+1; i < w; i++) {
		//벽이면 break, 다른 카메라가 위치한다면 continue
		if(map[y][i] == 6) break;
		if(map[y][i]) continue;
		else visit[y][i] = true;
	}
}
void changeLeft() {
	for(int i = x-1; i >= 0; i--) {
		if(map[y][i] == 6) break;
		if(map[y][i]) continue;
		else visit[y][i] = true;
	}
}
void changeUp() {
	for(int i = y-1; i >= 0; i--) {
		if(map[i][x] == 6) break;
		if(map[i][x]) continue;
		else visit[i][x] = true;
	}
}
void changeDown() {
	for(int i = y+1; i < h; i++) {
		if(map[i][x] == 6) break;
		if(map[i][x]) continue;
		else visit[i][x] = true;
	}
}
void solve(int cnt) {
	//카메라 수만큼 모두 순회했으면 각 카메라의 방향 camDir를 참고해 볼 수 있는 칸을 표시하고
	//표시하지 않은 칸의 수를 센다
    if(cnt+1 >= camera.size()) {
    	//visit 초기화
        memset(visit, false, sizeof(visit));
        for(int i = 0; i < camera.size(); i++) {
            y = camera[i].first; 
            x = camera[i].second;
            switch(map[y][x]) {
                case 1:
                	//0~3 순서대로 right, down, left, up
                    switch(camDir[i]) {
                        case 0:
                            changeRight(); break;
                        case 1:
                            changeDown(); break;
                        case 2:
                            changeLeft(); break;
                        case 3:
                            changeUp(); break;
                    }
                    break;
                case 2:
                    switch(camDir[i]) {
                        case 0:
                        case 2:
                            changeRight(); changeLeft(); break;
                        case 1:
                        case 3:
                            changeUp(); changeDown(); break;
                    }
                    break;
                case 3:
                    switch(camDir[i]) {
                        case 0:
                            changeUp(); changeRight(); break;
                        case 1:
                            changeRight(); changeDown(); break;
                        case 2:
                            changeDown(); changeLeft(); break;
                        case 3:
                            changeLeft(); changeUp(); break;
                    }
                    break;
                case 4:
                    switch(camDir[i]) {
                        case 0:
                            changeUp(); changeRight(); changeDown(); break;
                        case 1:
                            changeRight(); changeDown(); changeLeft(); break;
                        case 2:
                            changeDown(); changeLeft(); changeUp(); break;
                        case 3:
                            changeLeft(); changeUp(); changeRight(); break;
                    }
                    break;
                case 5:
                    changeRight(); changeDown(); changeLeft(); changeUp();
                    break;
            }
        }
        //0 개수 센다
        int cnt = 0;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(!visit[i][j] && !map[i][j])
                    cnt++;
            }
        }
        //ans와 비교해서 작은값 취한다.
        ans = min(ans, cnt);
        return;
    }
    for(int i = 0; i < 4; i++) {
    	//방향 i를 camDir에 저장
        camDir[cnt+1] = i;
        solve(cnt+1);
    }
}
int main() {
    int cnt = 0;
	scanf("%d %d", &h, &w);
	for(int i = 0 ; i < h; i ++) {
		for(int j = 0; j < w; j++) {
			scanf("%d", &map[i][j]);
			if(map[i][j] != 0) {
			    if(map[i][j] != 6)
			        camera.push_back({i, j});
			    cnt++;
			}
		}
	}
	for(int i = 0; i < 4; i++) {
	    camDir[0] = i;
	    solve(0);
	}
	printf("%d", ans);
	return 0;
}