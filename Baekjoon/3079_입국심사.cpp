// [3079] 입국심사 : https://www.acmicpc.net/problem/3079
#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;
#define MAX 100001

//n: 입국심사대 개수
//m: 대기 중인 사람들 수
int n, m;
long long ans;
int time[MAX];

//mid가 유효한 값인지 여부 판단
bool check(long long mid) {
	long long sum = 0;	//mid 시간 안에 가능한 사람 수
	for(int i = 0; i < n; i++) {
		//mid 시간 안에 m명 이상 입국심사할 수 있으면 true 리턴
		if(sum >= m) return true;
		//mid 시간보다 처리 시간이 긴 입국 심사대면 break
		if(time[i] > mid) break;
		//각 입국 심사대마다 mid 시간 동안 mid/time[i] 명 처리 가능
		sum += mid/time[i];
	}
	if(sum >= m) return true;
	else return false;
}
//binary search
void solve() {
	long long left = time[0], right = (long long)time[0]*m;
	while(left <= right) {
		long long mid = (left+right)/2;
		if(check(mid)) {
			ans = mid;
			right = mid - 1;
		} else left = mid + 1;
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%d", time+i);
	sort(time, time+n);
	solve();
	printf("%lld", ans);
	return 0;
}