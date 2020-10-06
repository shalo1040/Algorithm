// [19238] 스타트 택시 : https://www.acmicpc.net/problem/19238
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef struct {
	int y, x;
} Pos;

typedef struct {
	Pos start, end;
	bool arrived;	//목적지 도착 여부
} Guest;

int n, m, gas;
Pos taxi;
vector<vector<int>> map;	//활동 지역 정보
vector<Guest> guest;	//손님의 출발/도착 지점
vector<int> dist;		//택시와 손님 간 거리 저장

int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

//모든 승객을 이동시켰는지 여부 반환
bool isFinished() {
    for(Guest g : guest) {
        if(!g.arrived) return false;
    }
	return true;
}
//손님까지의 거리 계산
void getDist() {
	vector<vector<bool>> visit(n+1, vector<bool>(n+1, false));
	queue<pair<Pos, int>> q;	//{위치, 이동 횟수}
	q.push({{taxi.y, taxi.x}, 0});
	visit[taxi.y][taxi.x] = 1;
	while(!q.empty()) {
		int y = q.front().first.y;
		int x = q.front().first.x;
		int cnt = q.front().second;
		q.pop();
		for(int i = 0; i < guest.size(); i++) {
			if(guest[i].arrived || dist[i] > 0) continue;
			if(guest[i].start.y==y && guest[i].start.x==x) {
				dist[i] = cnt;
				break;
			}
		}
		for(int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];
			if(ny<=0 || ny>n || nx<=0 || nx>n || visit[ny][nx] || map[ny][nx]) continue;
			visit[ny][nx] = true;
			q.push({{ny,nx},cnt+1});
		}
	}
}
int moveGuest(int idx) {
	vector<vector<bool>> visit(n+1, vector<bool>(n+1, false));
	queue<pair<Pos, int>> q;
	q.push({{guest[idx].start.y, guest[idx].start.x}, 0});
	visit[guest[idx].start.y][guest[idx].start.x] = true;
	while(!q.empty()) {
		int y = q.front().first.y;
		int x = q.front().first.x;
		int cnt = q.front().second;
		q.pop();
		if(cnt > gas-dist[idx]) return -1;      //이동 도중 연료가 바닥나면 -1 반환
		if(y==guest[idx].end.y && x==guest[idx].end.x) return cnt;	//도착
		for(int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];
			if(ny<=0 || ny>n || nx<=0 || nx>n || visit[ny][nx] || map[ny][nx]) continue;
			visit[ny][nx] = true;
			q.push({{ny,nx},cnt+1});
		}
	}
	return -1;  //목적지에 가지 못한 경우
}
int solve() {
	while(1) {
		//모든 손님을 이동시켰으면 남은 연료의 양 출력
		if(isFinished()) break;
		dist = vector<int>(m,-1);
		//택시와 손님 간 거리 계산
		getDist();
		//손님에게 갈 수 없는 경우가 있으면 -1 반환
		for(int i = 0; i < dist.size(); i++) {
		    if(!guest[i].arrived && dist[i] == -1) return -1;
		}
		//거리가 가장 가깝고 행과 열이 작은 손님 찾기
		int min;
		for(int i = 0; i < dist.size(); i++) {
		    if(guest[i].arrived) continue;
		    min = i; break;
		}
		for(int i = min+1; i < dist.size(); i++) {
		    if(guest[i].arrived) continue;
			if(dist[min] > dist[i])		//거리가 가까우면 min
				min = i;
			else if(dist[min] == dist[i]) {		//거리가 같을 때 행이 작으면 min
				if(guest[min].start.y > guest[i].start.y)
					min = i;
				else if(guest[min].start.y == guest[i].start.y) {	//행도 같을 때 열이 작으면 min
					if(guest[min].start.x > guest[i].start.x)
						min = i;
				}
			}
		}
		if(dist[min] > gas) return -1;      //가는 도중 연료가 바닥나면 -1 반환
		int distToEnd = moveGuest(min);
		if(distToEnd == -1) return -1;      //가는 도중 연료가 바닥나거나 갈 수 없는 도착지인 경우 -1 반환
		gas += distToEnd - dist[min];
		//손님 도착 표시
		guest[min].arrived = true;
		//택시 위치
		taxi = guest[min].end;
	}
	return gas;
}
int main() {
	scanf("%d %d %d", &n, &m, &gas);
	map = vector<vector<int>>(n+1,vector<int>(n+1,0));
	//활동 영역
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	}
	//택시의 출발 지점
	scanf("%d %d", &taxi.y, &taxi.x);
	//승객의 출발 지점 및 목적 지점
	for(int i = 0; i < m; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		guest.push_back({a,b,c,d,false});
	}
	printf("%d", solve());
	return 0;
}