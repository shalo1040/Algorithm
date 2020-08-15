// [2343] 기타 레슨 : https://www.acmicpc.net/problem/2343
#include <cstdio>
#define MAX 100001

/*
n: 레슨 개수
m: 블루레이 개수
left: 가장 긴 레슨 길이
right: 모든 레슨 길이의 합
ans: 가능한 블루레이 길이 중 최대값(mid)
*/
int n, m, left, right, ans;
int map[MAX];

//binary search
void solve() {
	while(left <= right) {
	    //mid: 예상하는 답
		int mid = (left+right)/2;
		int sum = 0, cnt = 1;
		for(int i = 0; i < n; i++) {
		    //합이 mid보다 크면 새 블루레이에 녹화
			if(sum+map[i] > mid) {
				sum = map[i];
				cnt++;
			} else sum += map[i];
		}
		//답이 mid일 때 필요한 블루레이의 수가 m보다 크면 left 이동
		if(cnt > m)
			left = mid + 1;
		else {
			ans = mid;  //가능한 mid 값 저장
			right = mid - 1;
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d", map+i);
		//가장 큰 블루레이의 길이보다 크거나 같은 값이 답
		left = (left < map[i]) ? map[i] : left;
		right += map[i];
	}
	solve();
	printf("%d", ans);
	return 0;
}