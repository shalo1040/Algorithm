// [15685] 드래곤 커브 : https://www.acmicpc.net/problem/15685
#include <cstdio>
#include <vector>
using namespace std;

int n, x, y, d, g;
bool map[101][101];	//좌표
vector<int> dragon;	//드래곤커브의 방향 저장

int dir[][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}};

//드래곤 커브 규칙: dragon의 마지막 인덱스부터 0까지 해당 값을 1만큼 증가시켜 push_back한다.
void draw() {
    for(int i = dragon.size()-1; i >= 0; i--) {
        int d = (dragon[i]+1) % 4;	//0~3까지이므로 3일 경우 0을 가리킨다.
        y += dir[d][0];
        x += dir[d][1];
        map[y][x] = 1;
        dragon.push_back(d);
    }
}
//네 꼭짓점이 드래곤 커브가 지나는 정사각형의 개수 반환
int countDragon() {
    int cnt = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(map[i][j] && map[i][j+1] && map[i+1][j] && map[i+1][j+1])
                cnt++;
        }
    }
    return cnt;
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x, &y, &d, &g);
        dragon.clear();
        map[y][x] = 1;	//꼭짓점 표시
        y += dir[d][0];	//주어진 방향으로 이동하고 꼭짓점 표시
        x += dir[d][1];
        map[y][x] = 1;
        dragon.push_back(d);
        for(int j = 0; j < g; j++)
            draw();
    }
    printf("%d", countDragon());
    return 0;
}