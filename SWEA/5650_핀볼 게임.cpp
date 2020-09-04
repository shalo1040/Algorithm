//[5650] 핀볼 게임 : https://swexpertacademy.com/main/solvingProblem/solvingProblem.do
#include <cstdio>
#include <vector>
using namespace std;

int T, N;
vector<pair<int, int>> hole[5];
int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int max(int a, int b) { return (a > b) ? a : b; }
int solve(int y, int x, const vector<vector<int>> &map, int d) {
    int score = 0;
    int ny = y, nx = x;
    while(1) {
        //주어진 방향으로 이동
        ny += dir[d][0];
        nx += dir[d][1];
        
        //벽에 부딪히면 score+1, 방향 반대로
        if(ny<0 || ny>=N || nx<0 || nx>=N) {
            score++;
            d = (d%2) ? d-1 : d+1;
            continue;
        }
        
        //시작 지점이거나 블랙홀이면 score 리턴
        if(ny == y && nx == x) break;
        if(map[ny][nx] == -1) break;
        
        //map이 0이 아닐때까지 이동
        if(map[ny][nx] == 0) continue;
        
        //1~5: 블록, 6~10: 웜홀
        switch(map[ny][nx]) {
            //블록 -> score+1, 방향 알맞게 바꾼다
            case 1:
                score++;
                if(d==2) d = 0;
                else if(d==1) d = 3;
                else d = (d%2) ? d-1 : d+1;
                break;
            case 2:
                score++;
                if(d==1) d = 2;
                else if(d==3) d = 0;
                else d = (d%2) ? d-1 : d+1;
                break;
            case 3:
                score++;
                if(d==0) d = 2;
                else if(d==3) d = 1;
                else d = (d%2) ? d-1 : d+1;
                break;
            case 4:
                score++;
                if(d==0) d = 3;
                else if(d==2) d = 1;
                else d = (d%2) ? d-1 : d+1;
                break;
            case 5:
                score++;
                d = (d%2) ? d-1 : d+1; break;
            //웜홀 -> 해당 웜홀의 반대 좌표로 이동
            default:
                int idx = map[ny][nx] - 6;
                if(hole[idx][0].first == ny && hole[idx][0].second == nx) {
                    ny = hole[idx][1].first;
                    nx = hole[idx][1].second;
                } else {
                    ny = hole[idx][0].first;
                    nx = hole[idx][0].second;
                }
                break;
        }
    }
    return score;
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; testcase++) {
        scanf("%d", &N);
        //초기화
        vector<vector<int>> map(N, vector<int>(N));
        for(int i = 0; i < 5; i++) hole[i].clear();
        //입력
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                scanf("%d", &map[i][j]);
                if(map[i][j] > 5)
                    hole[map[i][j] - 6].push_back({i, j});
            }
        }
        //최댓값 찾기
        int ans = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(map[i][j]) continue;
                for(int d = 0; d < 4; d++)
                    ans = max(ans, solve(i, j, map, d));
            }
        }
        //출력
        printf("#%d %d\n", testcase, ans);
    }
    return 0;
}