// [2294] 동전2 : https://www.acmicpc.net/problem/2294
#include <cstdio>
#include <algorithm>
#define INF 0xfffffff
using namespace std;

//n: 동전 개수, k: 최소 동전 개수를 알고 싶은 동전의 합
int n, k;
int coins[101];		//동전 가치
int cnt[10001];		//dp

void solve() {
	for(int i = 1; i <= k; i++) {
		for(int j = 0; j < n; j++) {
			if(cnt[i] == 1) break;
			if(coins[j] > k) continue;
			//j-coins[i]가 음수가 되면 배열 범위를 초과
			if(i < coins[j] || cnt[i-coins[j]] == INF) continue;
			cnt[i] = min(cnt[i], cnt[i-coins[j]] + 1);
		}
	}
}
int main() {
	scanf("%d %d", &n, &k);
	cnt[0] = 0;
	for(int i = 1; i <= k; i++)
	    cnt[i] = INF;
	for(int i = 0; i < n; i++) {
		scanf("%d", &coins[i]);
		/*
		coins[i]가 최대 100,000 값을 가질 수 있지만
		k는 최대 10,000이기 때문에 cnt 배열의 크기를 k에 맞췄고
		모든 coins[i]를 입력받으면 배열 범위 초과 에러가 난다.
		따라서 coins[i]가 k보다 작거나 같을 때만 cnt에 접근할 수 있도록한다.
		*/
		if(coins[i] <= k)
			cnt[coins[i]] = 1;
	}
	solve();
	if(cnt[k] == INF) printf("-1");
	else printf("%d", cnt[k]);
	return 0;
}