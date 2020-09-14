// [17143] 낚시왕 : https://www.acmicpc.net/problem/17143
#include <cstdio>
#include <queue>
#include <unordered_map>
using namespace std;

typedef struct {
	int id, y, x, v, d, z;
} Shark;

//H: 행, W: 열
//M: 상어의 수
int H, W, M, ans;
unordered_map<int, Shark> map;

int dir[][2] = { {0,0}, {-1,0}, {1,0}, {0,1}, {0,-1} };

int main() {
	scanf("%d %d %d", &H, &W, &M);
	priority_queue<pair<int, int>> pq[H+1][W+1];
	for(int i = 0; i < M; i++) {
		int y, x, v, d, z;
		scanf("%d %d %d %d %d", &y, &x, &v, &d, &z);
		//반복해서 몇 바퀴를 도는 경우 시간 효율성을 위해 (바퀴 수)*(한 바퀴의 칸 수)를 뺀다
		switch(d) {
			case 1:
			case 2:
				if(v >= (H-1)*2) 
					v %= (H-1)*2;
				break;
			case 3:
			case 4:
				if(v >= (W-1)*2)
					v %= (W-1)*2;
				break;
		}
		map[i+1] = {i+1, y, x, v, d, z};
		pq[y][x].push({-z, i+1});
	}
	int fisherX = 0;
	while(fisherX != W) {
		//1. 사람이 오른쪽으로 한 칸 이동한다
		fisherX++;
		//2. 현재 위치한 열에서 가장 가까운 상어를 잡는다
		for(int j = 1; j <= H; j++) {
			if(pq[j][fisherX].size()) {
				ans += -pq[j][fisherX].top().first;
				map.erase(pq[j][fisherX].top().second);
				pq[j][fisherX].pop();
				break;
			}
		}
		//3-1. 상어 이동
		for(int i = 1; i <= H; i++) {
		    for(int j = 1; j <= W; j++) {
		        while(!pq[i][j].empty())
		            pq[i][j].pop();
		    }
		}
		for(int i = 1; i <= M; i++) {
		    if(map.find(i) == map.end()) continue;
		    Shark s = map[i];
		    int newY = s.y, newX = s.x;
		    for(int j = 0; j < s.v; j++) {
		        newY += dir[s.d][0];
		        newX += dir[s.d][1];
				//벽에 닿으면 반대 방향으로 이동
		        if(newY<=0 || newY>H || newX<=0 || newX>W) {
		            s.d = (s.d%2 == 0) ? s.d-1 : s.d+1;
		            newY += dir[s.d][0]*2;
		            newX += dir[s.d][1]*2;
		        }
		    }
		    pq[newY][newX].push({-s.z, s.id});
		    s.y = newY; s.x = newX;
		    map[s.id] = s;
		}
		//3-2. 같은 칸에 여러 마리의 상어가 존재하면 가장 큰 상어만 살아남는다
		for(int i = 1; i <= H; i++) {
			for(int j = 1; j <= W; j++) {
				//여러 마리가 존재하면 큐의 마지막에 가장 큰 상어가 존재
				while(pq[i][j].size() > 1) {
				    map.erase(pq[i][j].top().second);
					pq[i][j].pop();
				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}