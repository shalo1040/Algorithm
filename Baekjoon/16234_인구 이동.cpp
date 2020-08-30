// [16234] 인구 이동 : https://www.acmicpc.net/problem/16234
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define MAX 51

int n, L, R;
int ppl[MAX][MAX];	//각 지역별 인구수
bool visit[MAX][MAX];

struct Pos {
	int y, x;
};

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//절댓값 반환
int abs(int a) { return (a<0) ? -a : a; }

//하나의 영역으로 지역 묶는다
void bfs(int startY, int startX) {
    int sum = 0, total = 0;
    queue<Pos> q, unionQ;
    q.push({startY, startX});
    unionQ.push({startY, startX});
    visit[startY][startX] = true;
    while(!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        sum += ppl[y][x];
        total++;
        for(int i = 0; i < 4; i++) {
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];
            if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
            if(visit[ny][nx]) continue;
            int diff = abs(ppl[y][x] - ppl[ny][nx]);
            if(diff >= L && diff <= R) {
                visit[ny][nx] = true;
                q.push({ny, nx});
                unionQ.push({ny, nx});
            }
        }
    }
    //하나의 영역(union)에 result 대입
    int result = sum / total;
    while(!unionQ.empty()) {
        Pos p = unionQ.front();
        unionQ.pop();
        ppl[p.y][p.x] = result;
    }
}
//(y,x)와 인접한 곳에 하나의 영역으로 묶을 수 있는지 여부 반환
bool isExist(int y, int x) {
    for(int i = 0; i < 4; i++) {
        int ny = y+dir[i][0];
        int nx = x+dir[i][1];
        if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
        int diff = abs(ppl[y][x] - ppl[ny][nx]);
        if(diff >= L && diff <= R) return true;
    }
    return false;
}
//인구 이동이 가능한지 여부 반환
bool check() {
    bool flag = false;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visit[i][j] && isExist(i, j)) {
                bfs(i, j);
                flag = true;
            }
        }
    }
    return flag;
}
int main() {
	scanf("%d %d %d", &n, &L, &R);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			scanf("%d", &ppl[i][j]);
	}
	int ans = 0;
	while(check()) {
		ans++;
        memset(visit, false, sizeof(visit));
	}
    printf("%d", ans);
	return 0;
}

/*
//아래는 dfs로 푼 코드

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAX 51

int n, L, R;
int sum, total;
int ppl[MAX][MAX];
bool visit[MAX][MAX];
vector<pair<int, int>> list;

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int abs(int a) { return (a < 0) ? -a : a; }

void dfs(int y, int x) {
    for(int i = 0; i < 4; i++) {
        int ny = y+dir[i][0];
        int nx = x+dir[i][1];
        if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
        if(visit[ny][nx]) continue;
        int diff = abs(ppl[y][x] - ppl[ny][nx]);
        if(diff >= L && diff <= R) {
            visit[ny][nx] = true;
            sum += ppl[ny][nx];
            total++;
            list.push_back({ny, nx});
            dfs(ny, nx);
        }
    }
}
bool isExist(int y, int x) {
    for(int i = 0; i < 4; i++) {
        int ny = y+dir[i][0];
        int nx = x+dir[i][1];
        if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
        int diff = abs(ppl[y][x] - ppl[ny][nx]);
        if(diff >= L && diff <= R) return true;
    }
    return false;
}
bool check() {
    bool flag = false;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visit[i][j] && isExist(i, j)) {
                visit[i][j] = true;
                sum = ppl[i][j];
                total = 1;
                list.clear();
                list.push_back({i, j});
                dfs(i, j);
                for(int k = 0; k < list.size(); k++) {
                    int y = list[k].first;
                    int x = list[k].second;
                    ppl[y][x] = sum / total;
                }
                flag = true;
            }
        }
    }
    return flag;
}
int main() {
    scanf("%d %d %d", &n, &L, &R);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            scanf("%d", &ppl[i][j]);
    }
    int ans = 0;
    while(check()) {
        ans++;
        memset(visit, false, sizeof(visit));
    }
    printf("%d", ans);
    return 0;
}
*/