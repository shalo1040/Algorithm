// [1926] 그림 : https://www.acmicpc.net/problem/1926
#include <cstdio>
#include <queue>
using namespace std;

int w, h, count, maxArea;
bool map[501][501], visit[501][501];
int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//bfs
void solve(int y, int x) {
    int area = 1;
    queue<pair<int, int>> q;
    q.push({y, x});
    visit[y][x] = true;
    while(!q.empty()) {
        int yy = q.front().first;
        int xx = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int ny = yy + dir[i][0];
            int nx = xx + dir[i][1];
            if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
            if(!visit[ny][nx] && map[ny][nx]) {
                visit[ny][nx] = true;
                q.push({ny, nx});
                area++;
            }
        }
    }
    if(area > maxArea) maxArea = area;
}
int main() {
    scanf("%d %d", &h, &w);
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            scanf("%d", &map[i][j]);
    }
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(map[i][j] && !visit[i][j]) {
                solve(i, j);
                count++;
            }
        }
    }
    printf("%d\n%d", count, maxArea);
    return 0;
}