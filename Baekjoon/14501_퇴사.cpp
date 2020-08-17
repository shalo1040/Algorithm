// [14501] 퇴사 : https://www.acmicpc.net/problem/14501
#include <cstdio>

int n, ans;
int time[16], price[16], dp[16];

int max(int a, int b) { return (a < b) ? b : a; }

void solve() {
	//n번째부터 dp에 값을 저장한다.
	for(int i = n; i > 0; i--) {
		//주어진 일을 끝내고 새 일을 받을 수 있는 날
		int finishDay = i + time[i];
		if(finishDay > n+1) continue;
		//퇴사 전에 일을 끝낼 수 있지만 dp[finishDay]가 없을 때
		if(finishDay == n+1) dp[i] = price[i];
		else {
			//반드시 dp[finishDay]에 price[i]를 더할 필요 없이,
			//finishDay 이후의 날에 일을 받아도 무관하므로
			//값이 가장 큰 날에 price[i]를 더한다.
		    int maxi = finishDay;
		    for(int j = finishDay; j <= n; j++) {
		        if(dp[maxi] < dp[j]) maxi = j;
		    }
		    dp[i] = max(dp[i], dp[maxi] + price[i]);
		}
		ans = max(ans, dp[i]);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &time[i], &price[i]);
	solve();
	printf("%d", ans);
	return 0;
}