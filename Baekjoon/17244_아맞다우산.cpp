// [17244] 아맞다우산 : https://www.acmicpc.net/problem/17244
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

/*
N: 가로 길이
M: 세로 길이
x, y: S의 x, y 좌표
numOfX: 챙겨야하는 물건의 개수(최대 5개)
time: 최소시간
*/
int N, M, x, y, numOfX, time;
char map[51][51];
int visit[51][51][1<<5];

int dirX[] = {-1, 1, 0, 0};
int dirY[] = {0, 0, -1, 1};

typedef struct {
    int y, x, time, check;
} Info;

void bfs() {
	queue<Info> q;
	q.push({y, x, time, 0});
	visit[y][x][0] = 1;
	while(!q.empty()) {
		y = q.front().y;
		x = q.front().x;
		time = q.front().time;
		int check = q.front().check;	//비트마스크
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nextY = y + dirY[i];
			int nextX = x + dirX[i];
			if(nextY>=0 && nextY<M && nextX>=0 && nextX<N) {
			    //벽
			    if(map[nextY][nextX]=='#') continue;
				//newCheck에 새로 챙긴 물건까지 저장(비트마스크)
				int newCheck = check | (1 << (map[nextY][nextX]-'0'));
				//물건이 있는 공간
				if(map[nextY][nextX]>='0' && map[nextY][nextX]<'5'  && !visit[nextY][nextX][newCheck]) {
				    visit[nextY][nextX][newCheck] = 1;
					q.push({nextY, nextX, time+1, newCheck});
					continue;
				}
				//물건을 모두 챙겼고 나가는 문 발견했으면 나가기
				if((check == (1 << numOfX)-1) && map[nextY][nextX]=='E') { ++time; return; }
				//빈 공간
				if(!visit[nextY][nextX][check]) {
				    visit[nextY][nextX][check] = 1;
				    q.push({nextY, nextX, time+1, check});
				}
			}
		}
	}
}
int main() {
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; i++) {
	    scanf("%s", &map[i]);
		for(int j = 0; j <= N; j++) {
			if(map[i][j]=='S') { y = i; x = j; }
			else if(map[i][j]=='X') map[i][j] = numOfX++ + '0';
		}
	}
    bfs();
	printf("%d", time);
	return 0;
}