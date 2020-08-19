// [14890] 경사로 : https://www.acmicpc.net/problem/14890
#include <cstdio>
#include <cstring>

int size, L, ans;
int map[200][100];

int abs(int x) { return (x < 0) ? -x : x; }
void solve() {
	bool flag;
	int visit[size];
	for(int i = 0; i < 2*size; i++) {
		flag = true;
		memset(visit, 0, sizeof(visit));
		for(int j = 0; j < size; j++) {
			//다음 열의 원소와 1만큼 차이날 때
			if(j+1 < size && abs(map[i][j] - map[i][j+1]) == 1) {
				//왼쪽으로 경사로를 놓는 경우
				if(map[i][j] < map[i][j+1] && j-L+1 >= 0 && !visit[j]) {
					for(int k = 1; k < L; k++) {
						if(map[i][j-k] != map[i][j] || visit[j-k]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j-l] = 1;
					}
				}
				//오른쪽으로 경사로를 놓는 경우
				else if(map[i][j] > map[i][j+1] && j+L < size) {
					for(int k = 1; k < L; k++) {
						if(map[i][j+k+1] != map[i][j+1]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j+l+1] = 1;
						j += L-1;
					}
				} else flag = false;
			} else if(j+1 < size && abs(map[i][j] - map[i][j+1]) > 1) flag = false;
			if(!flag) break;
		}
		if(flag) ans++;
	}
}
int main() {
	scanf("%d %d", &size, &L);
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++)
			scanf("%d", &map[i][j]);
	}
	for(int i = size; i < 2*size; i++) {
		for(int j = 0; j < size; j++)
			map[i][j] = map[j][i-size];
	}
	solve();
	printf("%d", ans);
	return 0;
}

/*
처음엔 아래와 같이 열과 행을 따로 세주었으나
코드가 불필요하게 길어지고 중복되어 읽기와 수정이 불편했다.
위와 같이 map[][]을 두 배로 늘려 행만 세는 것처럼 코드를 수정해 불편함을 해결할 수 있었다.

#include <cstdio>
#include <cstring>

int size, L, ans;
int map[101][101];

int abs(int x) { return (x < 0) ? -x : x; }
void solve() {
	bool flag;
	int visit[size];
	//갈 수 있는 행 세기
	for(int i = 0; i < size; i++) {
		flag = true;
		memset(visit, 0, sizeof(visit));
		for(int j = 0; j < size; j++) {
			//다음 열의 원소와 1만큼 차이날 때
			if(j+1 < size && abs(map[i][j] - map[i][j+1]) == 1) {
				//왼쪽으로 경사로를 놓는 경우
				if(map[i][j] < map[i][j+1] && j-L+1 >= 0 && !visit[j]) {
					for(int k = 1; k < L; k++) {
						if(map[i][j-k] != map[i][j] || visit[j-k]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j-l] = 1;
					}
				}
				//오른쪽으로 경사로를 놓는 경우
				else if(map[i][j] > map[i][j+1] && j+L < size) {
					for(int k = 1; k < L; k++) {
						if(map[i][j+k+1] != map[i][j+1]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j+l+1] = 1;
						j += L-1;
					}
				} else flag = false;
			} else if(j+1 < size && abs(map[i][j] - map[i][j+1]) > 1) flag = false;
			if(!flag) break;
		}
		if(flag) ans++;
	}
	// 갈 수 있는 열 세기
	for(int i = 0; i < size; i++) {
		flag = true;
		memset(visit, 0, sizeof(visit));
		for(int j = 0; j < size; j++) {
			if(j+1 < size && abs(map[j][i] - map[j+1][i]) == 1) {
				if(map[j][i] < map[j+1][i] && j-L+1 >= 0 && !visit[j]) {
					for(int k = 1; k < L; k++) {
						if(map[j-k][i] != map[j][i] || visit[j-k]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j-l] = 1;
					}
				} else if(map[j][i] > map[j+1][i] && j+L < size) {
					for(int k = 1; k < L; k++) {
						if(map[j+k+1][i] != map[j+1][i]) {
							flag = false;
							break;
						}
					}
					if(flag) {
						for(int l = 0; l < L; l++)
							visit[j+l+1] = 1;
						j += L-1;
					}
				} else flag = false;
			} else if(j+1 < size && abs(map[j][i] - map[j+1][i]) > 1) flag = false;
			if(!flag) break;
		}
		if(flag) ans++;
	}
}
int main() {
	scanf("%d %d", &size, &L);
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++)
			scanf("%d", &map[i][j]);
	}
	solve();
	printf("%d", ans);
	return 0;
}
*/