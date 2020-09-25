// [2467] 용액 : https://www.acmicpc.net/problem/2467
#include <cstdio>
#include <algorithm>
using namespace std;

int N, a, b;
int arr[100001];

int abs(int x) { return (x<0) ? -x : x; }
int min(int x, int y) { return (abs(x)<abs(y)) ? x : y; }
void solve() {
	int ans = 2000000001;
	int start = 0;
	int end = N-1;
	while(start < end) {
		int result = arr[start] + arr[end];
		if(ans > abs(result)) {
		    ans = abs(result);
		    a = arr[start];
		    b = arr[end];
		}
		if(result >= 0) end--;
		else start++;
	}
}
int main() {
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	sort(arr, arr+N);
	solve();
	printf("%d %d", a, b);
	return 0;
}