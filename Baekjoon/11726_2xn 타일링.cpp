// [11726] 2xn 타일링 : https://www.acmicpc.net/problem/11726
#include <cstdio>

int n;
int arr[1001];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		if(i == 1) { arr[i] = 1; continue; }
		if(i == 2) { arr[i] = 2; continue; }
		arr[i] = (arr[i-1] + arr[i-2])%10007;
	}
	printf("%d", arr[n]);
	return 0;
}