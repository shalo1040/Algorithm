// [1389] 케빈 베이컨의 6단계 법칙 : https://www.acmicpc.net/problem/1389
#include <cstdio>

const int INF = 2e9;
int n, m;
int map[101][101];

int min(int a, int b) { return (a<b) ? a : b; }
void solve() {
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
			    if((i==j) || (i==k) || (k==j)) continue;
				if(map[i][k] < INF && map[k][j] < INF)
				    map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i <= n; i++) {
	    for(int j = 0; j <= n; j++)
	        map[i][j] = INF;
	}
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = map[b][a] = 1;
	}
	solve();
	int minSum = INF, idx = 0;
	for(int i = 1; i <= n; i++) {
		int sum = 0;
		for(int j = 1; j <= n; j++) {
		    if(i==j) continue;
			sum += map[i][j];
		}
		if(sum < minSum) {
			minSum = sum;
			idx = i;
		}
	}
	printf("%d", idx);
	return 0;
}