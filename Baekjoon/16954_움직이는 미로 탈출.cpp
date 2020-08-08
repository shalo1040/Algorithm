// [16954] 움직이는 미로 탈출 : https://www.acmicpc.net/problem/16954
#include <cstdio>
#include <queue>
using namespace std;

//top: 가장 높은 벽의 y값
//top이 없다면 메모리와 시간이 훨씬 더 낭비된다.
int top = -1;
char map[8][9];

int dir[][2] = { {0,0}, {0,1}, {0,-1}, {1,0}, {1,1}, {1,-1}, {-1,0}, {-1,1}, {-1,-1} };

bool solve() {
	queue<pair<int, int>> q;
	q.push({7, 0});
	while(!q.empty()) {
	    //이동할 곳을 찾는 동안 map이 바뀌면 안되므로 큐의 크기동안 기다린다.
	    int size = q.size();
	    while(size--) {
    		int y = q.front().first;
    		int x = q.front().second;
    		q.pop();
    		//최종 목적지에 도착하면 true 값을 반환한다.
    		if(y==0 && x==7) return true;
    		//현재 존재하는 벽보다 높이 있으면(y값이 더 작으면) 언젠가는 목적지에 도착할 것이므로 true 리턴
    		if(y<top) return true;
    		//현재 위치의 상하좌우, 대각선을 살핀다.
    		for(int i = 0; i < 9; i++) {
    			int ny = y + dir[i][0];
    			int nx = x + dir[i][1];
    			//범위 이탈
    			if(ny<0 || ny>=8 || nx<0 || nx>=8) continue;
    			//벽
    			if(map[ny][nx] == '#') continue;
    			//갈 곳의 윗칸이 벽이면 벽이 내려와 이동할 수 없어지므로 이동하지 않는다.
    			if(ny-1>=0 && map[ny-1][nx] == '#') continue;
    			//벽이 없는 곳으로 이동
    			q.push({ny, nx});
    		}
	    }
	    //벽 내려오기
		for(int k = 7; k > 0; k--) {
			for(int l = 0; l < 8; l++) {
			    map[k][l] = map[k-1][l];
				map[k-1][l] = '.';
			}
		}
		top++;  //벽이 한 칸씩 아래로 내려갔으므로 top도 +1 해준다.
	}
	return false;
}
int main() {
	for(int i = 0; i < 8; i++) {
	    for(int j = 0; j < 8; j++) {
	        scanf(" %c", &map[i][j]);
	        if(top==-1 && map[i][j]=='#')
	            top = i;
	    }
	}
	printf("%d", solve());
	return 0;
}