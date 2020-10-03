// [19236] 청소년 상어 : https://www.acmicpc.net/problem/19236
#include <cstdio>
#include <vector>
using namespace std;

typedef struct {
	int dir, x, y;
	bool alive;
	void setPos(int xx, int yy) { x=xx; y=yy; }
	void setFish(int d, int xx, int yy) { dir=d; x=xx; y=yy; }
} Fish;

int ans;
vector<vector<int>> map(4, vector<int>(4,0));
vector<Fish> fish(17);
int dir[][2] = {{0,0},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

int max(int a, int b) { return (a > b) ? a : b; }
void moveFish(int sharkX, int sharkY) {
    for(int i = 1; i <= 16; i++) {
        if(fish[i].alive == false) continue;
        int d = fish[i].dir;
        int x = fish[i].x;
        int y = fish[i].y;
        int cnt = 0;
        while(cnt < 8) {
            int nextX = x + dir[d][0];
            int nextY = y + dir[d][1];
			//상어가 있거나 범위를 벗어나면 반시계 방향으로 45도 회전
            if((nextX==sharkX && nextY==sharkY) || nextX<0 || nextX>=4 || nextY<0 || nextY>=4) {
                d = (d==8) ? 1 : d+1;
                cnt++;
                continue;
            }
			//물고기 이동
            int tmp = map[nextX][nextY];
            map[nextX][nextY] = map[x][y];
            map[x][y] = tmp;
            fish[tmp].setPos(x,y);
            fish[i].setFish(d,nextX,nextY);
            break;
        }
    }
}
void solve(int sharkX, int sharkY, int di, int sum) {
	vector<vector<int>> tmpMap = map;
	vector<Fish> tmpFish = fish;
	//물고기 이동
	moveFish(sharkX, sharkY);
	//상어 이동
	bool isPossible = false;
	int nextX = sharkX, nextY = sharkY;
	for(int i = 0; i < 3; i++) {
		nextX += dir[di][0];
		nextY += dir[di][1];
		//범위를 벗어나거나 물고기가 없으면 가지 않음
		if(nextX<0 || nextX>=4 || nextY<0 || nextY>=4 || !map[nextX][nextY]) continue;
		int d = fish[map[nextX][nextY]].dir;
		int n = map[nextX][nextY];
		map[nextX][nextY] = 0;
		fish[n].alive = false;
		solve(nextX, nextY, d, sum+n);	//이동
		map[nextX][nextY] = n;
		fish[n].alive = true;
		isPossible = true;
	}
	if(!isPossible)
		ans = max(ans, sum);
	//물고기 전 단계로 이동
	map = tmpMap;
	fish = tmpFish;
}
int main() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			int a, b;
			scanf("%d %d", &a, &b);
			fish[a] = {b,i,j,true};
			map[i][j] = a;
		}
	}
	//상어 입장
	int d = fish[map[0][0]].dir;
	int n = map[0][0];
	map[0][0] = 0;
	fish[n].alive = false;
	solve(0,0,d,n);
	printf("%d", ans);
	return 0;
}