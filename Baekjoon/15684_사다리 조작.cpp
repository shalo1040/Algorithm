// [15684] 사다리 조작 : https://www.acmicpc.net/problem/15684
#include <cstdio>
#include <vector>
using namespace std;

int h, w, lines, ans = 3210;
bool isPossible;
int map[32][11];
vector<pair<int, int>> nextLine;

int mini(int a, int b) { return (a < b) ? a : b; }
// 사다리타기
// i번에서 시작해서 i번으로 끝나는지 여부 반환
bool check() {
	bool flag = true;
	for(int i = 1; i <= w; i++) {
		int x = i;
		for(int y = 1; y <= h; y++) {
			switch(map[y][x]) {
				case 1:
					x--; break;
				case 2:
					x++; break;
			}
			if(y == h && x != i) flag = false;
		}
		if(!flag) break;
	}
	return flag;
}
// 완전탐색으로 cnt가 3보다 크지 않을 동안 다리를 놓을 수 있는 모든 조합 탐색
void solve(int idx, int cnt) {
	if(check()) { ans = mini(ans, cnt); isPossible = true; return; }
	if(cnt >= 3 || idx >= nextLine.size()) return;
	int y = nextLine[idx].first;
	int x = nextLine[idx].second;
	if(map[y][x] == map[y][x+1]) {
    	map[y][x] = 2;
    	map[y][x+1] = 1;
    	solve(idx+1, cnt+1);
    	map[y][x] = map[y][x+1] = 0;
	}
	solve(idx+1, cnt);
}
int main() {
	scanf("%d %d %d", &w, &lines, &h);
	for(int i = 0; i < lines; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		map[y][x] = 2;	//오른쪽으로
		map[y][x+1] = 1;	//왼쪽으로
	}
	for(int i = 1; i <= h; i++) {
		for(int j = 1; j <= w-1; j++) {
			// 다리를 놓을 수 있는 후보
			if(map[i][j] == 0 && map[i][j+1] == 0)
				nextLine.push_back({i, j});
		}
	}
	solve(0, 0);
	(isPossible) ? printf("%d", ans) : printf("-1");
	return 0;
}