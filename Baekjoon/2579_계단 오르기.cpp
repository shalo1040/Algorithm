// [2579] 계단 오르기 : https://www.acmicpc.net/problem/2579
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//n: 계단 수, stairs: 각 계단의 점수
int n;
int stairs[301];

void solve() {
	//score : 바로 앞 계단에서 올라왔을 때 점수
	//score2 : 두 칸 앞 계단에서 올라왔을 때 점수
	int score[n+1], score2[n+1];
	memset(score, 0, sizeof(score));
	memset(score2, 0, sizeof(score2));
	score[1] = stairs[1];
	score[2] = score[1] + stairs[2];
	score2[2] = stairs[2];
	//한 칸 오를 때는 이전 계단의 점수 중 두 칸을 올랐을 때의 점수(score2)에 합해야 조건 만족
	//두 칸 오를 때는 두 칸 전 계단의 점수(score, score2) 중 큰 수 선택
	for(int i = 3; i <= n; i++) {
		score[i] = score2[i-1] + stairs[i];
		score2[i] = max(score[i-2], score2[i-2]) + stairs[i];
	}
	printf("%d", max(score[n], score2[n]));
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &stairs[i]);
	solve();
	return 0;
}