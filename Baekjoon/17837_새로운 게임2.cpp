// [17837] 새로운 게임2 : https://www.acmicpc.net/problem/17837
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Info {
	int y, x, direction;
	Info() { y = 0; x = 0; direction = 0; };
	void setInfo(int yy, int xx, int d) { y = yy; x = xx; direction = d; }
	void setInfo(int yy, int xx) { y = yy; x = xx; }
} Info;

int n, k;
bool done = false;
int map[13][13];
vector<int> board[13][13];
Info info[13];

int dir[][2] = {{0,0}, {0,1}, {0,-1}, {-1,0}, {1,0}};

void white(int y, int x, int ny, int nx, int d, int knight) {
    vector<int> &cur = board[y][x];
    vector<int> &next = board[ny][nx];
    //cur에서의 말의 위치
    auto s = find(cur.begin(), cur.end(), knight);
    //s~cur.end()까지 next에 넣고 cur에서 erase
    for(auto i = s; i != cur.end(); ++i) {
        info[*i].setInfo(ny, nx);
        next.push_back(*i);
    }
    cur.erase(s, cur.end());
    if(next.size() >= 4) done = true;	//게임 종료 조건
}
void red(int y, int x, int ny, int nx, int d, int knight) {
    vector<int> &cur = board[y][x];
    vector<int> &next = board[ny][nx];
    //cur에서의 말의 위치
    auto s = find(cur.begin(), cur.end(), knight);
    //순서 바꾼다
    reverse(s, cur.end());
    //s~cur.end()까지 next에 넣고 cur에서 erase
    for(auto i = s; i != cur.end(); ++i) {
        info[*i].setInfo(ny, nx);
        next.push_back(*i);
    }
    cur.erase(s, cur.end());
    if(next.size() >= 4) done = true;	//게임 종료 조건
}
void blue(int y, int x, int d, int knight) {
	(d%2) ? d++ : d--;	//방향 반대로 바꾼다
	info[knight].setInfo(y, x, d);
	int ny = y + dir[d][0];
	int nx = x + dir[d][1];
	//전진할 위치가 벽이거나 파란색 칸이면 그자리에 멈춤
	if(ny<=0 || ny>n || nx<=0 || nx>n || map[ny][nx]==2) return;
	if(map[ny][nx] == 0) white(y, x, ny, nx, d, knight);		//흰색 칸
	else red(y, x, ny, nx, d, knight);			//빨간색 칸
}
int solve() {
	for(int turn = 1; turn <= 1000; ++turn) {
		for(int i = 1; i <= k; i++) {
			//현재 말의 정보
			int y = info[i].y;
			int x = info[i].x;
			int d = info[i].direction;
			//이동할 위치
			int ny = y + dir[d][0];
			int nx = x + dir[d][1];
			//벽이거나 파란색 칸이면 방향 바꾸고 전진
			if(ny<=0 || ny>n || nx<=0 || nx>n || map[ny][nx]==2)
				blue(y, x, d, i);
			else if(!map[ny][nx]) white(y, x, ny, nx, d, i);
			else red(y, x, ny, nx, d, i);
			if(done) return turn;	//게임 종료
		}
	}
	return -1;
}
int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	}
	for(int i = 1; i <= k; i++) {
		int y, x, d;
		scanf("%d %d %d", &y, &x, &d);
		info[i].setInfo(y, x, d);
		board[y][x].push_back(i);
	}
	printf("%d", solve());
	return 0;
}