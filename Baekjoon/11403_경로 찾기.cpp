// [11403] 경로 찾기 : https://www.acmicpc.net/problem/11403
#include <cstdio>

int n;
bool map[101][101];

void solve() {
	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(map[i][k] && map[k][j])
					map[i][j] = true;
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	}
	solve();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			(map[i][j]) ? printf("1 ") : printf("0 ");
		}
		printf("\n");
	}
}