// [12865] 평범한 배낭 : https://www.acmicpc.net/problem/12865
#include <cstdio>
#include <algorithm>
using namespace std;

//n: 물건 개수, k: 최대 무개
int n, k, ans;
int list[101][2];	//무게, 가치
int dp[100001];		//인덱스는 무게로 접근(최대 무게: 100,000). 최대 가치 저장.

void solve() {
	//0번째부터 n-1번째 물건까지
	for(int i = 0; i < n; i++) {
		//추가로 넣을 수 있는 무게가 j일 때(1부터 최대 무게인 k까지)
		//j가 증가하는 반복문은 같은 물건을 중복해서 넣기 때문에 오답
		for(int j = k; j >= 1; j--) {
			//i번째 물건의 무게가 j보다 작거나 같으면
			if(list[i][0] <= j)
				//그 물건을 넣지 않는 경우와 넣는 경우 중 큰 값을 저장
				dp[j] = max(dp[j], dp[j-list[i][0]] + list[i][1]);
		}
	}
}
int main() {
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &list[i][0], &list[i][1]);
	//dp
	solve();
	//최대 가치 값 찾아 출력
	for(int i : dp)
	    if(ans < i) ans = i;
	printf("%d", ans);
	return 0;
}