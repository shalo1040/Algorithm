// [3197] 백조의 호수 : https://www.acmicpc.net/problem/3197
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

//h: 높이, w: 너비
int h, w, ans;
//백조 두 마리의 위치
vector<pair<int, int>> pos;
//waterQ: 현재 물인 곳
//swanQ: 백조 한 마리가 갈 수 있는 영역
queue<pair<int, int>> waterQ, swanQ;
char map[1501][1501];
bool visit[1501][1501];

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//백조 두 마리가 만날 수 있는지 여부 반환
//백조 한 마리의 좌표를 큐에 넣고 순회
bool check() {
    //nextQ: 다음 날 물이 될 곳의 위치(백조 한 마리가 갈 수 있는 확장된 영역)
    queue<pair<int, int>> nextQ;
    while(!swanQ.empty()) {
        int y = swanQ.front().first;
        int x = swanQ.front().second;
        swanQ.pop();
        if(y == pos[1].first && x == pos[1].second) return true;
        for(int i = 0; i < 4; i++) {
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];
            if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
            if(!visit[ny][nx]) {
                //만약 X인 곳을 만나게 되면 다음 날 물이 될 곳이므로 nextQ에 넣어준다.
                if(map[ny][nx] == 'X')
                    nextQ.push({ny, nx});
                else swanQ.push({ny, nx});
                visit[ny][nx] = true;
            }
        }
    }
    swanQ = nextQ;
    return false;
}
//물과 인접한 빙하를 녹인다.
void solve() {
    int size = waterQ.size();
    while(size--) {
        int y = waterQ.front().first;
        int x = waterQ.front().second;
        waterQ.pop();
        for(int i = 0; i < 4; i++) {
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];
            if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
            //waterQ에는 현재 물인 곳의 위치가 들어있고
            //순회 도중 빙하(X)를 만나면 물(.)로 바꿔주고 waterQ에 push
            if(map[ny][nx] == 'X') {
                map[ny][nx] = '.';
                waterQ.push({ny, nx});
            }
        }
    }
}
int main() {
    scanf("%d %d", &h, &w);
    for(int i = 0; i < h; i++) {
        scanf("%s", &map[i]);
        for(int j = 0; j < w; j++) {
            switch(map[i][j]) {
                //오리(L)이거나 물(.)이면 waterQ에 넣어준다.
                case 'L':
                    pos.push_back({i, j});
                case '.':
                    waterQ.push({i, j}); break;
            }
        }
    }
    swanQ.push(pos[0]);
    visit[pos[0].first][pos[0].second] = true;
    while(!check()) {
        solve();
        ans++;
    }
    printf("%d", ans);
}_