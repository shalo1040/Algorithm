// [9461] 파도반 수열 : https://www.acmicpc.net/problem/9461
#include <cstdio>

int T;
long long int memo[101];

long long int solve(int x) {
	if(x <= 3) { memo[x] = 1; return 1; }
	if(memo[x] == 0)
		memo[x] = solve(x-2) + solve(x-3);
	return memo[x];
}
int main() {
	scanf("%d", &T);
	while(T--) {
		int num;
		scanf("%d", &num);
		printf("%lld\n", solve(num));
	}
	return 0;
}