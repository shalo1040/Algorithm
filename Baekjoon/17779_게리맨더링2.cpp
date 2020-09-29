// [17779] 게리맨더링2 : https://www.acmicpc.net/problem/17779
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, total, ans = 2e9;
int map[21][21];

int abs(int a) { return (a<0) ? -a : a; }
int min(int a, int b) { return (a<b) ? a : b; }
void solve() {
	for(int y = 1; y <= n; y++) {
		for(int x = 1; x <= n; x++) {
			for(int d1 = 1; d1 <= n; d1++) {
				for(int d2 = 1; d2 <= n; d2++) {
					if(y+d1+d2>n || x-d1<1 || x+d2>n) continue;
					int sum[6];
					memset(sum, 0, sizeof(sum));
					bool visit[n+1][n+1];
					for(int i = 1; i <= n; i++) {
					    for(int j = 1; j <= n; j++)
					        visit[i][j] = false;
					}
					/////////////////////////////////////////////////////
					//5번 구역
					for(int i = 0; i <= d1; i++)
					    visit[y+i][x-i] = visit[y+d2+i][x+d2-i] = true;
					for(int i = 0; i <= d2; i++)
					    visit[y+i][x+i] = visit[y+d1+i][x-d1+i] = true;
				    //1번 구역
					for(int r = 1; r < y+d1; r++) {
						for(int c = 1; c <= x; c++) {
						    if(visit[r][c]) break;
						    visit[r][c] = true;
							sum[1] += map[r][c];
						}
					}
					//2번 구역
					for(int r = 1; r <= y+d2; r++) {
						for(int c = n; c >= x+1; c--) {
						    if(visit[r][c]) break;
						    visit[r][c] = true;
							sum[2] += map[r][c];
						}
					}
					//3번 구역
					for(int r = y+d1; r <= n; r++) {
						for(int c = 1; c < x-d1+d2; c++) {
						    if(visit[r][c]) break;
						    visit[r][c] = true;
							sum[3] += map[r][c];
						}
					}
					//4번 구역
					for(int r = y+d2+1; r <= n; r++) {
						for(int c = n; c >= x-d1+d2; c--) {
						    if(visit[r][c]) break;
						    visit[r][c] = true;
							sum[4] += map[r][c];
						}
					}
					sum[5] = total - (sum[1] + sum[2] + sum[3] + sum[4]);
					/////////////////////////////////////////////////////
					
					/*
					처음엔 위의 ////로 감산 코드를 아래와 같이 적었더니 실행 시간도 더 오래 걸렸고 5번 구역의 코드 작성도 쉽지 않았다.

					//5번 구역
					//왼쪽 위 삼각형
					for(int r = y; r <= y+d1; r++) {
					    for(int c = x; c >= x-(r-y) && c >= 1; c--) {
					        if(visit[r][c]) continue;
					        visit[r][c] = true;
					        sum[5] += map[r][c];
					    }
					}
					//오른쪽 위 삼각형
					for(int r = y; r <= y+d2; r++) {
					    for(int c = x; c <= x+(r-y) && c <= n; c++) {
					        if(visit[r][c]) continue;
					        visit[r][c] = true;
					        sum[5] += map[r][c];
					    }
					}
					//왼쪽 아래 삼각형
					for(int r = y+d1; r <= y+d1+d2; r++) {
					    for(int c = x-d1+d2; c >= (x-d1)+(r-y-d1) && c >= 1; c--) {
					        if(visit[r][c]) continue;
					        visit[r][c] = true;
					        sum[5] += map[r][c];
					    }
					}
					//오른쪽 아래 삼각형
					for(int r = y+d2; r <= y+d1+d2; r++) {
					    for(int c = x-d1+d2; c <= (x+d2)-(r-y-d2) && c <= n; c++) {
					        if(visit[r][c]) continue;
					        visit[r][c] = true;
					        sum[5] += map[r][c];
					    }
					}
					//1번 구역
					for(int r = 1; r < y+d1; r++) {
						for(int c = 1; c <= x; c++) {
						    if(visit[r][c]) continue;
						    visit[r][c] = true;
							sum[1] += map[r][c];
						}
					}
					//2번 구역
					for(int r = 1; r <= y+d2; r++) {
						for(int c = x+1; c <= n; c++) {
						    if(visit[r][c]) continue;
						    visit[r][c] = true;
							sum[2] += map[r][c];
						}
					}
					//3번 구역
					for(int r = y+d1; r <= n; r++) {
						for(int c = 1; c < x-d1+d2; c++) {
						    if(visit[r][c]) continue;
						    visit[r][c] = true;
							sum[3] += map[r][c];
						}
					}
					//4번 구역
					for(int r = y+d2+1; r <= n; r++) {
						for(int c = x-d1+d2; c <= n; c++) {
						    if(visit[r][c]) continue;
						    visit[r][c] = true;
							sum[4] += map[r][c];
						}
					}
					*/
					
					//최솟값 찾기
					sort(sum+1, sum+6);
					ans = min(ans, abs(sum[5]-sum[1]));   //인구 수 가장 많은 구역과 적은 구역의 차
				}
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
			total += map[i][j];
		}
	}
	solve();
	printf("%d", ans);
	return 0;
}