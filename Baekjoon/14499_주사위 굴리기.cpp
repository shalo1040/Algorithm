// [14499] 주기위 굴리기 : https://www.acmicpc.net/problem/14499
#include <cstdio>

//h,w: 지도의 높이, 너비
//diceY, diceX: 주사위 위치
//k: 이동 명령 개수
int h, w, diceY, diceX, k;
int map[21][21], dice[4][3];	//map: 지도, dice: 주사위 전개도
int topY = 1, topX = 1, bottomY = 3, bottomX = 1;	//top, bottom x,y 인덱스값 고정

enum Direction {east = 1, west = 2, north = 3, south = 4};

//방향에 따라 주사위 전개도 값을 바꿔준다.
void solve(int dir) {
    int tmp;
	switch(dir) {
		//동쪽 또는 서쪽으로 이동할 때
		//dice[1][0], dice[1][1], dice[1][2], dice[3][1] 영향받는다.
		case east:
			//지도 범위를 넘어가면 명령 무시하고 함수 빠져나감
			if(diceX+1 >= w) return;
			diceX++;
			tmp = dice[1][2];
			for(int i = 2; i > 0; i--)
			    dice[1][i] = dice[1][i-1];
			dice[1][0] = dice[bottomY][bottomX];
			dice[bottomY][bottomX] = tmp;
			break;
		case west:
			if(diceX-1 < 0) return;
			diceX--;
			tmp = dice[1][0];
			for(int i = 0; i < 2; i++)
			    dice[1][i] = dice[1][i+1];
			dice[1][2] = dice[bottomY][bottomX];
			dice[bottomY][bottomX] = tmp;
			break;
		//북쪽 또는 남쪽으로 이동할 때
		//dice[0][0], dice[0][1], dice[0][2], dice[0][3] 영향 받는다.
		case north:
			if(diceY-1 < 0) return;
			diceY--;
			tmp = dice[0][1];
			for(int i = 0; i < 3; i++)
			    dice[i][1] = dice[i+1][1];
			dice[3][1] = tmp;
			break;
		case south:
			if(diceY+1 >= h) return;
			diceY++;
			tmp = dice[3][1];
			for(int i = 3; i > 0; i--)
			    dice[i][1] = dice[i-1][1];
			dice[0][1] = tmp;
			break;
	}
	//주사위가 위치한 지도의 칸이 0 값이면 주사위의 아랫면 값 복사
	if(map[diceY][diceX] == 0)
	    map[diceY][diceX] = dice[bottomY][bottomX];
	//지도에 0이 아닌 값이 있으면 주사위 아랫면에 복사 후 지도는 0으로 설정
    else {
        dice[bottomY][bottomX] = map[diceY][diceX];
        map[diceY][diceX] = 0;
    }
	printf("%d\n", dice[topY][topX]);
}
int main() {
	scanf("%d %d %d %d %d", &h, &w, &diceY, &diceX, &k);
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++)
			scanf("%d", &map[i][j]);
	}
	while(k--) {
		int dir;
		scanf("%d", &dir);
		solve(dir);
	}
	return 0;
}