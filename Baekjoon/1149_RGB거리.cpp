// [1149] RGB거리 : https://www.acmicpc.net/problem/1149
#include <cstdio>

//n: 집의 수
int n;
//rgb 가격 저장
int price[1001][3];
enum Color {RED, GREEN, BLUE};

int minimum(int a, int b) { return (a < b) ? a : b; }

int solve() {
	int totalPrice[1001][3] = {{price[0][RED], price[0][GREEN], price[0][BLUE]}};
	for(int i = 1; i < n; i++) {
		//i 번째에 빨간색을 칠했을 때
		totalPrice[i][RED] = minimum(totalPrice[i-1][GREEN], totalPrice[i-1][BLUE]) + price[i][RED];
		//i 번째에 초록색을 칠했을 때
		totalPrice[i][GREEN] = minimum(totalPrice[i-1][RED], totalPrice[i-1][BLUE]) + price[i][GREEN];
		//i 번째에 파란색을 칠했을 때
		totalPrice[i][BLUE] = minimum(totalPrice[i-1][RED], totalPrice[i-1][GREEN]) + price[i][BLUE];
	}
	return minimum(totalPrice[n-1][RED], minimum(totalPrice[n-1][GREEN], totalPrice[n-1][BLUE]));
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d %d", &price[i][RED] , &price[i][GREEN] ,&price[i][BLUE]);
	printf("%d", solve());
	return 0;
}