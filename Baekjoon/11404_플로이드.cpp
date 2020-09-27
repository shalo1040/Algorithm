// [11404] 플로이드 : https://www.acmicpc.net/problem/11404
#include <cstdio>

int city, bus;
int cost[101][101];

int min(int a, int b) { return (a<b) ? a : b; }
void solve() {
	for(int k = 1; k <= city; k++) {
		for(int i = 1; i <= city; i++) {
			for(int j = 1; j <= city; j++) {
				if(i==j || i==k || k==j) continue;
				if(cost[i][k] && cost[k][j]) {
					if(!cost[i][j]) 
						cost[i][j] = cost[i][k] + cost[k][j];
					else
						cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
				}
			}
		}
	}
}
int main() {
	scanf("%d %d", &city, &bus);
	for(int i = 0; i < bus; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		cost[a][b] = c;
	}
	solve();
	for(int i = 1; i <= city; i++) {
		for(int j = 1; j <= city; j++)
			printf("%d ", cost[i][j]);
		printf("\n");
	}
	return 0;
}