// [1904] 01타일 : https://www.acmicpc.net/problem/1904
#include <cstdio>

int n;
int memo[1000001] = {0, 1, 2};

//int solve2();

//DP_memoization
int solve(int x) {
	//memo에 넣어준 값이 없으면 계산
	if(memo[x] == 0)
		memo[x] = (solve(x-1) + solve(x-2)) % 15746;
	return memo[x];
}
int main() {
	scanf("%d", &n);
	printf("%d", solve(n));
	return 0;
}

/*
memoization으로 풀 때보다 더 빠르고 적은 메모리를 사용한다.
int solve2() {
    if(n==1) return 1;
    if(n==2) return 2;
    int cur, prev1=2, prev2=1;
    for(int i = 3; i <= n; i++) {
        cur = (prev1 + prev2) % 15746;
        prev2 = prev1;
        prev1 = cur;
    }
    return cur;
}
*/