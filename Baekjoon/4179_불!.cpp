// [4179] 불! : https://www.acmicpc.net/problem/4179-
#include <cstdio>
#include <queue>
using namespace std;

int w, h, ans;
int startY, startX;     //지훈이의 처음 위치
char map[1001][1001];
queue<pair<int, int>> fire;     //번지는 불의 위치

int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//bfs
bool solve(int y, int x) {
    bool visit[h][w];
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            visit[i][j] = false;
    }
    queue<pair<pair<int, int>, int>> q;
    q.push({{y, x}, 0});
    visit[y][x] = true;
    while(!q.empty()) {
        //지훈이가 움직인다
        int size = q.size();
        while(size--) {
            int yy = q.front().first.first;
            int xx = q.front().first.second;
            int cnt = q.front().second;     //움직인 시간
            q.pop();
            if(map[yy][xx] == 'F') continue;    //불이 있는 곳에 가지 않음
            //가장자리에 다다르면 리턴
            if(yy==0 || yy==h-1 || xx==0 || xx==w-1) {ans = cnt+1; return true; }
            for(int i = 0; i < 4; i++) {
                int ny = yy + dir[i][0];
                int nx = xx + dir[i][1];
                if(!visit[ny][nx] && map[ny][nx] == '.') {
                    visit[ny][nx] = true;
                    q.push({{ny, nx}, cnt+1});
                    ans++;
                }
            }
        }
        //불이 번진다
        size = fire.size();
        while(size--) {
            int yy = fire.front().first;
            int xx = fire.front().second;
            fire.pop();
            for(int i = 0; i < 4; i++) {
                int ny = yy + dir[i][0];
                int nx = xx + dir[i][1];
                if(ny<0 || ny>=h || nx<0 || nx>=w || map[ny][nx] == '#' || map[ny][nx] == 'F') continue;
                fire.push({ny, nx});
                map[ny][nx] = 'F';
            }
        }
    }
    return false;
}
int main() {
    scanf("%d %d", &h, &w);
    for(int i = 0; i < h; i++) {
        scanf("%s", &map[i][0]);
        for(int j = 0; j < w; j++) {
            switch(map[i][j]) {
                case 'J':
                    startY = i;
                    startX = j;
                    break;
                case 'F':
                    fire.push({i, j});
                    break;
            }
        }
    }
    if(solve(startY, startX))
        printf("%d", ans);
    else printf("IMPOSSIBLE");
    return 0;
}