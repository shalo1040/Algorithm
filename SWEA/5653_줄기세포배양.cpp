// [5653] 줄기세포배양 : https://swexpertacademy.com/main/solvingProblem/solvingProblem.do
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

typedef struct {
    int time, life, y, x;
} Info;

//우선순위 큐에서의 Info 비교 연산자 오버로딩
//시간 적은 순, 생명력 큰 순
bool operator<(Info a, Info b) {
    if(a.time == b.time)
        return a.life < b.life;
    else
        return a.time > b.time;
}
const int MAX = 350, START = 150;
int T, h, w, K;
int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int solve(vector<vector<int>> &map, priority_queue<Info> &pq) {
    for(int time = 1; time < K; time++) {
        while(!pq.empty() && pq.top().time == time) {
            Info cell = pq.top();
            pq.pop();
            //죽은 줄기세포
            if(cell.life == 100) continue;
            for(int i = 0 ; i < 4; i++) {
                int ny = cell.y + dir[i][0];
                int nx = cell.x + dir[i][1];
                if(map[ny][nx]) continue;
                map[ny][nx] = cell.life;
                pq.push({time+cell.life+1, cell.life, ny, nx});
            }
            cell.time = time+cell.life-1;
            cell.life = 100;
            pq.push(cell);
        }
    }
    //비활성화 + 활성화 상태의 줄기세포
    return pq.size();
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; testcase++) {
        vector<vector<int>> map(MAX, vector<int>(MAX));
        priority_queue<Info> pq;
        scanf("%d %d %d", &h, &w, &K);
        for(int i = START; i < START + h; i++) {
            for(int j = START; j < START + w; j++) {
                scanf("%d", &map[i][j]);
                if(map[i][j]) pq.push({map[i][j], map[i][j], i, j});
            }
        }
        printf("#%d %d\n", testcase, solve(map, pq));
    }
    return 0;
}