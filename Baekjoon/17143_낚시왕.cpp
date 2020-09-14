// [17143] 낚시왕 : https://www.acmicpc.net/problem/17143
#include <cstdio>

typedef struct {
	int v, d, z;
} Shark;

//H: 행, W: 열
//M: 상어의 수
int H, W, M, ans;
Shark map[101][101], tmp[101][101];

int dir[][2] = { {0,0}, {-1,0}, {1,0}, {0,1}, {0,-1} };

int main() {
	scanf("%d %d %d", &H, &W, &M);
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
		map[y][x] = {v, d, z};
	}
	int fisherX = 0;
	while(fisherX != W) {
		//1. 사람이 오른쪽으로 한 칸 이동한다
		fisherX++;
		//2. 현재 위치한 열에서 가장 가까운 상어를 잡는다
		for(int j = 1; j <= H; j++) {
			if(map[j][fisherX].z != 0) {
				ans += map[j][fisherX].z;
				map[j][fisherX] = {0, 0, 0};
				break;
			}
		}
		//3-1. 상어 이동
		for(int i = 1; i <= H; i++) {
		    for(int j = 1; j <= W; j++)
		        tmp[i][j] = {0, 0, 0};
		}
		for(int i = 1; i <= H; i++) {
		    for(int j = 1; j <= W; j++) {
		        if(map[i][j].z == 0) continue;
		        Shark s = map[i][j];
		        int newY = i, newX = j;
		        for(int k = 0; k < s.v; k++) {
		            newY += dir[s.d][0];
		            newX += dir[s.d][1];
		            //벽에 닿으면 반대 방향으로 이동
		            if(newY<=0 || newY>H || newX<=0 || newX>W) {
    		            s.d = (s.d%2 == 0) ? s.d-1 : s.d+1;
    		            newY += dir[s.d][0]*2;
    		            newX += dir[s.d][1]*2;
    		        }
		        }
		        //3-2. 같은 칸에 여러 마리의 상어가 존재하면 가장 큰 상어만 살아남는다
		        if(tmp[newY][newX].z < s.z)
		            tmp[newY][newX] = s;
		    }
		}
		for(int i = 1; i <= H; i++) {
		    for(int j = 1; j <= W; j++)
		        map[i][j] = tmp[i][j];
		}
	}
	printf("%d", ans);
	return 0;
}