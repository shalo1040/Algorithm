#include <cstdio>
#include <queue>
using namespace std;

int w, h, ans = 100;
char map[51][51];

int dirX[] = {1, 0};
int dirY[] = {0, 1};

//bfs
void solve(int startY, int startX, char startColor) {
	int cnt = 0;
	//색을 변경해줘야해서 임의의 map을 초기화한다.
	char tempMap[8][8];
	for(int i = 0; i < 8; i++) {
	    for(int j = 0; j < 8; j++) {
	    	//첫번째 칸이 W 또는 B일 경우를 모두 고려
	        if(i==0 && j==0 && startColor != map[startY+i][startX+j]) {
	            cnt++;
	            tempMap[i][j] = startColor;
	        } else tempMap[i][j] = map[startY+i][startX+j];
	    }
	}
	int visit[8][8] = { 0 };
	queue<pair<int, int>> q;
	q.push({0, 0});
	visit[0][0] = 1;
	while(!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for(int i = 0; i < 2; i++) {
			int nextY = y + dirY[i];
			int nextX = x + dirX[i];
			if(nextY<0 || nextY>=8 || nextX<0 || nextX>=8) continue;
			if(!visit[nextY][nextX]) {
				if(tempMap[nextY][nextX] == tempMap[y][x]) {
				    cnt++;
				    tempMap[nextY][nextX] = (tempMap[y][x] == 'W') ? 'B' : 'W';
				}
				visit[nextY][nextX] = 1;
				q.push({nextY, nextX});
			}
		}
	}
	ans = (ans < cnt) ? ans : cnt;
}
int main() {
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; i++)
		scanf("%s", &map[i]);
	for(int i = 0; i <= h-8; i++) {
		for(int j = 0; j <= w-8; j++) {
			solve(i, j, 'W');
			solve(i, j, 'B');
		}
	}
	printf("%d", ans);
	return 0;
}

/*
문제는 bfs로 풀었지만 아래 코드와 같이 풀면 코드도 훨씬 간결하고 실행 시간도 더 짧다.
#include <cstdio>

int w, h, ans = 100;
char map[51][51];

int main() {
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; i++)
		scanf("%s", &map[i]);
	int y = 0, x = 0;
	while(1) {
	    if(y+7==h) break;
	    if(x+7==w) { y++; x = 0; continue; }
	    int cntW = 64, cntB = 64;
	    for(int i = 0; i < 8; i++) {
	        for(int j = 0; j < 8; j++) {
	        	//첫번째 칸이 W면 cntW-1, B면 cntB-1
	            if((i+j)%2 == ((map[y+i][x+j] == 'W') ? 1 : 0)) cntW--;
	            else cntB--;
	        }
	    }
	    int min = (cntW < cntB) ? cntW : cntB;
	    ans = (ans < min) ? ans : min;
	    x++;
	}
	printf("%d", ans);
	return 0;
}
*/