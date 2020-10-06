// [19237] 어른 상어 : https://www.acmicpc.net/problem/19237
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef struct {
	int time, y, x;
} Time;

int n, m, k;
vector<vector<int>> smell, map(20, vector<int>(20,0));
vector<int> shark;
vector<pair<int, int>> again;	//갔던 곳으로 갔을 때 시간을 알맞게 갱신하기 위함
queue<Time> time;
queue<pair<int, int>> q;

int dir[][2] = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
vector<vector<vector<int>>> moveDir;	//상어별 이동 우선순위 저장

bool isNotValid(int y, int x) {
	return y<0 || y>=n || x<0 || x>=n;
}
int min(int a, int b) { return (a<b) ? a : b; }
void moveShark() {
	vector<vector<int>> nextMap(20, vector<int>(20,0));
	queue<pair<int, int>> newSmell;
	int size = q.size();
	while(size--) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		int num = map[y][x];
		bool flag = false;
		for(int i = 0; i < 4; i++) {
			int nextDir = moveDir[num][shark[num]][i];
			int ny = y + dir[nextDir][0];
			int nx = x + dir[nextDir][1];
			if(isNotValid(ny,nx)) continue;
			if(!smell[ny][nx]) {		//1. 아무 냄새 없는 칸
				shark[num] = nextDir;
				if(nextMap[ny][nx])
					nextMap[ny][nx] = min(nextMap[ny][nx], num);
				else {
					nextMap[ny][nx] = num;
					time.push({k+1, ny, nx});
					q.push({ny, nx});
					newSmell.push({ny, nx});
				}
				flag = true;
				break;
			}
		}
		//냄새가 없는 칸이 없으면 자신의 냄새가 있는 칸으로 이동
		if(!flag) {
			for(int i = 0; i < 4; i++) {
				int nextDir = moveDir[num][shark[num]][i];
				int ny = y + dir[nextDir][0];
				int nx = x + dir[nextDir][1];
				if(isNotValid(ny, nx)) continue;
				if(smell[ny][nx] == num) {
				    shark[num] = nextDir;
					nextMap[ny][nx] = num;
					again.push_back({ny, nx});
					q.push({ny, nx});
					break;
				}
			}
		}
	}
	while(!newSmell.empty()) {
	    int y = newSmell.front().first;
	    int x = newSmell.front().second;
	    newSmell.pop();
	    smell[y][x] = nextMap[y][x];
	}
	map = nextMap;
}
void decSmell() {
	int size = time.size();
	while(size--) {
		Time t = time.front(); time.pop();
		bool flag = false;
		//자신이 갔던 곳을 가게되면 큐에 정보가 중복되어 있으므로 again을 이용해 한번만 적용
		for(int i = 0; i < again.size(); i++) {
			if(t.y==again[i].first && t.x==again[i].second) {
				flag = true;
				time.push({k,t.y,t.x});
				break;
			}
		}
		if(flag) continue;
		t.time--;
		if(!t.time) smell[t.y][t.x] = 0;	//시간이 0이 되면 냄새를 없애줌
		else time.push(t);
	}
}
int solve() {
	int t = 0;
	while(1) {
		if(q.size() == 1) break;	//1번 상어만 남으면 시간 반환
		if(t >= 1000) return -1;
		moveShark();		//모든 상어 이동
		decSmell();		//냄새 유지 시간 감소
		again.clear();
		t++;
	}
	return t;
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	shark = vector<int>(m+1,0);
	moveDir = vector<vector<vector<int>>>(m+1,vector<vector<int>>(5,vector<int>(4,0)));
	//상어 위치
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			if(map[i][j]) {
				time.push({k,i,j});		//냄새가 유지되는 시간
				q.push({i,j});
			}
		}
	}
	smell = map;
	//상어 방향
	for(int i = 1; i <= m; i++)
	    scanf("%d", &shark[i]);
	//이동 우선순위
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= 4; j++) {
			for(int l = 0; l < 4; l++)
				scanf("%d", &moveDir[i][j][l]);
		}
	}
	printf("%d", solve());
	return 0;
}