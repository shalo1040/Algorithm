#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

typedef struct {
    int y, x, d, k;
} Bomb;

int T, N;
int map[4002][4002];

//상(0), 하(1), 좌(2), 우(3)
int dir[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int solve(queue<Bomb> &q) {
    int sum = 0;
    while(1) {
        //원자가 폭발할 위치를 담을 벡터
        vector<pair<int, int>> pos;
        int size = q.size();
        //남은 원자들이 0개 또는 1개이면 리턴
        if(size < 2) return sum;
        //0.5초마다 1칸, 1초마다 2칸씩 이동
        for(int i = 0; i < size; i++) {
            Bomb b = q.front();
            q.pop();
            //기존에 있던 자리에 더이상 존재하지 않으므로 -1
            map[b.y][b.x]--;
            //1칸(문제에서 0.5칸) 이동
            b.y += dir[b.d][0];
            b.x += dir[b.d][1];
            //범위를 벗어나면 큐에 넣지 않고 continue
            if(b.y >= 4002 || b.y < 0 || b.x >= 4002 || b.x < 0) continue;
            map[b.y][b.x]++;
            //새 위치에서의 값이 2가되면 pos에 넣어준다.
            //(2라는 값에 아직 이동하지 않은 원자가 있을 수 있으므로 확인 필요)
            if(map[b.y][b.x] == 2) {
                pos.push_back({b.y, b.x});
                sum += b.k;
            } else q.push(b);
        }
        for(int i = 0; i < pos.size(); i++) {
            //확실히 2개 이상이 존재하는지 여부 검사
            if(map[pos[i].first][pos[i].second] < 2) continue;
            //큐에 있는 원자 중 x,y 좌표가 pos의 좌표와 같다면 터뜨린다.
            size = q.size();
            for(int h = 0; h < size; h++) {
                Bomb b = q.front();
                q.pop();
                if(b.y == pos[i].first && b.x == pos[i].second) sum += b.k;
                else q.push(b);
            }
        }
    }
    return sum;
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; testcase++) {
        scanf("%d", &N);
        memset(map, 0, sizeof(map));
		queue<Bomb> q;
        for(int i = 0; i < N; i++) {
            int y, x, d, k;
            scanf("%d %d %d %d", &x, &y, &d, &k);
            //문제에서의 y 방향이 map의 인덱스와 반대이므로 d를 반전시켜준다.
            if(d==0) d = 1;
            else if(d==1) d = 0;
            q.push({(y+1000)*2, (x+1000)*2, d, k});
        }
        printf("#%d %d\n", testcase, solve(q));
    }
    return 0;
}